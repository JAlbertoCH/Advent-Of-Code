#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <functional>

bool compare_by_hash(const int a, const int b, std::vector<std::vector<int>> relationships) {
    if (std::find(relationships[b].begin(), relationships[b].end(), a) != relationships[b].end()) {
        return true;
    } else {
        return false;
    }
}


int main() {
    std::vector<std::vector<int>> relationships(100, std::vector<int>());
    bool relationship_lines=true;
    size_t delimiter_pos;
    int n1, n2, count1=0, count2=0;
    std::function<bool(int, int)> bound_compare;
    
    std::string token;
    std::vector<int> numbers;
    bool valid;

    // Read input file
    std::ifstream input("full_input.txt");
    std::string line;
    while (std::getline(input, line)) {
        if (line == ""){
            relationship_lines = false;
            bound_compare = std::bind(compare_by_hash, std::placeholders::_1, std::placeholders::_2, relationships);
            continue;
        }
        if (relationship_lines) {
            delimiter_pos = line.find('|');
            n1 = std::stoi(line.substr(0, delimiter_pos));
            n2 = std::stoi(line.substr(delimiter_pos + 1));

            relationships[n2].push_back(n1);
        }else {
            numbers.clear();
            valid = true;

            std::stringstream ss(line);
            while (std::getline(ss, token, ',')) {
                numbers.push_back(std::stoi(token));
            }
            for (size_t i=numbers.size(); i<=numbers.size(); i--){
                // if number(out of relationships) not exists in line or number is before it means relationship holds.
                for (size_t j=0; j<relationships[numbers[i]].size(); j++){

                    if (std::find(numbers.begin()+i, numbers.end(), relationships[numbers[i]][j]) != numbers.end()){
                        valid = false;
                        break;
                    }
                }
                if (!valid){
                    break;
                }
            }
            if (valid){
                count1 += numbers[(numbers.size()-1)/2];
            }else{
                std::sort(numbers.begin(), numbers.end(), bound_compare);
                count2 += numbers[(numbers.size()-1)/2];
            }
        }
    }
    input.close();
    

    std::cout << "Result 1: " << count1 << std::endl;
    std::cout << "Result 2: " << count2 << std::endl;

    std::cout << "Challenge completed successfully!" << std::endl;

    return 0;
}
