#include <vector>
#include <string>

/**
* @class ProblemSolver
* @brief This class provides a framework for solving problems by defining methods for input, solving, and output.
*/
class ProblemSolver {
    public:
        void virtual get_input() = 0;
        void virtual solve() = 0;
        void virtual get_output() = 0;
};


/**
* @class Day1Solver
* @brief This is the problem of the first day of the Advent of Code
* To solve this problem, we convert the input into a list of integers (R is positive, L is negative) and then sum them up considering that
* a modular space of numbers. Each subquent sum is verified if it is 0 to count the times it happens.
* Regarding part 2, the solution now inclues times the dial passes 0.
*/
class Day1Solver : public ProblemSolver {
    private:
        std::vector<int> dial_movements;
        int dial_value;
        size_t zero_count;
        size_t zero_passes;
    public:
        void get_input() override;
        void solve() override;
        void get_output() override;
};

/**
* @class Day2Solver
* @brief This is the problem of the second day of the Advent of Code
* To solve this problem, I will read the input into ranges as pair of strings.
* The 
*/
class Day2Solver : public ProblemSolver {
    private:
        std::vector<std::pair<std::string, std::string>> ranges;
        long long int sum, complete_sum;
        int get_closest_duplicated_id(std::string bound, bool is_lower);
        long long int get_invalid_id(long long int duplicate);
        bool is_invalid_id(long long int id);
    public:
        void get_input() override;
        void solve() override;
        void get_output() override;
};

/**
* @class Day3Solver
* @brief This is the problem of day 3 of the Advent of Code
* To solve this problem, I will read the input into ranges as pair of strings.
* The 
*/
class Day3Solver : public ProblemSolver {
    private:
        std::vector<std::string> banks;
        long long int sum_part_1, sum_part_2;
    public:
        long long int get_joltage_from_bank(std::string bank, int digits=2);
        void get_input() override;
        void solve() override;
        void get_output() override;
};
