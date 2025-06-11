#include "WorldMap.h"
#include <fstream>
#include <isstream>
#include <iostream>

void WorldMap::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);

    if (in.is_open()) {
        std::string line;
        while (getline(in, line)) {
            std::istringstream iss(line);
            char type;
            std::string name;
            iss >> type >> name;

            if (type == 'U') {
                int price, upgrade_price;
                iss >> price >> upgrade_price;
                std::vector<int> fines(5);
                for (int& fine : fines) iss >> fine;
                units_.emplace_back(std::make_unique<UpgradableUnit>(name, price, upgrade_price, fines));
            }
            else if (type == 'C') {
                int price, fine;
                iss >> price >> fine;
                units_.emplace_back(std::make_unique<CollectableUnit>(name, price, fine));
            }
            else if (type == 'R') {
                int price, fine;
                iss >> price >> fine;
                units_.emplace_back(std::make_unique<RandomCostUnit>(name, price, fine));
            }
            else if (type == 'J') {
                units_.emplace_back(std::make_unique<JailUnit>(name));
            }
        }
        in.close();
    }
    
}

MapUnit* WorldMap::getUnit(int index) const {
    if (index < 0 || index >= (int)units_.size()) return nullptr;
    return units_[index].get();
}

size_t WorldMap::size() const {
    return units_.size();
}

void WorldMap::printMap() const {
    for (size_t i = 0; i < units_.size(); ++i) {
        std::cout << "[" << i << "] ";
        units_[i]->printStatus();
    }
}