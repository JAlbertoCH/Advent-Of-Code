#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <functional>
#include <unordered_set>
#include <queue>

int manhattan_distance(std::pair<size_t, size_t> probe, std::pair<size_t, size_t> target){
    return abs(target.second - probe.second) + abs(target.first - probe.first);
}

struct CustomHash {
    std::size_t operator()(const std::pair<size_t, size_t>& position) const {
        // Combine the two integers using a common hash-combination technique
        return position.first * 31 + position.second;
    }
};

std::unordered_map<std::pair<size_t, size_t>, int, CustomHash> costs_numeric_keypad, costs_directional_keypad_1, costs_directional_keypad_2;
std::vector<std::pair<size_t, size_t>> directional_keypad_cords = {
    {0,0},
    {1,0},
    {0,1},
    {1,1},
    {2,1}
};

std::vector<std::pair<size_t, size_t>> numeric_keypad_cords = {
    {1,0},
    {2,1},
    {1,1},
    {0,1},
    {2,2},
    {1,2},
    {0,2},
    {2,3},
    {1,3},
    {0,3},
    {0,0}
};


int get_optimal_cost_directional(std::pair<size_t, size_t> probe, std::pair<size_t, size_t>target){

    int min_cost= -1;
    int rows=2, cols=3;

    std::priority_queue<std::pair<int, std::vector<size_t>>, std::vector<std::pair<int, std::vector<size_t>>>, std::greater<>> openList;
    std::unordered_map<std::pair<size_t, size_t>, int, CustomHash> gScore;
    openList.push({0, {probe.first, probe.second, 0}});
    gScore[probe] = 0;

    std::vector<std::pair<int, int>> directions = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
    

    while (!openList.empty()) {
        std::vector<size_t> current_state = openList.top().second;
        std::pair<size_t, size_t> current = {current_state[0], current_state[1]};
        openList.pop();

        // Goal check
        if (!manhattan_distance(current, target)) {
            if (min_cost > gScore[current] + costs_directional_keypad_1[{current_state[2], 0}] || min_cost == -1){
                // Added last press
                min_cost = gScore[current] + costs_directional_keypad_1[{current_state[2], 0}];
            }
            continue;
        }

        for (size_t i=0; i<directions.size(); i++){
            std::pair<size_t, size_t> neighbor = {current.first + directions[i].first, current.second + directions[i].second};
            
            if (neighbor.first<cols && neighbor.second<rows && (neighbor.first!=2 || neighbor.second!=0)){
                int tentativeG = gScore[current] + costs_directional_keypad_1[{current_state[2], i+1}] ;
                //std::cout<<current.first<<","<<current.second<< " checked "<<neighbor.first<< ","<< neighbor.second<< "-"<< (costs_directional_keypad_1[{0, i+1}] )<< costs_directional_keypad_1[{i+1, 0}]<<std::endl;
                
                if (!gScore.count(neighbor) || tentativeG < gScore[neighbor]) {
                    gScore[neighbor] = tentativeG;
                    int fScore = tentativeG + 3 * manhattan_distance(neighbor, target);
                    //std::cout<<current.first<<","<<current.second<< " added "<<neighbor.first<< ","<< neighbor.second<<std::endl;
                    openList.push({fScore, {neighbor.first, neighbor.second, i+1}});
                }
            }
        }
    }
    if (min_cost<0){
        //std::cout<<probe.first<<","<<probe.second<< " "<<target.first<< ","<< target.second<<std::endl;
    }else{
        //std::cout<<probe.first<<","<<probe.second<< " "<<target.first<< ","<< target.second<<std::endl;
    }
    return min_cost;
}


int get_optimal_cost(std::pair<size_t, size_t> probe, std::pair<size_t, size_t>target){

    int min_cost= -1;
    int rows=4, cols=3;

    std::priority_queue<std::pair<int, std::vector<size_t>>, std::vector<std::pair<int, std::vector<size_t>>>, std::greater<>> openList;
    std::unordered_map<std::pair<size_t, size_t>, int, CustomHash> gScore;
    openList.push({0, {probe.first, probe.second, 0}});
    gScore[probe] = 0;

    std::vector<std::pair<int, int>> directions = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
    

    while (!openList.empty()) {
        std::vector<size_t> current_state = openList.top().second;
        std::pair<size_t, size_t> current = {current_state[0], current_state[1]};
        openList.pop();

        // Goal check
        if (!manhattan_distance(current, target)) {
            if (min_cost > gScore[current] + costs_directional_keypad_2[{current_state[2], 0}] || min_cost == -1){
                // Added last press
                min_cost = gScore[current] + costs_directional_keypad_2[{current_state[2], 0}];
            }
            continue;
        }

        for (size_t i=0; i<directions.size(); i++){
            std::pair<size_t, size_t> neighbor = {current.first + directions[i].first, current.second + directions[i].second};
            
            if (neighbor.first<cols && neighbor.second<rows && (neighbor.first!=2 || neighbor.second!=0)){
                int tentativeG = gScore[current] + costs_directional_keypad_2[{current_state[2], i+1}];
                std::cout<<current.first<<","<<current.second<< " checked "<<neighbor.first<< ","<< neighbor.second<< "-"<< (costs_directional_keypad_2[{current_state[2], i+1}] )<<std::endl;
                
                if (!gScore.count(neighbor) || tentativeG < gScore[neighbor]) {
                    gScore[neighbor] = tentativeG;
                    int fScore = tentativeG + 3 * manhattan_distance(neighbor, target);
                    //std::cout<<current.first<<","<<current.second<< " added "<<neighbor.first<< ","<< neighbor.second<<std::endl;
                    openList.push({fScore, {neighbor.first, neighbor.second, i+1}});
                }
            }
        }
    }
    return min_cost;
}






void initialize_costs(){
    //Initialize direction costs
    for (size_t i = 0; i<5;i++){
        for (size_t j = 0; j<5;j++){
            costs_directional_keypad_1[{i, j}] = manhattan_distance(directional_keypad_cords[i], directional_keypad_cords[j]) + 1;
            //std::cout<<i<<" "<<j<< ":" <<costs_directional_keypad_1[{i, j}] <<std::endl;
        }
    }

    for (size_t i = 0; i<5;i++){
        for (size_t j = 0; j<5;j++){
            costs_directional_keypad_2[{i, j}] = get_optimal_cost_directional(directional_keypad_cords[i], directional_keypad_cords[j]);
            //std::cout<<i<<" "<<j<< ":" <<costs_directional_keypad_2[{i, j}] <<std::endl;
        }
    }
     
    //Initialize numeric costs
    for (size_t i = 2; i<=10;i++){
        for (size_t j = 9; j<=10;j++){
            costs_numeric_keypad[{i, j}] = get_optimal_cost(numeric_keypad_cords[i], numeric_keypad_cords[j]);
            std::cout<<costs_numeric_keypad[{i, j}]<<std::endl;
            break;
        }
        break;
    }
}






int main() {
    int count1=0, count2=0, key, number;
    initialize_costs();

    size_t position = 10;


    // Read input file
    std::ifstream input("input.txt");
    std::string line;
    while (std::getline(input, line) && line.size()) {
        int length = 0, number = 0;
        for (size_t i=0; i<line.size();i++){
            if (line[i] == 'A'){
                key = 10;
            }else{
                key = line[i] - '0';
            }
            length += costs_numeric_keypad[{position, key}];
            std::cout << position << " "<< key<<" "<< costs_numeric_keypad[{position,key}]<< std::endl;
            position = key;
            if (key<10){
                number = number * 10 + key;
            }
        }
        std::cout << length << " "<< number<< std::endl;
        count1 += length * number;
    }
    input.close();
    

    std::cout << "Result 1: " << count1 << std::endl;
    std::cout << "Result 2: " << count2 << std::endl;

    std::cout << "Challenge completed successfully!" << std::endl;

    return 0;
}
