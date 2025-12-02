#include "problem_solver.hpp"
#include "input_reader.hpp"
#include <iostream>
#include <regex>
#include <cmath>

using namespace std;



void Day1Solver::get_input() {
    // The input for the first day is the the contents of the input file: input_day_1.txt
    // To interpret the data from the file, we will convert each line into an integer.
    // The integer is positive if the first letter is 'R' and negative if the first letter is 'L'.

    vector<string> lines = get_file_input("2025/inputs/input_day_1.txt");
    string dial_movement;

    for (size_t i = 0; i < lines.size(); i++){
        dial_movement = lines[i];
        if (dial_movement[0] == 'R'){
            dial_movements.push_back(stoi(dial_movement.substr(1)));
        } else if (dial_movement[0] == 'L'){
            dial_movements.push_back(-stoi(dial_movement.substr(1)));
        }
    }

    // Addtionally, the dial must be initialized to 50 and the zero count to 0.
    dial_value = 50;
    zero_count = 0;
    zero_passes = 0;
}

void Day1Solver::solve() {
    // To solve the problem, we will sum up the dial movements and count the number of times the dial value is 0.
    int full_rotations, dial_movement;
    for (size_t i = 0; i < dial_movements.size();  i++){
        dial_movement = dial_movements[i];
        full_rotations = abs(dial_movement / 100);
        dial_movement = dial_movement % 100;
        
        dial_value = (dial_value + dial_movement) % 100;
        
        if (dial_value == 0){
            // The dial hit zero.
            zero_count++;
        }else if (dial_value + 100 * (dial_value < 0)  - dial_movement < 0 || dial_value + 100 * (dial_value < 0)  - dial_movement > 100){
            // The dial has passed through zero.
            zero_passes++;
        }
        if (full_rotations > 0){
            // Full rotations
            zero_passes += abs(full_rotations) - (dial_movement == 0 && dial_value == 0 ? 1 : 0);
        }
    }
}

void Day1Solver::get_output(){
    // The final value is the zero count.
    cout << "Day 1 Solution " << endl;
    cout << "Password (Part 1): " << zero_count << endl;
    cout << "Password (Part 2): " << zero_count + zero_passes << endl;
}




void Day2Solver::get_input() {
    // The input for the second day is the the contents of the input file: input_day_2.txt
    // To interpret the data from the file, we will convert each line into a pair of strings representing the ranges.

    vector<string> lines = get_file_input("2025/inputs/input_day_2.txt");
    string line = lines[0];

    regex pattern(R"((\d+)-(\d+))"); // Combined pattern
        smatch match;
    
    // Iterate through matches
    std::sregex_iterator begin(line.begin(), line.end(), pattern);
    std::sregex_iterator end;

    for (std::sregex_iterator it = begin; it != end; ++it) {
        match = *it;
        ranges.push_back({match.str(1), match.str(2)});
    }

    // Addtionally, the sum must be initialized to 0.
    sum=0;
    complete_sum=0;
}

void Day2Solver::solve() {
    // To solve the problem, we will first calculate all invalid IDs within a range.
    int closest_lower_bound, closest_upper_bound;
    long long int lower_bound_int, upper_bound_int;
    for (size_t i = 0; i < ranges.size();  i++){
        //Find lengths of ranges:
        cout << "Processing range: " << ranges[i].first << "-" << ranges[i].second << endl;
        closest_lower_bound = get_closest_duplicated_id(ranges[i].first, true);
        closest_upper_bound = get_closest_duplicated_id(ranges[i].second, false);

        while (closest_lower_bound <= closest_upper_bound){
            sum += get_invalid_id((long long) closest_lower_bound);
            closest_lower_bound++;
        }

        lower_bound_int = stol(ranges[i].first);
        upper_bound_int = stol(ranges[i].second);

        for (long long int id = lower_bound_int; id <= upper_bound_int; id++){
            if (is_invalid_id(id)){
                complete_sum += id;
            }
        }
    }
}

/**
 * @brief This function finds the closest invalid ID to the given bound.
 * @param bound The bound ID as a string.
 * @param is_lower A boolean indicating if the bound is a lower bound (true) or upper bound (false).
 */
int Day2Solver::get_closest_duplicated_id(string bound, bool is_lower) {
    size_t order_bound = bound.length();
    long int bound_value = stol(bound), order = pow(10, order_bound/2);
    int closest_duplicated_id;

    if (order_bound % 2 == 0){ // If even length
        closest_duplicated_id = stoi(bound.substr(0, order_bound / 2));;
        if (is_lower && closest_duplicated_id * order + closest_duplicated_id < bound_value) {
            closest_duplicated_id += 1;
            return closest_duplicated_id;
        } else if (!is_lower && closest_duplicated_id * order + closest_duplicated_id > bound_value) {
            closest_duplicated_id -= 1;
            return closest_duplicated_id;
        } else {
            return closest_duplicated_id;
        }
    } else { // Id odd length
        if (is_lower){
            order_bound += 1; // Make it even
            return order;
        } else {
            order_bound += 1; // Make it even
            return order - 1;
        }
    }
}

/**
 * @brief This function calculates the invalid ID from the duplicate value.
 * @param duplicate The duplicate value.
 */
long long int Day2Solver::get_invalid_id(long long int duplicate) {
    int order = 0;
    while ((duplicate / int(pow(10, order))) > 0){
        order++;
    }
    return duplicate * pow(10, order) + duplicate;
}

bool Day2Solver::is_invalid_id(long long int id_int) {
    string id = to_string(id_int);
    size_t is_length = id.length();
    string duplicate_number;
    bool is_invalid = false;

    for (size_t i = 1; i < is_length / 2 + 1; i++){
        string duplicate_number = id.substr(0, i);
        is_invalid = true;
        for (size_t j = i; j < is_length; j += i){
            if (id.substr(j, i) != duplicate_number){
                is_invalid = false;
                break;
            }
        }
        if (is_invalid){
            return true;
        }
    }
    return false;
}

void Day2Solver::get_output(){
    // The final value is the zero count.
    cout << "Day 2 Solution " << endl;
    cout << "Sum of invalid IDs (Part 1): " << sum << endl;
    cout << "Sum of invalid IDs (Part 2): " << complete_sum << endl;
}