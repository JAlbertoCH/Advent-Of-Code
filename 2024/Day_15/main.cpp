#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <functional>
#include <unordered_set>

std::vector<std::vector<size_t>> map;


void print_table(){
    for (size_t y = 0; y<map.size();y++){
        for (size_t x = 0; x<map[y].size();x++){
            if (map[y][x] == 1){
                std::cout << '#';
            }else if(map[y][x] == 0){
                std::cout << '.';
            }else if(map[y][x] == 2){
                std::cout << '[';
            }else if(map[y][x] == 3){
                std::cout << '@';
            }else if(map[y][x] == 4){
                std::cout << ']';
            }
            
        }
        std::cout << std::endl;
    }
    std::cout<<std::endl;
}

bool is_pushable(std::vector<int> object_location, std::vector<int> direction){
    if (map[object_location[1]][object_location[0]] == 1) {
        return false;
    }else if (map[object_location[1]][object_location[0]] == 3){
        if (!is_pushable({object_location[0] + direction[0], object_location[1] + direction[1]} , direction)){
            return false;
        }
    }else if(map[object_location[1]][object_location[0]] == 2 || map[object_location[1]][object_location[0]] == 4){
        int vangard = 3 - (int)(map[object_location[1]][object_location[0]]);
        int box_twin = object_location[0] + vangard;
        
        if (direction[1] && (!is_pushable({object_location[0], object_location[1] + direction[1]} , direction) || !is_pushable({box_twin, object_location[1] + direction[1]} , direction))){
            return false;
        }else if(direction[0] && !is_pushable({object_location[0] + vangard * (vangard == direction[0]) + direction[0], object_location[1]} , direction)){
            return false;
        }
    }
    return true;
}

bool push_object(std::vector<int> object_location, std::vector<int> direction){
    if (map[object_location[1]][object_location[0]] == 1) {
        return false;
    }else if (map[object_location[1]][object_location[0]] == 3){
        if (!push_object({object_location[0] + direction[0], object_location[1] + direction[1]} , direction)){
            return false;
        }
        map[object_location[1] + direction[1]][object_location[0] + direction[0]] = map[object_location[1]][object_location[0]];
        map[object_location[1]][object_location[0]] = 0;
    }else if(map[object_location[1]][object_location[0]] == 2 || map[object_location[1]][object_location[0]] == 4){
        int vangard = 3 - (int)(map[object_location[1]][object_location[0]]);
        int box_twin = object_location[0] + vangard;
        
        if (!is_pushable(object_location, direction)){
            return false;
        }

        int first_side_to_move = object_location[0] + vangard * (vangard == direction[0]);
        int second_side_to_move = object_location[0] + vangard * (vangard != direction[0]);

        if (direction[0]) push_object({first_side_to_move + direction[0], object_location[1]}, direction);
        if (direction[1]){
            push_object({first_side_to_move, object_location[1] + direction[1]}, direction);
            push_object({second_side_to_move, object_location[1] + direction[1]}, direction);
        } 

        map[object_location[1] + direction[1]][ first_side_to_move + direction[0]]= map[object_location[1]][first_side_to_move];
        map[object_location[1]][first_side_to_move]= 0;

        map[object_location[1] + direction[1]][second_side_to_move + direction[0]]= map[object_location[1]][second_side_to_move];
        map[object_location[1]][second_side_to_move]= 0;
    }
    //std::cout<< map[object_location[1] + direction[1]][object_location[0] + direction[0]] <<" "<< object_location[0] << ","<< object_location[1] <<std::endl;
    //print_table();
    return true;
}




int main() {
    int count1=0, count2=0;

    std::vector<int> position(2), direction(2);
    int width, height;
    int y = 0;


    // Read input file
    std::ifstream input("full_input.txt");
    std::string line;
    while (std::getline(input, line) && line.size()) {
        if(!map.size()){
            width = line.size() * 2;
        }
        map.push_back(std::vector<size_t> (width, 0));
        for (int x=0; x<line.size(); x++){
            //std::cout<<x<< ": "<< line[x]<<std::endl;
            if (line[x] == '#'){
                map[y][2*x]=1;
                map[y][2*x+1]=1;
                continue;
            }else if (line[x] == '@'){
                map[y][2*x]=3;
                map[y][2*x+1]=0;
                position = {2*x, y};
            }else if (line[x] == 'O'){
                map[y][2*x]=2;
                map[y][2*x+1]=4;
            }else{
                map[y][2*x]=0;
                map[y][2*x+1]=0;
            }
        }
        y++;
    }


    while(std::getline(input, line)){
        for (int i=0; i<line.size(); i++){
            
            direction = {('>' == line[i])-('<' == line[i]), ('v' == line[i])-('^' == line[i])};
            //std::cout<<"Move:"<<i<< " Direction: "<< line[i] << " "<< direction[0]<< ","<< direction[1]<<" Position: "<< position[0] << ","<< position[1]<<std::endl;
            //print_table();
            if (push_object(position, direction)){
                position[0] += direction[0];
                position[1] += direction[1];
            }
        }
    }

    input.close();
    print_table();
    for (y = 0; y<map.size();y++){
        for (size_t x = 0; x<map[y].size();x++){
            if (map[y][x] == 2){
                //std::cout<<"Box: "<<x<< ","<< y<< " Coordinate: "<< 100 * y + y <<std::endl;
                count1 += 100 * y + x;
            }
        }
    }
    
    


    

    std::cout << "Result 1: " << count1 << std::endl;
    std::cout << "Result 2: " << count2 << std::endl;

    std::cout << "Challenge completed successfully!" << std::endl;

    return 0;
}
