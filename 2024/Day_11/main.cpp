#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <unordered_map> 

struct PairHash {
    std::size_t operator()(const std::pair<int, long double>& p) const {
        std::size_t h1 = std::hash<int>{}(p.first);       // Hash the integer
        std::size_t h2 = std::hash<long double>{}(p.second);  // Hash the double

        // Combine the hashes (using XOR and shifting)
        return h1 ^ (h2 << 1); // A simple but effective combination
    }
};

std::unordered_map<std::pair<int, long double>, long long int, PairHash> stone_count;

int order_of_magnitude(int number){
    int oom=0;
    while(number){
        oom++;
        number/=10;
    }
    return oom;
}

long long int get_stone_count_after_blink(int n, long double lognumber){
    //std::cout << n << std::endl;
    if (stone_count.count({n, lognumber})) return stone_count[{n, lognumber}];

    if (n == 0) return 1;
    if (lognumber < 0){
        stone_count[{n, lognumber}] = get_stone_count_after_blink(n-1, 0);
        return stone_count[{n, lognumber}];
    }
    
    if (!((long long int)lognumber % 2)){
        stone_count[{n, lognumber}] = get_stone_count_after_blink(n-1, log10(2024) + lognumber);
        return stone_count[{n, lognumber}];
    } 

    long long int division, remainder;
    long double stone;
    long long int number = lround(pow(10.0, lognumber));
    long long int half_number_power = (long long int) pow(10.0, (long long int) lognumber / 2 + 1);
    
    division = number / half_number_power;
    remainder = number % half_number_power;


    if (remainder<1){
        stone = -1;
    }else{
        stone = log10(remainder);
    }
    stone_count[{n, lognumber}] = get_stone_count_after_blink(n-1, log10(division)) + get_stone_count_after_blink(n-1, stone);
    return stone_count[{n, lognumber}];
}


int main() {
    long long int count1=0;
    long double number;
    

    // Read input file
    std::ifstream input("full_input.txt");
    std::string line;
    while (std::getline(input, line)) {
        std::istringstream lineStream(line);
        while (lineStream >> number) {
            std::cout<< number<< std::endl;
            count1 += get_stone_count_after_blink(75, log10(number));
        }
    }
    input.close();

    std::cout << "Result 1: " << count1 << std::endl;

    std::cout << "Challenge completed successfully!" << std::endl;

    return 0;
}
