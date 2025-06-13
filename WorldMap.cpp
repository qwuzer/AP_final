#include "WorldMap.h"
#include "player.h"
#include "map.h"
#include <fstream>
#include <sstream>
#include <iostream>

void WorldMap::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    int idx = 0;

    if (in.is_open()) {
        std::string line;
        while (getline(in, line)) {
            if (idx >= 20) break;  // Prevent overflow
            std::istringstream iss(line);
            char type;
            std::string name;
            iss >> type >> name;

            if (type == 'U') {
                int price, upgrade_price;
                iss >> price >> upgrade_price;
                std::vector<int> fines(5);
                for (int& fine : fines) iss >> fine;
                units_[idx++] = UpgradableUnit(idx - 1, name, price, upgrade_price, fines[0]);
            }
           else if (type == 'C') {
                int price, fine;
                iss >> price >> fine;
                CollectableUnit test(idx - 1, name, price, fine);
                units_[idx++] = &test;
            }
            else if (type == 'R') {
                int price, fine;
                iss >> price >> fine;
                units_[idx++] = new RandomCostUnit(idx - 1, name, price, fine);
            }
            else if (type == 'J') {
                units_[idx++] = new JailUnit(idx - 1, name);
            }
        }
        in.close();
    }
}

MapUnit* WorldMap::getUnit(int index) const {
    if (index < 0 || index >= (int)units_.size()) return nullptr;
    return units_[index];
}


void WorldMap::display(const WorldPlayer& worldPlayer) const {
    int total = size();
    int mid = total / 2 + total % 2;

    for (int row = 0; row < mid; ++row) {
        int leftIdx = row;
        int rightIdx = row + mid;

        std::string left = formatUnitDisplay(leftIdx, worldPlayer);
        std::string right = (rightIdx < total) ? formatUnitDisplay(rightIdx, worldPlayer) : "";

        std::cout << left << "    " << right << "\n";
    }
}


std::string WorldMap::formatUnitDisplay(int i, const WorldPlayer& worldPlayer) const {
    std::ostringstream oss;
    const MapUnit* unit = units_[i];

    // =players=
    oss << "=";
    for (int p = 0; p < worldPlayer.getNumPlayers(); ++p) {
        oss << (worldPlayer.getPlayer(p).getLocation() == i ? std::to_string(worldPlayer.getPlayer(p).getID()) : " ");
    }
    oss << "= ";

    // [i] 
    oss << std::setw(4) << ("[" + std::to_string(i) + "]");

    // unit name    
    oss << std::setw(10) << std::left << unit->getName();

    // <owner> //getOwner if no owner?
    if (unit->getOwner()) {
        oss << std::setw(4) << ("<" + std::to_string(unit->getOwner()->getID()) + ">");
    } else {
        oss << std::setw(4) << "< >";
    }
    
    // type
    std::string type = " ";
    if (auto* up = dynamic_cast<const UpgradableUnit*>(unit)) {
        // B$ or U$ with fine and level
        std::string type = up->getOwner() ? "U$" : "B$";
        oss << std::setw(5) << type;
        oss << std::setw(5) << up->calculateFine();
        oss << "L" << up->getLevel();
    }
    else if (auto* c = dynamic_cast<const CollectableUnit*>(unit)) {
        // Collectable: <owner> x N (no fine, no level)
        oss << " x " << c->getCount();
    }
    else if (dynamic_cast<const RandomCostUnit*>(unit)) {
        // Random: just display "?" (no fine, no level)
        oss << std::setw(5) << "?";
    }
    else if (dynamic_cast<const JailUnit*>(unit)) {
        oss << std::setw(5) << "J";
    }

    return oss.str();
}

