#include <iostream>
#include <fstream>
#include <regex>


int main() {
    int count1 = 0, count2 = 0;
    int first, second;
    bool enabled = true;

    // Read input file
    std::ifstream input("full_input.txt");
    std::string line;
    while (std::getline(input, line)) {
        std::regex pattern(R"(mul\((\d+),(\d+)\)|do\(\)|don't\(\))"); // Combined pattern
        std::smatch match;

        // Iterate through matches
        std::sregex_iterator begin(line.begin(), line.end(), pattern);
        std::sregex_iterator end;

        for (std::sregex_iterator it = begin; it != end; ++it) {
            match = *it;
            std::cout << "Full match: " << match.str(0) << std::endl;
            if (match[1].matched && match[2].matched) {
                first = std::stoi(match.str(1));
                second = std::stoi(match.str(2));
                count1 += first * second;
                if (enabled){
                    count2 += first * second;
                }
            } else if ((match.str(0) == "do()" && !enabled) || (match.str(0) == "don't()" && enabled)) {
                enabled = !enabled;
            }
            
        }
        
        std::cout << "Finished line " << std::endl;
    }

    input.close();

    std::cout << "Result 1: " << count1 << std::endl;
    std::cout << "Result 2: " << count2 << std::endl;

    std::cout << "Challenge completed successfully!" << std::endl;

    return 0;
}
