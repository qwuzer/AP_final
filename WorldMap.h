#pragma once
#include <string>
#include "MapUnit.h"

class WorldMap {
public:
    WorldMap() = default;

    void loadFromFile(const std::string& filename);
    MapUnit* getUnit(int index) const;
    size_t size() const;
    void printMap() const;  
private:
    MapUnit* units_[20]; 
};wo