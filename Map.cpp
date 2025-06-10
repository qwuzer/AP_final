#include "map.h"

// ============ MapUnit ============
MapUnit::MapUnit(int id, const std::string &name, int price)
    : id_(id), name_(name), price_(price), owner_(nullptr) {}

void MapUnit::addPlayer(Player *player) {
    whoishere_.push_back(player);
}

void MapUnit::removePlayer(Player *player) {
    auto it = std::remove(whoishere_.begin(), whoishere_.end(), player);
    if (it != whoishere_.end()) {
        whoishere_.erase(it);
    }
}

int MapUnit::getId() const {
    return id_;
}

std::string MapUnit::getName() const {
    return name_;
}

int MapUnit::getPrice() const {
    return price_;
}

Player* MapUnit::getOwner() const {
    return owner_;
}

const std::vector<Player*>& MapUnit::getPlayersHere() const {
    return whoishere_;
}

void MapUnit::setOwner(Player *owner) {
    owner_ = owner;
}

// ============ UpgradableUnit ============
UpgradableUnit::UpgradableUnit(int id, const std::string &name, int price, int level, int upgradePrice, int baseFine)
    : MapUnit(id, name, price), level_(level), upgradePrice_(upgradePrice), baseFine_(baseFine) {}

bool UpgradableUnit::isOwned() const {
    return owner_ != nullptr;
}

