#include <fstream>
#include <iostream>
#include <regex>
#include <cmath>
#include <unordered_set>

// 148758992
std::vector<long long int> registers = {0,0,0}, init_registers;
std::vector<long long int> program, output;
size_t pointer=0;

long long int get_combo(size_t literal){
    //std::cout<< literal << " " << registers[0]<<std::endl;
    if (literal==7) return -1;
    if (literal >=4 && literal < 7) return registers[literal-4];
    return literal;
}

void run_opcode(size_t opcode, size_t literal, bool display){
    if (opcode == 0){
        long long int combo = get_combo(literal);
        if (combo == -1){
            return;
        }
        for (size_t i=0;i<combo;i++){
            registers[0] /= 2;
        }
        return;
    }else if (opcode == 1){
        registers[1] ^= literal;
        return;
    }else if (opcode == 2){
        long long int combo = get_combo(literal);
        if (combo < 0){
            //std::cout<< combo << " " << (combo % 8)<<std::endl;
            return;
        }
        registers[1] = (combo % 8);
        return;
    }else if (opcode == 3){
        if (registers[0]){
            pointer = literal - 2;
        }
        return;
    }else if (opcode == 4){
        registers[1] ^= registers[2];
        return;
    }else if (opcode == 5){
        long long int combo = get_combo(literal);
        if (combo == -1){
            return;
        }
        //if(display) std::cout<<registers[0]<< " ";
        if(display) std::cout<<(combo % 8)<<",";
        output.push_back(combo % 8);
        return;
    }else if (opcode == 6){
        long long int combo = get_combo(literal);
        if (combo == -1){
            return;
        }
        registers[1] = registers[0] >> combo;
        return;
    }else if (opcode == 7){
        int combo = get_combo(literal);
        if (combo == -1){
            return;
        }
        registers[2] = registers[0] >> combo;
        return;
    }
    
}


int main() {
    
    // Read input file
    std::ifstream input("full_input.txt");
    std::string line;
    while (std::getline(input, line)) {
        if (!line.size()) continue;

        std::regex pattern_register(R"(Register (\w): (\d+))"); 
        std::regex pattern_program(R"(Program: )"); 

        std::smatch match;

        // Iterate through matches
        std::sregex_iterator begin(line.begin(), line.end(), pattern_register);
        std::sregex_iterator end;

        if (begin != end) {
            match = *begin;
            if (match.str(1) == "A"){
                registers[0] = stoi(match.str(2));
            }else if (match.str(1) == "B"){
                registers[1] = stoi(match.str(2));
            }else if (match.str(1) == "C"){
                registers[2] = stoi(match.str(2));
            }
            continue;
        }

        
        if (std::regex_search(line, match, pattern_program)) {

            // Find all additional numbers after commas
            std::string remaining = match.suffix().str();
            std::regex number_pattern(R"((\d))"); // Pattern for single digits

            auto begin = std::sregex_iterator(remaining.begin(), remaining.end(), number_pattern);
            auto end = std::sregex_iterator();

            // Iterate and print the remaining numbers
            for (std::sregex_iterator i = begin; i != end; ++i) {
                std::smatch number_match = *i;
                program.push_back(stoi(number_match[1]));
            }

        }

        
    }
    input.close();

    long long int a, max_a;

    

    //long long int exp, next_output;
    std::vector<long long int> possibilities = {0}, new_possibilities;
    bool valid;
    for (size_t i=(program.size()-1); i<program.size();i--){
        a = 0;
        valid = false;
        
        for (a=0; a<8; a++){
            for (size_t k=0; k<possibilities.size();k++){
                //std::cout<<a+possibilities[k]<<std::endl;
                
                valid = true;
                output.clear();
                registers = {a+possibilities[k], 0, 0};
                for (pointer=0; pointer<program.size();pointer+=2){
                    run_opcode(program[pointer], program[pointer+1], false);
                }
                for(size_t j=0; j< output.size(); j++){
                    std::cout<< a+possibilities[k] <<  " " <<  program[program.size() -1 - j]<< " " << output[output.size() -1 - j]<< std::endl;
                    if (output[output.size() -1 - j] != program[program.size() -1 - j]){
                        valid = false;
                        break;
                    }
                }
                //std::cout<<valid<<std::endl;
                if (valid && a+possibilities[k]){
                    //std::cout<<i<<" "<<a+possibilities[k]<<std::endl;
                    new_possibilities.push_back(a+possibilities[k]);
                    if (i==0){
                        break;
                    }
                }
            }
            if (valid && i==0){
                break;
            }
        }
        std::cout<<valid<<std::endl;
        if (i!=0){
            for (size_t k=0; k<new_possibilities.size();k++){
                new_possibilities[k] *= 8;
                std::cout<<i<<" "<<new_possibilities[k]<<std::endl;
            }
        }
        
        possibilities = new_possibilities;
        new_possibilities.clear();

    }

    registers = {possibilities[0], 0, 0};
    for (pointer=0; pointer<program.size();pointer+=2){
        run_opcode(program[pointer], program[pointer+1], true);
    }
    std::cout<< std::endl;

    std::cout << "a: " << possibilities[0] << std::endl;
    //std::cout << "Result 2: " << count2 << std::endl;

    std::cout << "Challenge completed successfully!" << std::endl;

    return 0;
}
