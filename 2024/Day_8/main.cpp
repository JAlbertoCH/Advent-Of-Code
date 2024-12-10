#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <functional>
#include <unordered_map>
#include <unordered_set>

struct CustomHash {
    std::size_t operator()(const std::vector<int>& position) const {
        // Combine the two integers using a common hash-combination technique
        return position[0] * 31 + position[1];
    }
};


int main() {
    int count1=0, count2=0;
    int max_width=0, max_height=0, antinode_x, antinode_y;
    std::unordered_map<char, std::vector<std::vector<int>>> antennas;
    std::unordered_set<std::vector<int>, CustomHash> antinodes, antinodes2;

    // Read input file
    std::ifstream input("full_input.txt");
    std::string line;
    while (std::getline(input, line)) {
        if (!max_width){
            max_width = line.size();
        }
        for (int i=0; i<max_width; i++){
            if (line[i] != '.'){
                if (antennas.find(line[i]) != antennas.end()){
                    antennas[line[i]].push_back({i, max_height});
                }else{
                    antennas[line[i]] = {{i, max_height}};
                }
            }
        }
        max_height++; 
    }
    input.close();

    for (const auto& pair : antennas) {
        std::cout << pair.first << ": "<< "\n";
        for (size_t i=0; i< pair.second.size(); i++){
            for (size_t j=0; j< pair.second.size(); j++){
                if (i==j){
                    continue;
                }
                std::cout << "Compare: " << pair.second[j][0] << "," << pair.second[j][1] << " with "<< pair.second[i][0] << "," << pair.second[i][1] << std::endl;
                 
                antinode_x = pair.second[j][0];
                antinode_y = pair.second[j][1];
                if (antinode_x + (pair.second[j][0] - pair.second[i][0])>=0 && antinode_x+ (pair.second[j][0] - pair.second[i][0])<max_width && antinode_y+(pair.second[j][1] - pair.second[i][1])>=0 && antinode_y+(pair.second[j][1] - pair.second[i][1])<max_height){
                    antinodes.insert({antinode_x+(pair.second[j][0] - pair.second[i][0]), antinode_y+(pair.second[j][1] - pair.second[i][1])});
                }
                while (antinode_x>=0 && antinode_x<max_width && antinode_y>=0 && antinode_y<max_height){
                    antinodes2.insert({antinode_x, antinode_y});
                    antinode_x += (pair.second[j][0] - pair.second[i][0]);
                    antinode_y += (pair.second[j][1] - pair.second[i][1]);
                }
            }
            
        }
    }

    count1 = antinodes.size();
    count2 = antinodes2.size();

    std::cout << "Result 1: " << count1 << std::endl;
    std::cout << "Result 2: " << count2 << std::endl;

    std::cout << "Challenge completed successfully!" << std::endl;

    return 0;
}
