#include <iostream>
#include "map.h"
#include "WorldMap.h"

// ============ MapUnit ============
MapUnit::MapUnit(int id, const std::string &name, int price)
    : id_(id), name_(name), price_(price), owner_(nullptr) {}

MapUnit::~MapUnit() {};

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

const std::string& MapUnit::getName() const {
    return name_;
}

int MapUnit::getPrice() const {
    return price_;
}

Player* MapUnit::getOwner() const {
    return owner_;
}

const std::vector<Player*>& MapUnit::whoishere() const {
    return whoishere_;
}

void MapUnit::setOwner(Player *owner) {
    owner_ = owner;
}

// ============ UpgradableUnit ============
UpgradableUnit::UpgradableUnit(int id, const std::string &name, int price, int upgrade_price, int base_fine)
    : MapUnit(id, name, price), level_(MIN_LEVEL), upgradePrice_(upgrade_price), baseFine_(base_fine) {}

bool UpgradableUnit::isOwned() const {
    return owner_ != nullptr;
}

bool UpgradableUnit::isUpgradable() const {
    return isOwned() && level_ < MAX_LEVEL;
}

int UpgradableUnit::calculateFine() const {
    return baseFine_ * level_;
}

void UpgradableUnit::upgrade() {
    if (isUpgradable()) {
        ++level_;
    }
}

void UpgradableUnit::reset() {
    level_ = 1; // Reset to initial level
    owner_ = nullptr;
}

int UpgradableUnit::getLevel() const {
    return level_;
}

int UpgradableUnit::getUpgradePrice() const {
    return upgradePrice_;
}

int UpgradableUnit::getBaseFine() const {
    return baseFine_;
}

void UpgradableUnit::event(Player &player) {
    if (!isOwned()) {
        if (player.getMoney() >= price_) {
            // TODO: Player can choose to buy the unit
        } 

    }
    else if (*owner_ == player) {
        // Player owns the unit, can upgrade if possible
        if (isUpgradable()) {
            // TODO: Player can choose to upgrade
        }
    }
    else {
        // Player must pay the fine
        int totalFine = calculateFine();
        player.deduct(totalFine);
        owner_->earnings(totalFine);
    }
}

void UpgradableUnit::printUnit(std::ostream &os) const {
    os << "[UpgradableUnit] " << getName() << " | Price: $" << getPrice()
       << " | Owner: " << (owner_ ? owner_->getName() : "None")
       << " | Level: " << level_
       << " | Fine: $" << calculateFine() << "\n";
}



// ============ CollectableUnit ============
CollectableUnit::CollectableUnit(int id, const std::string &name, int price, int fine)
    : MapUnit(id, name, price), fine_(fine) {}

int CollectableUnit::getFine() const {
    return fine_;
}

int CollectableUnit::calculateFine() const {
    if (!owner_) {
        return 0; // Not owned, no fine
    }

    int count = 0;
    // TODO: Count the number of Collectable units owned by the player
    return count * fine_;
}

void CollectableUnit::event(Player &player) {
    if (!owner_) {
        if (player.getMoney() >= price_) {
            // TODO: Player can choose to buy the unit
        }
    }
    else if (owner_ != &player) {
        // Player must pay the fine to owner
        // FIXME: Calculate fine based on the number of Collectable units owned by the owner
        int totalFine = calculateFine();
        player.deduct(totalFine);
        owner_->earnings(totalFine);
    }
}

void CollectableUnit::printUnit(std::ostream &os) const {
    os << "[CollectableUnit] " << getName() << " | Price: $" << getPrice()
       << " | Owner: " << (owner_ ? owner_->getName() : "None")
       << " | Fine per unit: $" << fine_ << "\n";
}


// ============ RandomCostUnit ============
RandomCostUnit::RandomCostUnit(int id, const std::string &name, int price, int fine)
    : MapUnit(id, name, price), fine_(fine) {}

int RandomCostUnit::getFine() const {
    return fine_;
}

int RandomCostUnit::calculateFine() const {
    return rollDice() * fine_;
}

void RandomCostUnit::event(Player &player) {
    if (!owner_) {
        if (player.getMoney() >= price_) {
            // TODO: Player can choose to buy the unit.
            // player.deduct(price_);
            // setOwner(&player);
            // player add owned unit
        }
    }
    else if (*owner_ == player) {
        // Player must pay the fine to owner
        int totalFine = calculateFine();
        player.deduct(totalFine);
        owner_->earnings(totalFine);
    }
}

int RandomCostUnit::rollDice() const {
    return rand() % 6 + 1;
}

void RandomCostUnit::printUnit(std::ostream &os) const {
    os << "[RandomCostUnit] " << getName() << " | Price: $" << getPrice()
       << " | Owner: " << (owner_ ? owner_->getName() : "None")
       << " | Fine Multiplier: $" << fine_ << " per dice roll\n";
}

// =========== JailUnit ============
JailUnit::JailUnit(int id, const std::string &name)
    : MapUnit(id, name, 0) {}

void JailUnit::event(Player &player) {
    // TODO: Handle jail event for player
}

void JailUnit::printUnit(std::ostream &os) const {
    os << "[JailUnit] " << getName() << " | JAIL\n";
}