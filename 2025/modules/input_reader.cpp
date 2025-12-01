#include <iostream>
#include <fstream>
#include "input_reader.hpp"

using namespace std;

vector<string> get_file_input(string file_path){
    vector<string> lines;
    ifstream file(file_path);
    if (file.is_open()){
        string line;
        while (getline(file, line)){
            lines.push_back(line);
        }
    }
    file.close();
    return lines;
}