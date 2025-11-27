#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <functional>
#include <unordered_set>

void printLans(const std::vector<std::unordered_set<std::string>>& lans) {
    for (const auto& lan : lans) {
        std::vector<std::string> sorted_lan(lan.begin(), lan.end());
        std::sort(sorted_lan.begin(), sorted_lan.end());
        for (const auto& item : sorted_lan) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    int count1=0, count2=0;
    std::unordered_map<std::string, std::vector<std::string>> network_map;
    std::vector<std::unordered_set<std::string>> network_triples;

    // Read input file
    std::ifstream input("full_input.txt");
    std::string line;
    while (std::getline(input, line) && line.size()) {
        std::regex pattern_netconnect(R"((\w+)\-(\w+))");
        std::smatch match;

        // Iterate through matches
        std::sregex_iterator begin(line.begin(), line.end(), pattern_netconnect);
        std::sregex_iterator end;

        if (begin != end) {
            match = *begin;
            if (network_map.find(match.str(1)) == network_map.end()){
                network_map[match.str(1)] = std::vector<std::string>();
            }
            if (network_map.find(match.str(2)) == network_map.end()){
                network_map[match.str(2)] = std::vector<std::string>();
            }
            network_map[match.str(1)].push_back(match.str(2));
            network_map[match.str(2)].push_back(match.str(1));
        }
    }
    input.close();

    std::vector<std::unordered_set<std::string>> lans;
    std::unordered_set<std::string> inserted_computers;
    std::unordered_set<std::string> new_lan;
    int counter = 0;
    for (auto& [key, value] : network_map){
        std::cout << counter << " out of "<< network_map.size()<< std::endl;
        for (size_t i = 0; i< lans.size(); i++){
            bool in_lan = true;
            for (auto& computer : lans[i]){
                if (std::find(value.begin(), value.end(), computer) == value.end()){
                    in_lan = false;
                    break;
                }
            }
            if (in_lan){
                new_lan = lans[i];
                new_lan.insert(key);
                lans.push_back(new_lan);
            }
        }

        
        for (auto& v : value){
            if (inserted_computers.find(v) != inserted_computers.end()){
                continue;
            }
            new_lan.clear();
            new_lan.insert(key);
            new_lan.insert(v);
            lans.push_back(new_lan);
            
        }
        inserted_computers.insert(key);
        counter++;
    }

    printLans(lans);
    int max_lan_size = 0;
    std::unordered_set<std::string> max_lan;
    for (auto& lan : lans){
        if (max_lan_size < lan.size()){
            max_lan_size = lan.size();
            max_lan = lan;
        }
    }
    
    std::vector<std::string> sorted_lan(max_lan.begin(), max_lan.end());
    std::sort(sorted_lan.begin(), sorted_lan.end());
    
    for (const auto& lan : sorted_lan){
        std::cout << lan << ",";
    }
    std::cout << std::endl;
    

    std::cout << "Result 1: " << count1 << std::endl;
    std::cout << "Result 2: " << max_lan_size << std::endl;

    std::cout << "Challenge completed successfully!" << std::endl;

    return 0;
}
