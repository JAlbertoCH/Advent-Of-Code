#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <functional>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <queue>

struct CustomHash {
    std::size_t operator()(const std::vector<size_t>& position) const {
        // Combine the two integers using a common hash-combination technique
        return position[0] * 31 + position[1];
    }
};

int heuristic(std::vector<size_t> probe, std::vector<size_t>target){
    return abs(target[1] - probe[1]) + abs(target[0] - probe[0]);
}

int count_reacheable(std::vector<size_t> probe, std::vector<size_t>target, std::vector<std::vector<size_t>> topology){
    if (heuristic(probe, target)>9){
        return 0;
    }

    int count=0;
    int rows=topology.size(), cols=topology[0].size();

    std::priority_queue<std::pair<int, std::vector<size_t>>, std::vector<std::pair<int, std::vector<size_t>>>, std::greater<>> openList;
    openList.push({0, probe});
    std::unordered_map<std::vector<size_t>, int, CustomHash> gScore;

    gScore[probe] = 0;

    std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    

    while (!openList.empty()) {
        std::vector<size_t> current = openList.top().second;
        openList.pop();

        //std::cout << current[0] << " "<< current[1]<< ", " << target[0] << " "<< target[1] << std::endl;

        // Goal check
        if (!heuristic(current, target)) {
            count++;
            continue;
        }
        

        // Explore neighbors
        for (const auto& dir : directions) {
            std::vector<size_t> neighbor = {current[0] + dir.first, current[1] + dir.second};
            if (neighbor[1] >= rows || neighbor[0] >= cols) continue;
            if (topology[neighbor[1]][neighbor[0]]-topology[current[1]][current[0]] != 1 || heuristic(neighbor, target)>9) continue;

            int tentativeG = gScore[current] + 1;
            if (!gScore.count(neighbor) || tentativeG <= gScore[neighbor]) {
                gScore[neighbor] = tentativeG;
                int fScore = tentativeG + heuristic(neighbor, target);
                openList.push({fScore, neighbor});
            }
        }
    }
    return count;
}


int main() {
    int count1=0, count2=0, paths=0;
    
    

    std::vector<std::vector<size_t>> topology;
    std::vector<std::vector<size_t>> starting_points;
    std::vector<std::vector<size_t>> targets;

    // Read input file
    std::ifstream input("full_input.txt");
    std::string line;
    size_t lines=0, height=0;
    while (std::getline(input, line)) {
        topology.push_back({});
        for (size_t i =0; i<line.size(); i++){
            height = int(line[i]-'0');
            if (!height){
                starting_points.push_back({i, lines});
            }else if(height == 9){
                targets.push_back({i, lines});
            }
            topology[lines].push_back(height);
        }
        lines++;
    }
    input.close();

    for (size_t i=0;i<starting_points.size();i++){
        for (size_t j=0;j<targets.size();j++){
            //std::cout << starting_points[i][0] << " "<< starting_points[i][1]<< ", " << targets[j][0] << " "<< targets[j][1] << std::endl;
            paths = count_reacheable(starting_points[i], targets[j], topology);
            count2 += paths;
            if (paths){
                count1++;
            }
        }
    }
    std::cout << "Result 1: " << count1 << std::endl;
    std::cout << "Result 2: " << count2 << std::endl;

    std::cout << "Challenge completed successfully!" << std::endl;

    return 0;
}
