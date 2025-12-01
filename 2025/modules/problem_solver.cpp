#include "problem_solver.hpp"
#include "input_reader.hpp"
#include <iostream>

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