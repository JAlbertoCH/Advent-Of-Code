#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <functional>
#include <unordered_set>

struct CustomHash {
    std::size_t operator()(const std::vector<int>& position) const {
        // Combine the two integers using a common hash-combination technique
        return position[0] * 31 + position[1];
    }
};

struct CustomHash2 {
    std::size_t operator()(const std::vector<int>& position) const {
        // Combine the two integers using a common hash-combination technique
        std::size_t hash0 = std::hash<int>()(position[0]);
        std::size_t hash1 = std::hash<int>()(position[1]);
        std::size_t hash2 = std::hash<int>()(position[2]);
        return  hash0 ^ (hash1 << 1) ^ (hash2 << 2);
    }
};


int main() {
    int count1=0, count2=0;
    std::vector<std::vector<std::vector<int>>> obstacles(2, std::vector<std::vector<int>>());

    std::vector<int> position(2), init_position(2);
    int init_direction, direction = 0, increment = 0;
    bool end, is_y, is_closed_path;

    std::unordered_set<std::vector<int>, CustomHash> path;
    std::unordered_set<std::vector<int>, CustomHash2> closed_path;


    int y = 0;


    // Read input file
    std::ifstream input("full_input2.txt");
    std::string line;
    while (std::getline(input, line)) {
        if (y==0){
            obstacles[1] = std::vector<std::vector<int>> (line.size(), std::vector<int>());
        }
        obstacles[0].push_back(std::vector<int> {});

        for (int x=0; x<line.size(); x++){
            
            if (line[x] == '#'){
                obstacles[0][y].push_back(x);
                obstacles[1][x].push_back(y);
                continue;
            }else if (line[x] == '^' || line[x] == 'v'){
                position = {x, y};
                direction = (line[x] == '^') * 2;
            }else if (line[x] == '>' || line[x] == '<'){
                position = {x, y};
                direction = (line[x] == '<') * 2 + 1;
            }
        }
        y++;
    }
    input.close();

    init_position = position;
    init_direction = direction;
    path.insert(position);
    while(1){
        is_y = !(direction%2);
        end=true;
        increment = (direction <= 1) * 2 - 1;
        for (size_t i = (increment<0)*(obstacles[is_y][position[!is_y]].size()-1); i < obstacles[is_y][position[!is_y]].size() && i>=0; i+= increment){
            // increment < 0 -> position < obstacle, increment > 0 -> position < obstacle
            if (increment * (obstacles[is_y][position[!is_y]][i]-position[is_y])  > 0){
                while(abs(position[is_y] - obstacles[is_y][position[!is_y]][i]) != 1){
                    position[is_y] += increment;
                    path.insert(position);
                }
                end = false;
                direction -= 1;
                direction += 4 * (direction < 0);
                direction = direction % 4;
                break;
            }
        }
        if (end){
            while(position[is_y] + increment < obstacles[!is_y].size() and position[is_y] + increment >= 0){
                position[is_y] += increment;
                path.insert(position);
            }
            break;
        }
    }

    count1 = path.size();
    path.erase(init_position);
    std::vector<std::vector<int>> vec_path(path.begin(), path.end());
    std::cout << "size: " << vec_path.size() << std::endl;
    
    for (size_t i=0; i < vec_path.size(); i++){
        std::cout << "i: " << i << std::endl;
        auto it = std::lower_bound(obstacles[0][vec_path[i][1]].begin(), obstacles[0][vec_path[i][1]].end(), vec_path[i][0]);
        obstacles[0][vec_path[i][1]].insert(it, vec_path[i][0]);

        it = std::lower_bound(obstacles[1][vec_path[i][0]].begin(), obstacles[1][vec_path[i][0]].end(), vec_path[i][1]);
        obstacles[1][vec_path[i][0]].insert(it, vec_path[i][1]);

        position = init_position;
        direction = init_direction;


        is_closed_path = false;
        closed_path.clear();
        while(1){
            is_y = !(direction%2);
            end=true;
            increment = (direction <= 1) * 2 - 1;
            for (size_t i = (increment<0)*(obstacles[is_y][position[!is_y]].size()-1); i < obstacles[is_y][position[!is_y]].size() && i>=0; i+= increment){
                if (increment * (obstacles[is_y][position[!is_y]][i]-position[is_y])  > 0){
                    while(abs(position[is_y] - obstacles[is_y][position[!is_y]][i]) != 1){
                        position[is_y] += increment;
                        if (closed_path.find({position[0], position[1], direction}) == closed_path.end()) {
                            closed_path.insert({position[0], position[1], direction});
                        } else {
                            is_closed_path = true;
                            break;
                        }
                    }
                    end = false;
                    direction -= 1;
                    direction += 4 * (direction < 0);
                    direction = direction % 4;
                    break;
                }
            }
            if (is_closed_path){

                count2++;
                break;
            }
            if (end){
                break;
            }

        }

        auto it2 = std::find(obstacles[0][vec_path[i][1]].begin(), obstacles[0][vec_path[i][1]].end(), vec_path[i][0]);  // Find the first occurrence of '2'
        if (it2 != obstacles[0][vec_path[i][1]].end()) {
            obstacles[0][vec_path[i][1]].erase(it2);
        }
        auto it3 = std::find(obstacles[1][vec_path[i][0]].begin(), obstacles[1][vec_path[i][0]].end(), vec_path[i][1]);  // Find the first occurrence of '2'
        if (it3 != obstacles[1][vec_path[i][0]].end()) {
            obstacles[1][vec_path[i][0]].erase(it3); 
        }
    }
    


    

    std::cout << "Result 1: " << count1 << std::endl;
    std::cout << "Result 2: " << count2 << std::endl;

    std::cout << "Challenge completed successfully!" << std::endl;

    return 0;
}
