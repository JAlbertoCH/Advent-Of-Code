#include <iostream>
#include <fstream>
#include <regex>

int run_kernel_through_matrix(std::vector<std::string> kernel, std::vector<std::string> matrix){
    int rows = matrix.size();
    int cols = matrix[0].size();
    int kernelRows = kernel.size();
    int kernelCols = kernel[0].size();

    int matchCount = 0;
    bool match;
    int outputRows = rows - kernelRows + 1;
    int outputCols = cols - kernelCols + 1;
    
    
    for (int i = 0; i < outputRows; ++i) {
        for (int j = 0; j < outputCols; ++j) {
            match = true;
            
            for (int m = 0; m < kernelRows; ++m) {
                for (int n = 0; n < kernelCols; ++n) {
                    // Apply NXOR between the matrix and kernel values
                    if (matrix[i + m][j + n] != kernel[m][n] && kernel[m][n] != ' ') {
                        match = false;
                        break;
                    }
                }
                if (!match){
                    break;
                }
            }
            
            // Check if the number of matches meets the threshold
            if (match) {
                matchCount++;
            }
        }
    }
    return matchCount;
}


int main() {
    std::vector<std::string> matrix;
    std::vector<std::vector<std::string>> kernels_1 = {
        {"XMAS"},
        {"SAMX"},
        {"X","M","A","S"},
        {"S","A","M","X"},
        {"X   "," M  ","  A ","   S"},
        {"S   "," A  ","  M ","   X"},
        {"   X","  M "," A  ","S   "},
        {"   S","  A "," M  ","X   "}
    };
    std::vector<std::vector<std::string>> kernels_2 = {
        {"M M", " A ", "S S"},
        {"S M", " A ", "S M"},
        {"S S", " A ", "M M"},
        {"M S", " A ", "M S"}
    };

    int matches_1=0, matches_2=0;

    // Read input file
    std::ifstream input("full_input.txt");
    std::string line;
    while (std::getline(input, line)) {
        matrix.push_back(line);
    }
    input.close();

    for(size_t i; i < kernels_1.size(); i++)
        matches_1 += run_kernel_through_matrix(kernels_1[i], matrix);
    
    for(size_t i; i < kernels_2.size(); i++)
        matches_2 += run_kernel_through_matrix(kernels_2[i], matrix);
    

    std::cout << "Result 1: " << matches_1 << std::endl;
    std::cout << "Result 2: " << matches_2 << std::endl;

    std::cout << "Challenge completed successfully!" << std::endl;

    return 0;
}
