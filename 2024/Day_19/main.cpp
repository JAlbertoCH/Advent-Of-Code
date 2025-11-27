#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <functional>
#include <unordered_set>
#include <queue>
#include <any>



std::vector<std::pair<std::any, bool>> patterns(5, std::pair<std::any, bool>{});
std::map<std::string, long long int> checked_patterns;

int get_color_id(char color){
    return  (color == 'u') + 2 * (color == 'b') + 3 * (color == 'r') + 4 * (color == 'g');
}

char get_color_from_id(int id){
    if (id == 0){
        return 'w';
    }else if (id == 1){
        return 'u';
    }else if (id == 2){
        return 'b';
    }else if (id == 3){
        return 'r';
    }else if (id == 4){
        return 'g';
    }
    return ' ';
}

long long int count_patterns(std::string line){
    if (!line.size()){
        return 1;
    }
    long long int count = 0;
    //std::cout<<line<<std::endl;
    std::vector<std::pair<std::any, bool>> current_pattern = patterns;
    for (size_t i = 0; i<line.size();i++){
        if (current_pattern[get_color_id(line[i])].second){
            if (checked_patterns.find(line.substr(i+1)) == checked_patterns.end()){
                checked_patterns[line.substr(i+1)] = count_patterns(line.substr(i+1));
            }
            if (checked_patterns[line.substr(i+1)]){
                count += checked_patterns[line.substr(i+1)];
            } 
        } 
        if (!current_pattern[get_color_id(line[i])].first.has_value()){
            break;
        }
        current_pattern=std::any_cast<std::vector<std::pair<std::any, bool>>>(current_pattern[get_color_id(line[i])].first);
    }
    std::cout<< count <<std::endl;
    return count;
}


std::vector<std::pair<std::any, bool>> add_pattern_to_patterns(std::string pattern, std::vector<std::pair<std::any, bool>> current_pattern){
    if (pattern.size()==1){
        if (!current_pattern[get_color_id(pattern[0])].first.has_value()){
            current_pattern[get_color_id(pattern[0])].first = std::vector<std::pair<std::any, bool>> (5, std::pair<std::any, bool>{});
        }
        current_pattern[get_color_id(pattern[0])].second = true;
    }else{
        if (!current_pattern[get_color_id(pattern[0])].first.has_value()){
            current_pattern[get_color_id(pattern[0])].first = std::vector<std::pair<std::any, bool>> (5, std::pair<std::any, bool>{});
            current_pattern[get_color_id(pattern[0])].second = false;
        }
        std::vector<std::pair<std::any, bool>> next_pattern = std::any_cast<std::vector<std::pair<std::any, bool>>>(current_pattern[get_color_id(pattern[0])].first);
        current_pattern[get_color_id(pattern[0])].first = add_pattern_to_patterns(pattern.substr(1), next_pattern);
    }
    return current_pattern;
}

void print_patterns(std::string pattern, std::vector<std::pair<std::any, bool>> current_pattern){
    for (size_t i = 0; i < current_pattern.size(); i++){
        if(current_pattern[i].second){
            std::cout << pattern<< get_color_from_id(i)<<std::endl;
        }
        if (current_pattern[i].first.has_value()){
            print_patterns(pattern + get_color_from_id(i), std::any_cast<std::vector<std::pair<std::any, bool>>>(current_pattern[i].first));
        }
    }
}



int main() {
    long long int count1=0, count2;

    // Read input file
    std::ifstream input("full_input.txt");
    std::string line;
    if (std::getline(input, line)) {
        
        std::regex pattern_coordinates(R"(\w+)");

        std::smatch match;

        // Iterate through matches
        std::sregex_iterator begin(line.begin(), line.end(), pattern_coordinates);
        std::sregex_iterator end;

        if (begin != end) {
            for (std::sregex_iterator it = begin; it!= end; it++){
                match = *it;
                std::string pattern = match.str(0);
                patterns = add_pattern_to_patterns(pattern, patterns);
            }
        }
        print_patterns("", patterns);
        
    }
    std::getline(input, line);
    int j =0;
    while(std::getline(input, line)){
        std::cout<< j <<std::endl;
        count1 += count_patterns(line);
        if (count1<0){
            break;
        }
        j++;
    }
    input.close();
    

    std::cout << "Result 1: " << count1 << std::endl;
    //std::cout << "Result 2: " << t<<"/"<< falling_bits.size()<<  "-"<< falling_bits[t-1][0]<< ","<<falling_bits[t-1][1]  << std::endl;

    std::cout << "Challenge completed successfully!" << std::endl;

    return 0;
}
