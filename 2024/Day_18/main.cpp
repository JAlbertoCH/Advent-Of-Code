#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <functional>
#include <unordered_set>
#include <queue>


struct CustomHash {
    std::size_t operator()(const std::vector<size_t>& position) const {
        // Combine the two integers using a common hash-combination technique
        return position[0] * 31 + position[1];
    }
};

std::vector<std::vector<size_t>> map;
std::unordered_map<std::vector<size_t>, std::vector<size_t>, CustomHash> cameFrom; // Parent map for path reconstruction

std::unordered_set<std::vector<size_t>, CustomHash> full_path;


void print_table(){
    for (size_t y = 0; y<map.size();y++){
        for (size_t x = 0; x<map[y].size();x++){
            if (map[y][x] == 1){
                std::cout << '#';
            }else if(map[y][x] == 0){
                std::cout << '.';
            }else if(map[y][x] == 2){
                std::cout << '[';
            }else if(map[y][x] == 3){
                std::cout << '@';
            }else if(map[y][x] == 4){
                std::cout << ']';
            }
            
        }
        std::cout << std::endl;
    }
    std::cout<<std::endl;
}

void clear_path_map(){
    for (size_t y = 0; y<map.size();y++){
        for (size_t x = 0; x<map[y].size();x++){
            if (map[y][x] == 2){
                map[y][x] = 0;
            }
        }
    }
}

void add_falling_bits(std::vector<std::vector<size_t>> falling_bits, size_t t){
    for (size_t i =0; i<t;i++){
        map[falling_bits[i][1]][falling_bits[i][0]]= 1;
    }
}



int heuristic(std::vector<size_t> probe, std::vector<size_t>target){
    return abs(target[1] - probe[1]) + abs(target[0] - probe[0]);
}

int find_path(std::vector<size_t> probe, std::vector<size_t>target){

    int min_cost=-1;
    int rows=map.size(), cols=map[0].size();

    std::priority_queue<std::pair<int, std::vector<size_t>>, std::vector<std::pair<int, std::vector<size_t>>>, std::greater<>> openList;
    openList.push({0, probe});
    std::unordered_map<std::vector<size_t>, int, CustomHash> gScore;

    gScore[probe] = 0;

    std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    full_path.clear();
    

    while (!openList.empty()) {
        std::vector<size_t> current = openList.top().second;
        openList.pop();
        //std::cout << current[0] << " "<< current[1]<< ", " << target[0] << " "<< target[1] << std::endl;

        // Goal check
        if (!heuristic(current, target)) {
            min_cost = gScore[current];
            std::vector<size_t> path = current;
            clear_path_map();
            while(path != probe){
                map[path[1]][path[0]] = 3;
                full_path.insert(path);
                path = cameFrom[path];
            }
            break;
        }
        

        // Explore neighbors
        for (const auto& dir : directions) {
            std::vector<size_t> neighbor = {current[0] + dir.first, current[1] + dir.second};
            if (neighbor[1] >= rows || neighbor[0] >= cols) continue;
            if (map[neighbor[1]][neighbor[0]] == 1) continue;
            //std::cout << neighbor[0] << " "<< neighbor[1]<< ", " << target[0] << " "<< target[1] << std::endl;

            int tentativeG = gScore[current] + 1;
            
            if (!gScore.count(neighbor) || tentativeG < gScore[neighbor]) {
                gScore[neighbor] = tentativeG;
                cameFrom[neighbor] = current;
                int fScore = tentativeG + heuristic(neighbor, target);
                openList.push({fScore, neighbor});
            }
        }
    }
    return min_cost;
}




int main() {
    std::vector<std::vector<size_t>> falling_bits;
    size_t grid_size = 70, t=1024;
    int count1, count2;

    map = std::vector<std::vector<size_t>>(grid_size + 1, std::vector<size_t>(grid_size+1, 0));
    
    // Read input file
    std::ifstream input("full_input.txt");
    std::string line;
    while (std::getline(input, line)) {

        std::regex pattern_coordinates(R"((\d+),(\d+))");

        std::smatch match;

        // Iterate through matches
        std::sregex_iterator begin(line.begin(), line.end(), pattern_coordinates);
        std::sregex_iterator end;

        if (begin != end) {
            match = *begin;
            falling_bits.push_back({(size_t)stoi(match.str(1)),(size_t)stoi(match.str(2))});
            continue;
        }
        
    }
    input.close();

    add_falling_bits(falling_bits, t);
    print_table();

    count1 = find_path({0,0}, {grid_size, grid_size});
    count2 =count1;
    while (count2 != -1 && t<falling_bits.size()){
        add_falling_bits({falling_bits[t]}, 1);
        print_table();
        std::cout << falling_bits[t][0]<< "," << falling_bits[t][1] << "-" << (full_path.find(falling_bits[t])!= full_path.end()) <<std::endl;
        if (full_path.find(falling_bits[t])!= full_path.end()){
            count2 = find_path({0,0}, {grid_size, grid_size});
        }
        t++;
    }


    

    std::cout << "Result 1: " << count1 << std::endl;
    std::cout << "Result 2: " << t<<"/"<< falling_bits.size()<<  "-"<< falling_bits[t-1][0]<< ","<<falling_bits[t-1][1]  << std::endl;

    std::cout << "Challenge completed successfully!" << std::endl;

    return 0;
}
