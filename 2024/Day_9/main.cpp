#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <functional>
#include <unordered_set>

void print_memory(std::vector<int> memory){
    std::cout << "Memory: ";
    for (size_t i = 0; i<memory.size(); i++){
        std::cout << memory[i] << " ";
    }
    std::cout << std::endl;
}


int main() {
    int last_occupied_memory;
    long long int checksum =0;
    std::vector<int> memory = {};
    std::vector<int> unmoved_files = {};


    // Read input file
    std::ifstream input("full_input.txt");
    std::string line;
    if (std::getline(input, line)) {
        for (size_t i =0; i<line.size(); i++){
            memory.push_back(line[i] - '0');
        }
    }
    input.close();
    
    if (false){
        last_occupied_memory = (memory.size()/2)*2;
        int i=0, j=0;
        while(i<=last_occupied_memory){
            if (i%2){
                while(memory[i] > 0 && i < last_occupied_memory){
                    if (!memory[last_occupied_memory]){
                        last_occupied_memory -= 2;
                        continue;
                    }
                    memory[last_occupied_memory]--;
                    memory[i]--;
                    checksum += j * last_occupied_memory/2;
                    j++;
                }
            }else{
                while(memory[i]>0){
                    memory[i]--;
                    checksum += j * i/2;
                    j++;
                }
            }
            i++;
        }
    }

    for (size_t i = 0; i< memory.size(); i+=2){
        unmoved_files.push_back(i);
    }
    int last = 0, last_blocks, last_index =0 ;
    int i=0, j=0;
    while(i<=memory.size()){
        std::cout << i << " out of " << memory.size() << std::endl;
        //print_memory(memory);
        if (i%2){
            last = unmoved_files.size()-1;
            last_index = unmoved_files[last];
            last_blocks = memory[last_index];
            while(memory[i] > 0 && i < last_index){
                if (last_blocks > memory[i] || last_blocks == 0){
                    last--;
                    last_index = unmoved_files[last];
                    last_blocks = memory[unmoved_files[last]];
                    continue;
                }
                if (std::count(unmoved_files.begin(), unmoved_files.end(), last_index)){
                    unmoved_files.erase(unmoved_files.begin() + last);
                }
                last_blocks--;
                memory[i]--;
                checksum += j * last_index/2;
                //std::cout << "j: " << j << " i: " << last_index << " j*i/2=" << j * last_index/2 << " Checksum: " << checksum << std::endl;
                j++;
            }
            if(memory[i]){
                j+=memory[i];
            }
        }else{
            while(memory[i]>0){
                memory[i]--;
                if (std::count(unmoved_files.begin(), unmoved_files.end(), i)){
                    checksum += j * i/2;
                    //std::cout << "j: " << j << " i: " << i << " j*i/2=" << j * i/2 << " Checksum: " << checksum << std::endl;
                }
                j++;
            }
        }
        i++;
    }
    std::cout << "Result 1: " << checksum << std::endl;

    std::cout << "Challenge completed successfully!" << std::endl;

    return 0;
}
