#include <iostream>
#include <fstream>
#include <string>
#include <filesystem> // C++17 or later
#include <sstream>
#include <vector>
#include <algorithm>

bool check_difference(int direction, int difference) {
    if (direction == 0) {
        return 0 < abs(difference) && abs(difference) < 4;
    }
    return direction * difference > 0 && direction * difference < 4;
}

bool validate_array(std::vector<int> array){

    int direction=0, difference;

    for (size_t i = 1; i < array.size(); ++i) {
        
        difference = array[i]-array[i-1];
        if (check_difference(direction, difference)) {
            if (direction == 0) {
                direction = (difference > 0) - (difference < 0);
            }
        }else{
            return false;
        }
    }
    return true;
}



int main() {
    int count1 = 0;
    int count2 = 0;
    int number;
    std::vector<int> array;
    std::vector<int> result;

    // Read input file
    std::ifstream input("input copy.txt");
    std::string line;
    while (std::getline(input, line)) {
        std::istringstream lineStream(line);
        array.clear();
         

        while (lineStream >> number) {
            array.push_back(number);
        }

        if (validate_array(array)){
            count1++;
            count2++;
        }else
        {
            for (size_t i = 0; i < array.size(); ++i) {
                result.clear();

                // Iterate through the original vector
                for (size_t j = 0; j < array.size(); ++j) {
                    if (j != i) {
                        result.push_back(array[j]); // Copy all except the one at the index
                    }
                    
                }
                if (validate_array(result)){
                    count2++;
                    break;
                }
                std::cout << std::endl;
            }
            
        }
        std::cout << "Finished line " << std::endl;
    }

    input.close();

    std::cout << "Ammount of slightly strictly monotone series: " << count1 << std::endl;
    std::cout << "Ammount of slightly strictly monotone series(removing 1): " << count2 << std::endl;

    std::cout << "Challenge completed successfully!" << std::endl;

    return 0;
}
