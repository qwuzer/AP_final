#include "WorldMap.h"
#include "player.h"
// #include "map.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

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
                units_[idx++] = new UpgradableUnit(idx - 1, name, price, upgrade_price, fines[0]);
                std::cout << "Loaded UpgradableUnit: " << name << " with price: " << price << " and upgrade price: " << upgrade_price << "\n";
            }
            else if (type == 'C') {
                int price, fine;
                iss >> price >> fine;
                units_[idx++] = new CollectableUnit(idx - 1, name, price, fine);
                std::cout << "Loaded CollectableUnit: " << name << " with price: " << price << " and fine: " << fine << "\n";
            }
            else if (type == 'R') {
                int price, fine;
                iss >> price >> fine;
                units_[idx++] = new RandomCostUnit(idx - 1, name, price, fine);
                std::cout << "Loaded RandomCostUnit: " << name << " with price: " << price << " and fine: " << fine << "\n";
            }
            else if (type == 'J') {
                units_[idx++] = new JailUnit(idx - 1, name);
                std::cout << "Loaded JailUnit: " << name << "\n";
            }
        }
        in.close();
    }
}

MapUnit* WorldMap::getUnit(int index) const {
    if (index < 0 || index >= 20) return nullptr;
    return units_[index];
}

size_t WorldMap::size() const {
    size_t count = 0;
    for (const auto& unit : units_) {
        if (unit != nullptr) ++count;
    }
    return count;
}


void WorldMap::display( WorldPlayer& worldPlayer) const {
    int total = size();
    cout << "total: " << total << endl;
    int mid = total / 2 + total % 2;
    cout << "mid: " << mid << endl;

    for (int row = 0; row < mid; ++row) {
        int leftIdx = row;
        int rightIdx = row + mid;

        std::string left = formatUnitDisplay(leftIdx, worldPlayer);
        std::string right = (rightIdx < total) ? formatUnitDisplay(rightIdx, worldPlayer) : "";

        // std::cout << left << "    " << right << "\n";
        std::cout << std::left << std::setw(40) << left << right << "\n";
    }
}


std::string WorldMap::formatUnitDisplay(int i,  WorldPlayer& worldPlayer) const {
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
    oss << std::setw(10) << std::right << unit->getName();

    // <owner> //getOwner if no owner?
    if (unit->getOwner()) {
        oss << std::setw(4) << std::right << ("{" + std::to_string(unit->getOwner()->getID()) + "}");
    } else {
        oss << std::setw(4) << "  ";
    }
    
    // type
    std::string type = " ";
    if (auto* up = dynamic_cast<const UpgradableUnit*>(unit)) {
        if (up->getOwner()) {
            // Owned: show upgraded price and level
            oss << std::setw(3) << "U$";
            oss << std::setw(5) << up->calculateFine();
            oss << " L" << up->getLevel();
        } else {
            // Not owned: show base price
            oss << std::setw(3) << "B$";
            oss << std::setw(5) << up->getPrice();
        }
    }
    else if (auto* c = dynamic_cast<const CollectableUnit*>(unit)) {
        // Collectable: <owner> x N (no fine, no level)
        if (c->getOwner()) {
            oss << " x" << c->getOwner()->getNumberOfCollectableUnits();
        } else {
            oss <<  std::setw(3) << "C$";
            oss << std::setw(5) << c->getPrice();
        }
    }
    else if (dynamic_cast<const RandomCostUnit*>(unit)) {
        // Random: just display "?" (no fine, no level)
        oss << std::setw(3) << "?";
    }
    else if (dynamic_cast<const JailUnit*>(unit)) {
        oss << std::setw(3) << "J";
    }

    return oss.str();
}

