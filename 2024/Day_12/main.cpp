#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <functional>
#include <unordered_map> 

struct Region{
    int area;
    int perimeter;
    int sides;
    std::vector<int> boundary;
    std::vector<int> next_boundary;
};

int get_index(std::vector<int> vector, int value){
    auto it = std::find(vector.begin(), vector.end(), value);
    if (it != vector.end()) {
        return std::distance(vector.begin(), it);
    }
    return -1;
};

int find_region_by_boundary(std::vector<Region> region_list, int boundary_position){
    Region region;
    std::vector<int>::iterator it;
    for(int j=0; j<region_list.size(); j++){
        region = region_list[j];
        it = std::find(region.boundary.begin(), region.boundary.end(), boundary_position);
        if (it != region.boundary.end()) {
            return j;
        }
    }
    return -1;
};

int get_extra_sides_number(Region region, int added_position){

    int sides = 0;
    if (get_index(region.next_boundary, added_position-1) == -1){
        return 2*(get_index(region.boundary, added_position-1) != -1) + 2*(get_index(region.boundary, added_position+1) != -1);
    }else if (get_index(region.boundary, added_position) != -1){
        return -2 + 2*(get_index(region.boundary, added_position+1) != -1);
    }
    
    return 2*(get_index(region.boundary, added_position-1) != -1);
    
};


int main() {
    std::unordered_map<char, std::vector<Region>> regions;

    int y=0, count1 = 0, count2 = 0, current_Region, prev_Region;
    Region region;
    bool up, side;
    

    // Read input file
    std::ifstream input("full_input.txt");
    std::string line;
    while (std::getline(input, line)) {
        for (int i=0; i<line.size(); i++){
            side = (i!=0 && line[i-1]==line[i]);
            up = false;
            if (regions.count(line[i])){
                std::vector<int>::iterator it;
                for(int j=0; j<regions[line[i]].size(); j++){
                    region = regions[line[i]][j];
                    it = std::find(region.boundary.begin(), region.boundary.end(), i);
                    if (it != region.boundary.end()) {
                        current_Region = j;
                        up=true;
                        break;
                    }
                }
            }
            if (!side && !up){
                region = Region {1,4,4,std::vector<int> {}, std::vector<int> {i}};
                current_Region = regions[line[i]].size();
                regions[line[i]].push_back(region);
            }else{
                //std::cout<< up << " ";
                regions[line[i]][current_Region].area++;
                regions[line[i]][current_Region].perimeter+=4-2*(up+side);
                regions[line[i]][current_Region].next_boundary.push_back(i);
                if (side && up && prev_Region!= current_Region){
                    regions[line[i]][current_Region].area += regions[line[i]][prev_Region].area;
                    regions[line[i]][current_Region].perimeter += regions[line[i]][prev_Region].perimeter;
                    regions[line[i]][current_Region].sides += regions[line[i]][prev_Region].sides;
                    for(size_t j = 0; j<regions[line[i]][prev_Region].next_boundary.size();j++){
                        regions[line[i]][current_Region].next_boundary.push_back(regions[line[i]][prev_Region].next_boundary[j]);
                    }
                    for(size_t j = 0; j<regions[line[i]][prev_Region].boundary.size();j++){
                        regions[line[i]][current_Region].boundary.push_back(regions[line[i]][prev_Region].boundary[j]);
                    }
                    if (prev_Region<current_Region){
                        current_Region--;
                    }
                    regions[line[i]].erase(regions[line[i]].begin() + prev_Region);
                }
                regions[line[i]][current_Region].sides+=get_extra_sides_number(regions[line[i]][current_Region], i);

            }
            prev_Region = current_Region;
        }
        
        for (std::unordered_map<char, std::vector<Region>>::iterator it = regions.begin(); it != regions.end(); ++it) {
            for (size_t i = 0; i < it->second.size(); i++){
                it->second[i].boundary = it->second[i].next_boundary;
                it->second[i].next_boundary={};
                if ((it->second[i].boundary.size())){
                    std::cout<< it->second[i].area << "-"<<it->second[i].sides<< " ";
                }
            }
        }
        std::cout<< std::endl;
    }
    input.close();

    for (std::unordered_map<char, std::vector<Region>>::iterator it = regions.begin(); it != regions.end(); ++it) {
        for (size_t i = 0; i < it->second.size(); i++){
            count1 += it->second[i].area * it->second[i].perimeter;
            count2 += it->second[i].area * it->second[i].sides;
        }
    }

    std::cout << "Result 1: " << count1 << std::endl;
    std::cout << "Result 2: " << count2 << std::endl;

    std::cout << "Challenge completed successfully!" << std::endl;

    return 0;
}
