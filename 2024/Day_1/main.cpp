#include <iostream>
#include <fstream>
#include <string>
#include <filesystem> // C++17 or later
#include <sstream>
#include <vector>
#include <algorithm>

int main() {
    std::cout << "Current working directory: "
              << std::filesystem::current_path() << std::endl;

    // Read input file
    std::ifstream input("input.txt");
    if (!input.is_open()) {
        std::cerr << "Error: Could not open input.txt" << std::endl;
        return 1;
    }

    std::vector<int> array1; // First column values
    std::vector<int> array2; // Second column values

    std::string line;
    while (std::getline(input, line)) {
        std::istringstream lineStream(line);
        int number1, number2;
        if (lineStream >> number1 >> number2) {
            array1.push_back(number1);
            array2.push_back(number2);
        }
    }

    input.close();

    // Sort array1
    std::sort(array1.begin(), array1.end());

    // Sort array2
    std::sort(array2.begin(), array2.end());

    // Sum the absolute value of the differences
    int sumDiffs = 0;
    for (size_t i = 0; i < array1.size(); ++i) {
        sumDiffs = sumDiffs + abs(array1[i] - array2[i]);
    }

    std::cout << "Sum of the absolute value of the differences between the sorted arrays: " << sumDiffs << std::endl;

    std::cout << "Challenge completed successfully!" << std::endl;

    return 0;
}
