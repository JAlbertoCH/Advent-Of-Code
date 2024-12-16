#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <functional>


int main() {
    long long int max_x = 101, max_y = 103, duration = 100, t=0, skip_to_t = 500, quadrant;
    bool found = false;
    std::string user_input;

    
    std::vector<long long int> pos;
    std::vector<std::vector<std::vector<std::vector<long long int>>>> v_cleared(max_y, std::vector<std::vector<std::vector<long long int>>>(max_x, std::vector<std::vector<long long int>>{}));
    std::vector<std::vector<std::vector<std::vector<long long int>>>> v_next = v_cleared, v=v_cleared;
    std::vector<long long int> quadrants= {0,0,0,0};

    // Read input file
    std::ifstream input("full_input.txt");
    std::string line;
    while (std::getline(input, line)) {
        std::regex pattern_state(R"(p=(-?\d+),(-?\d+) v=(-?\d+),(-?\d+))"); 
        std::smatch match;

        // Iterate through matches
        std::sregex_iterator begin(line.begin(), line.end(), pattern_state);
        std::sregex_iterator end;

        if (begin != end) {
            match = *begin;
            pos = {stoi(match.str(1)) + stoi(match.str(3)) * duration, stoi(match.str(2)) + stoi(match.str(4)) * duration};

            pos[0] %= max_x;
            pos[1] %= max_y;

            if (pos[0] < 0) pos[0] += max_x;
            if (pos[1] < 0) pos[1] += max_y;

            v[stoi(match.str(2))][stoi(match.str(1))].push_back({stoi(match.str(3)), stoi(match.str(4))});
            //std::cout << "p: " << p[0] << "," << p[1] << std::endl;
            if (pos[0] != (max_x-1)/2 && pos[1] != (max_y-1)/2){
                quadrant = (pos[0]<max_x/2) + 2*(pos[1]<max_y/2);
                quadrants[quadrant]++;
                //std::cout << "quadrant: " << quadrant <<  std::endl;
            }
        }
    }
    input.close();

    while(!found){
        std::cout << "Duration:"<< t << std::endl;
        for (size_t y =0;y<v.size(); y++){
            for (size_t x =0;x<v[y].size(); x++){
                if (v[y][x].size()){
                    std::cout<< v[y][x].size();
                }else{
                    std::cout<< ".";
                }
            }
            std::cout<< std::endl;

        }
        std::cout<< std::endl;
        std::cout<< std::endl;

        std::cout << "Do you see a christmas tree? (y/n)"<< std::endl;
        std::cin >> user_input;
        if (user_input == "y"){
            found = true;
        }else{
            int consecutive=0, max_consecutive=0;
            while (t< skip_to_t || max_consecutive<10){
                max_consecutive=0;
                consecutive = 0;
                t++;
                v_next = v_cleared;
                for(size_t y=0;y<v.size(); y++){
                    for (size_t x =0;x<v[y].size(); x++){
                        for (size_t i=0; i<v[y][x].size();i++){
                            pos[0] = x + v[y][x][i][0];
                            pos[1] = y + v[y][x][i][1];

                            pos[0] %= max_x;
                            pos[1] %= max_y;

                            if (pos[0] < 0) pos[0] += max_x;
                            if (pos[1] < 0) pos[1] += max_y;

                            v_next[pos[1]][pos[0]].push_back(v[y][x][i]);
                        }
                    }
                }
                v = v_next;
                for(size_t y=0;y<v.size(); y++){
                    for (size_t x =0;x<v[y].size(); x++){
                        if (v[y][x].size()){
                            consecutive++;
                            if (consecutive > max_consecutive){
                                max_consecutive = consecutive;
                            }
                        }else{
                            consecutive = 0;
                        }
                    }
                }
                
            }
        }
    }
    
    std::cout << "Safety factor: " << quadrants[0]* quadrants[1]* quadrants[2]*quadrants[3] << std::endl;

    std::cout << "Challenge completed successfully!" << std::endl;

    return 0;
}
