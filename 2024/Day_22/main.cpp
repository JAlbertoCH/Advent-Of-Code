#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <functional>

struct CustomHash
{
    std::size_t operator()(const std::vector<int>& position) const {
        // Combine the two integers using a common hash-combination technique
        return ((position[0] * 31 + position[1]) * 37 + position[2]) * 41 + position[3];
    }
};


int next_secret_number(int n){
    n ^= (n << 6);
    n &= 16777215;
    n ^= (n >> 5);
    n &= 16777215;
    n ^= (n << 11);
    n &= 16777215;
    return n;
}

int main() {
    long long int count1=0, count2=0, number, init, price, prev_price = -1;
    std::vector<int> sequence;
    std::unordered_map<std::vector<int>, int, CustomHash> buyer_sequences, sequences;

    // Read input file
    std::ifstream input("full_input.txt");
    std::string line;
    while (std::getline(input, line) && line.size()) {
        init = std::stoi(line);
        number = init;
        prev_price = number%10;
        buyer_sequences.clear();
        sequence.clear();
        for (size_t i =1; i<2000;i++){
            number = next_secret_number(number);
            price = number%10;

            if (sequence.size() < 4) {
                sequence.push_back(price-prev_price); // Add normally if there's space
                if (sequence.size() == 4){
                    //std::cout<<price<<std::endl;
                    buyer_sequences[sequence] = price;
                }
            } else {
                sequence.erase(sequence.begin()); // Remove the oldest element
                sequence.push_back(price-prev_price);   // Add the new element
                if (buyer_sequences.find(sequence) == buyer_sequences.end()){
                    buyer_sequences[sequence] = price;
                }
            }
            prev_price = price;
        }
        for (const auto& pair : buyer_sequences) {
            if (sequences.find(pair.first) == sequences.end()) {
                sequences[pair.first] = pair.second;
            }else{
                sequences[pair.first] += pair.second;
            }
        }
        count1 += number;
    }
    input.close();

    int max_price = 0;

    for (const auto& pair : sequences) {
        std::cout<< pair.first[0]<<","<< pair.first[1]<<","<< pair.first[2]<<","<< pair.first[3]<<" "<<pair.second<<std::endl;
        if (max_price < pair.second){
            sequence = pair.first;
            max_price = pair.second;
        }
    }
    
    
    std::cout<< sequence[0]<<","<< sequence[1]<<","<< sequence[2]<<","<< sequence[3]<<std::endl;
    std::cout << "Result 1: " << count1 << std::endl;
    std::cout << "Result 2: " << max_price << std::endl;

    std::cout << "Challenge completed successfully!" << std::endl;

    return 0;
}
