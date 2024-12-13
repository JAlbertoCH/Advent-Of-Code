#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <functional>
#include <unordered_set>
#include <cmath>

bool is_colinear(std::vector<long double> array1, std::vector<long double> array2){
    return array1[0]/array1[1] == array2[0]/array2[1];
}


int main() {
    std::vector<long double> array_A, array_B, prize, moves={0,0};
    std::vector<std::vector<long double>> Matrix, inv_Matrix;
    long long int tokens = 0;

    // Read input file
    std::ifstream input("full_input.txt");
    std::string line;
    while (std::getline(input, line)) {
        std::regex pattern_button(R"(Button (\w): X\+(\d+), Y\+(\d+))"); // Combined pattern
        std::regex pattern_prize(R"(Prize: X=(\d+), Y=(\d+))"); // Combined pattern
        std::smatch match;

        // Iterate through matches
        std::sregex_iterator begin(line.begin(), line.end(), pattern_button);
        std::sregex_iterator end;

        if (begin != end) {
            match = *begin;
            if (match.str(1) == "A"){
                array_A = {std::stod(match.str(2)), std::stod(match.str(3))};
            }else if (match.str(1) == "B"){
                array_B = {std::stod(match.str(2)), std::stod(match.str(3))};
            }
        }

        begin = std::sregex_iterator(line.begin(), line.end(), pattern_prize);
        if (begin != end) {
            match = *begin;
            prize = {std::stod(match.str(1))+10000000000000, std::stod(match.str(2))+10000000000000};
            if(is_colinear(array_A, array_B)){
                std::cout << "Colinear" << std::endl;
            }else{
                Matrix = {
                    {array_A[0] - 3*array_B[0], array_B[0]},
                    {array_A[1] - 3*array_B[1], array_B[1]}
                    };


                long double det = Matrix[0][0]*Matrix[1][1] - Matrix[0][1]*Matrix[1][0];
                inv_Matrix = {{Matrix[1][1], -Matrix[0][1]}, {-Matrix[1][0], Matrix[0][0]}};
                moves[0] = inv_Matrix[0][0] * prize[0] + inv_Matrix[0][1] * prize[1];
                moves[1] = inv_Matrix[1][0] * prize[0] + inv_Matrix[1][1] * prize[1];
                moves[0] /= det;
                moves[1] /= det;
                if (std::fabs(moves[0] - std::round(moves[0]))<0.0001 && std::fabs(moves[1] - std::round(moves[1]))<0.00001 && (moves[0]>=0.0) &&  ((moves[1]-3*moves[0])>=0.0)){
                    tokens += moves[1];
                }
            }
        }


    }
    input.close();
    
    

    std::cout << "tokens: " << tokens << std::endl;

    std::cout << "Challenge completed successfully!" << std::endl;

    return 0;
}
