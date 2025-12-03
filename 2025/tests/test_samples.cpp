#include <gtest/gtest.h>
#include "../modules/problem_solver.hpp"


using namespace std;


TEST(Day3, SampleTest_test_joltage_from_bank_part_1) {
    vector<string> sample_bank = {"987654321111111", "811111111111119", "234234234234278", "818181911112111"};
    vector<int> expected_joltage = {98, 89, 78, 92};
    long long int joltage;

    for (size_t i = 0; i < sample_bank.size(); i++) {
        Day3Solver solver;
        joltage = solver.get_joltage_from_bank(sample_bank[i]);
        EXPECT_EQ(joltage, expected_joltage[i]) << "Joltage calculation failed for bank: " << sample_bank[i] << ". Expected: " << expected_joltage[i] << ". Got: "<< joltage <<endl;
    }
}

TEST(Day3, SampleTest_test_joltage_from_bank_part_2) {
    vector<string> sample_bank = {"987654321111111", "811111111111119", "234234234234278", "818181911112111"};
    vector<long long int> expected_joltage = {987654321111, 811111111119, 434234234278, 888911112111};
    long long int joltage;

    for (size_t i = 0; i < sample_bank.size(); i++) {
        Day3Solver solver;
        joltage = solver.get_joltage_from_bank(sample_bank[i], 12);
        EXPECT_EQ(joltage, expected_joltage[i]) << "Joltage calculation failed for bank: " << sample_bank[i] << ". Expected: " << expected_joltage[i] << ". Got: "<< joltage <<endl;
    }
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}