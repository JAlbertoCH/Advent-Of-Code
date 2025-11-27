#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <functional>
#include <cmath>

std::unordered_map<std::string, bool> wires;
std::vector<std::pair<std::pair<std::string, std::string>, std::string>> xor_instructions, or_instructions, and_instructions;

bool run_instructions(std::vector<std::pair<std::pair<std::string, std::string>, std::string>>& instructions, int operation){
    bool missing = false;
    for (size_t i = 0; i < instructions.size(); i++) {
        if (wires.find(instructions[i].second) == wires.end() && wires.find(instructions[i].first.first) != wires.end() && wires.find(instructions[i].first.second) != wires.end()) {
            if (operation == 0){
                wires[instructions[i].second] = wires[instructions[i].first.first] & wires[instructions[i].first.second];
            } else if (operation == 1){
                wires[instructions[i].second] = wires[instructions[i].first.first] | wires[instructions[i].first.second];
            } else if (operation == 2){
                wires[instructions[i].second] = wires[instructions[i].first.first] ^ wires[instructions[i].first.second];
            }
        } else if (wires.find(instructions[i].second) == wires.end()) {
            missing = true;
        }
    }
    return missing;
}


int get_ouput(std::string output, std::unordered_map<std::string, bool> wires, std::vector<std::pair<std::pair<std::string, std::string>, std::string>>& instructions, int operation){
    int j = 0;
    while (j<1000 && wires.find(output) == wires.end()){
        for (size_t i = 0; i < instructions.size(); i++) {
            if (wires.find(instructions[i].second) == wires.end() && wires.find(instructions[i].first.first) != wires.end() && wires.find(instructions[i].first.second) != wires.end()) {
                if (operation == 0){
                    wires[instructions[i].second] = wires[instructions[i].first.first] & wires[instructions[i].first.second];
                } else if (operation == 1){
                    wires[instructions[i].second] = wires[instructions[i].first.first] | wires[instructions[i].first.second];
                } else if (operation == 2){
                    wires[instructions[i].second] = wires[instructions[i].first.first] ^ wires[instructions[i].first.second];
                }
            }
        }
        j++;
    }
    if (wires.find(output) == wires.end()){
        return wires[output];
    }else {
        return -1;
    }
}

std::tuple<std::vector<std::pair<std::string, bool>>, std::vector<std::pair<std::string, bool>>, std::vector<std::pair<std::string, bool>>> get_wires(){
    std::vector<std::pair<std::string, bool>> x_wires, y_wires, z_wires;
    for (auto& [key, value] : wires){
        if (key[0] == 'x'){
            x_wires.push_back({key, value});
        } else if (key[0] == 'y'){
            y_wires.push_back({key, value});
        } else if (key[0] == 'z'){
            z_wires.push_back({key, value});
        }
    }
    std::sort(x_wires.begin(), x_wires.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
    });
    std::sort(y_wires.begin(), y_wires.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
    });
    std::sort(z_wires.begin(), z_wires.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
    });

    return std::make_tuple(x_wires, y_wires, z_wires);
}


bool is_instruction_expected(std::vector<std::string> inputs, std::string){

}





void check_instructions(){
    auto [x_wires, y_wires, z_wires] = get_wires();

    std::string and_result;
    std::string or_result;
    std::string xor_result;
    std::pair<std::pair<std::string, std::string>, std::string> xor_instruction;

    for (size_t i = 0; i < x_wires.size(); i++) {
        if (i == 0){
            std::unordered_map<std::string, bool> custom_wire = {{ x_wires[i].first, 0}, };
            
        }
        
        
    }
}


int main() {
    long long int count1=0, count2=0;
    
    // Read input file
    std::ifstream input("full_input.txt");
    std::string line;
    while (std::getline(input, line) && line.size()) {
        std::regex pattern_initial(R"(([a-zA-Z0-9]+): (\d))");
        std::smatch match;
        
        std::sregex_iterator begin(line.begin(), line.end(), pattern_initial);
        match = *begin;
        std::cout << match.str(1) << " " << match.str(2) << std::endl;
        wires[match.str(1)] = (match.str(2) == "1");
    }

    

    while (std::getline(input, line)) {
        std::regex pattern_instructions(R"(([a-zA-Z0-9]+) (\w+) ([a-zA-Z0-9]+) -> ([a-zA-Z0-9]+))");
        std::smatch match;
        std::sregex_iterator begin(line.begin(), line.end(), pattern_instructions);
        match = *begin;
        if (match.str(2) == "AND"){
            and_instructions.push_back({{match.str(1), match.str(3)}, match.str(4)});
        } else if (match.str(2) == "OR"){
            or_instructions.push_back({{match.str(1), match.str(3)}, match.str(4)});
        } else if (match.str(2) == "XOR"){
            xor_instructions.push_back({{match.str(1), match.str(3)}, match.str(4)});
        }
    }

    input.close();

    std::cout << "Instructions loaded" << std::endl;
    for (auto& [key, value] : wires){
        std::cout << key << " " << value << std::endl;
    }

    for (auto& pair : and_instructions){
        std::cout << pair.first.first << " AND " << pair.first.second << " -> "<< pair.second << std::endl;
    }

    for (auto& pair : or_instructions){
        std::cout << pair.first.first << " OR " << pair.first.second << " -> "<< pair.second << std::endl;
    }

    for (auto& pair : xor_instructions){
        std::cout << pair.first.first << " XOR " << pair.first.second << " -> "<< pair.second << std::endl;
    }


    bool missing = true;
    while (missing){
        missing = false;
        missing |= run_instructions(and_instructions, 0);
        missing |= run_instructions(or_instructions, 1);
        missing |= run_instructions(xor_instructions, 2);
    }

    std::cout << "Instructions executed" << std::endl;
    std::vector<std::pair<std::string, bool>> z_wires;
    for (auto& [key, value] : wires){
        //std::cout << key << " " << value << std::endl;
        if (key[0] == 'z'){
            z_wires.push_back({key, value});
        }
    }

    std::sort(z_wires.begin(), z_wires.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
    });

    long long int number = 0;
    for (size_t i = z_wires.size()-1; i < z_wires.size(); i--){
        //std::cout << z_wires[i].second << std::endl;
        number += z_wires[i].second * pow(2, i);
    }



    check_instructions(and_instructions, or_instructions, xor_instructions);

    
    

    std::cout << "Result 1: " << number << std::endl;
    std::cout << "Result 2: " << count2 << std::endl;

    std::cout << "Challenge completed successfully!" << std::endl;

    return 0;
}
