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
        return (position[0] * 31 + position[1])*31 + position[2];
    }
};

std::vector<std::vector<size_t>> map;
std::unordered_map<std::vector<size_t>, std::vector<std::vector<size_t>>, CustomHash> cameFrom; // Parent map for path reconstruction




void print_table(){
    for (size_t y = 0; y<map.size();y++){
        for (size_t x = 0; x<map[y].size();x++){
            if (map[y][x] == 1){
                std::cout << '#';
            }else if(map[y][x] == 0){
                std::cout << '.';
            }else if(map[y][x] == 2){
                std::cout << 'v';
            }else if(map[y][x] == 3){
                std::cout << '>';
            }else if(map[y][x] == 4){
                std::cout << '^';
            }else if(map[y][x] == 5){
                std::cout << '<';
            }
            
        }
        std::cout << std::endl;
    }
    std::cout<<std::endl;
}

int count_optimal_path_tiles(){
    int count=0;
    for (size_t y = 0; y<map.size();y++){
        for (size_t x = 0; x<map[y].size();x++){
            if (map[y][x] == 2){
                count++;
            }
        }
    }
    return count;
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

void pin_on_map_path(std::vector<size_t> current, std::vector<size_t> probe){
    if (current == probe || map[current[1]][current[0]] == 2){
        map[current[1]][current[0]] = 2;
        return;
    }
    for (size_t i =0; i<cameFrom[current].size();i++){
        pin_on_map_path(cameFrom[current][i], probe);
    }
    map[current[1]][current[0]] = 2;
}



int heuristic(std::vector<size_t> probe, std::vector<size_t>target){
    return abs(target[1] - probe[1]) + abs(target[0] - probe[0]);
}

int count_reacheable(std::vector<size_t> probe, std::vector<size_t>target){

    int count=0, min_cost= 10000 * heuristic(probe, target);
    int rows=map.size(), cols=map[0].size();

    std::priority_queue<std::pair<int, std::vector<size_t>>, std::vector<std::pair<int, std::vector<size_t>>>, std::greater<>> openList;
    openList.push({0, probe});
    std::unordered_map<std::vector<size_t>, int, CustomHash> gScore;
    
    

    gScore[probe] = 0;

    std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    

    while (!openList.empty()) {
        //std::cout<< openList.size()<<std::endl;
        std::vector<size_t> current = openList.top().second;
        openList.pop();

        //std::cout << current[0] << " "<< current[1]<< ", " << target[0] << " "<< target[1] << std::endl;
        //map[current[1]][current[0]]=current[2]+2;
        //print_table();

        // Goal check
        if (!heuristic(current, target)) {
            if (min_cost >= gScore[current]){
                min_cost = gScore[current];
                clear_path_map();
                pin_on_map_path(current, probe);
            }
            continue;
        }

        std::vector<size_t> neighbor = {current[0] + directions[current[2]].first, current[1] + directions[current[2]].second, current[2]};
        //std::cout << neighbor[0] << " "<< neighbor[1]<< ", " << map[neighbor[1]][neighbor[0]]  << " " << std::endl;
        if (map[neighbor[1]][neighbor[0]] != 1){
            int tentativeG = gScore[current] + 1;
            
            if (!gScore.count(neighbor) || tentativeG <= gScore[neighbor]) {
                if (tentativeG == gScore[neighbor]){
                    cameFrom[neighbor].push_back(current);
                } else{
                    gScore[neighbor] = tentativeG;
                    cameFrom[neighbor] = {current};
                }
                int fScore = tentativeG + heuristic(neighbor, target);
                openList.push({fScore, neighbor});
            }
        }

        neighbor = {current[0], current[1], (current[2] + 1)%4};
        int tentativeG = gScore[current] + 1000;

        if (!gScore.count(neighbor) || tentativeG <= gScore[neighbor]) {
            if (tentativeG == gScore[neighbor]){
                cameFrom[neighbor].push_back(current);
            } else{
                gScore[neighbor] = tentativeG;
                cameFrom[neighbor] = {current};
            }
            int fScore = tentativeG + heuristic(neighbor, target);
            openList.push({fScore, neighbor});
        }

        neighbor = {current[0], current[1], (current[2] - 1)%4};
        if (!gScore.count(neighbor) || tentativeG <= gScore[neighbor]) {
            if (tentativeG == gScore[neighbor]){
                cameFrom[neighbor].push_back(current);
            } else{
                gScore[neighbor] = tentativeG;
                cameFrom[neighbor] = {current};
            }
            int fScore = tentativeG + heuristic(neighbor, target);
            openList.push({fScore, neighbor});
        }
    }
    return min_cost;
}







int main() {
    int count1=0, count2=0;

    std::vector<size_t> position, target;
    int width, height;
    size_t y = 0;


    // Read input file
    std::ifstream input("full_input.txt");
    std::string line;
    while (std::getline(input, line) && line.size()) {
        if(!map.size()){
            width = line.size();
        }
        map.push_back(std::vector<size_t> (width, 0));
        for (size_t x=0; x<line.size(); x++){
            //std::cout<<x<< ": "<< line[x]<<std::endl;
            if (line[x] == '#'){
                map[y][x]=1;
                continue;
            }else if (line[x] == 'S'){
                map[y][x]=0;
                position = {x, y, 1};
            }else if (line[x] == 'E'){
                map[y][x]=0;
                target = {x, y, 1};
            }else{
                map[y][x]=0;
                map[y][x]=0;
            }
        }
        y++;
    }
    input.close();

    print_table();

    count1 = count_reacheable(position, target);
    count2 = count_optimal_path_tiles();

    print_table();
    

    std::cout << "Result 1: " << count1 << std::endl;
    std::cout << "Result 2: " << count2 << std::endl;

    std::cout << "Challenge completed successfully!" << std::endl;

    return 0;
}
