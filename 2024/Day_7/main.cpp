#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <functional>
#include <unordered_set>

int exponential(int n, int power){
    int result = 1;
    if (power < 1){
        return 1;
    }
    for(size_t i=0; i<power;i++){
        result *= n;
    }
    return result;
}


int main() {
    int count2, multiplier, temp;
    long long int sum = 0, count1=0, number, ref;
    std::vector<int> numbers;

    char seperator;


    // Read input file
    std::ifstream input("full_input.txt");
    std::string line;
    while (std::getline(input, line)) {
        numbers.clear();

        std::istringstream lineStream(line);
        lineStream >> ref;
        lineStream >> seperator;
        while (lineStream >> number){
            numbers.push_back(number);
        }
        
        for (size_t i = 0; i < exponential(3, numbers.size() - 1) ; i++){
            sum = numbers[0];
            size_t combination = i;
            size_t j = 1;
            while(j < numbers.size()){
                if (sum > ref){
                    break;
                }
                if (false){
                    if (combination & 1) { // Check the least significant bit
                        sum *= numbers[j];
                    }else{
                        sum += numbers[j];
                    }
                    combination >>= 1; // Shift right to process the next bit
                }
                if (combination %3 == 0) { // Check the least significant bit
                    sum *= numbers[j];
                }else if (combination %3 == 1){
                    sum += numbers[j];
                }else{
                    temp = numbers[j];
                    multiplier = 1;
                    while (temp > 0) {
                        multiplier *= 10;
                        temp /= 10;
                    }
                    sum = sum * multiplier + numbers[j];
                }
                combination /= 3; // Shift right to process the next bit
                ++j;
                
            }
            if (sum==ref){
                count1 += ref;
                std::cout << "Result 1: " << count1 << std::endl;
                break;
            }
        }
    }
    input.close();
    


    

    std::cout << "Result 1: " << count1 << std::endl;
    std::cout << "Result 2: " << count2 << std::endl;

    std::cout << "Challenge completed successfully!" << std::endl;

    return 0;
}
