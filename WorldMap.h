#ifndef WORLD_MAP_H
#define WORLD_MAP_H
#include <string>
#include "map.h"

class WorldMap {
public:
    WorldMap() = default;

    void loadFromFile(const std::string& filename);
    MapUnit* getUnit(int index) const;
    size_t size() const;
    void display(WorldPlayer& worldPlayer) const;
    std::string formatUnitDisplay(int i,  WorldPlayer& worldPlayer) const;
private:
    MapUnit* units_[20]; 
};

#endif