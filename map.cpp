#include <iostream>
#include "map.h"
#include "WorldMap.h"

using namespace std;

// ============ MapUnit ============
MapUnit::MapUnit(int id, const string &name, int price)
    : id_(id), name_(name), price_(price), owner_(nullptr) {}

void MapUnit::addPlayer(Player *player) {
    whoishere_.push_back(player);
}

void MapUnit::removePlayer(Player *player) {
    auto it = remove(whoishere_.begin(), whoishere_.end(), player);
    if (it != whoishere_.end()) {
        whoishere_.erase(it);
    }
}

int MapUnit::getId() const {
    return id_;
}

const string& MapUnit::getName() const {
    return name_;
}

int MapUnit::getPrice() const {
    return price_;
}

Player* MapUnit::getOwner() const {
    return owner_;
}

const vector<Player*>& MapUnit::whoishere() const {
    return whoishere_;
}

void MapUnit::setOwner(Player *owner) {
    owner_ = owner;
    owner->addUnit();
}

void MapUnit::releaseOwner(Player *player) {
    if (owner_ == player) {
        owner_ = nullptr;
    }

    removePlayer(player);
}



void MapUnit::printUnit(ostream &os) const {
    os << "[MapUnit] " << getName() << "\n";
}

// ============ UpgradableUnit ============
UpgradableUnit::UpgradableUnit(int id, const string &name, int price, int upgrade_price, int base_fine)
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

void UpgradableUnit::releaseOwner(Player* player) {
    if (owner_ == player) {
        owner_ = nullptr;
        level_ = MIN_LEVEL;
    }
    removePlayer(player);
}

int UpgradableUnit::event(Player &player) {
    if (!isOwned()) {
        if (player.getMoney() >= price_) {
            // Player can choose to buy the unit
            cout << "This land is unowned. Buy it for $" << price_ << "? (y/n): ";
            string answer;
            cin >> answer;

            if (checkAnswer(answer) && (answer[0] == 'y' || answer[0] == 'Y')) {
                player.deduct(price_);
                setOwner(&player);
                cout << "You bought " << getName() << " for $" << price_ << ".\n";
            } else {
                cout << "You chose not to buy " << getName() << ".\n";
            }
        } 

    }
    else if (*owner_ == player) {
        // Player owns the unit, can upgrade if possible
        if (isUpgradable()) {
            // Player can choose to upgrade
            cout << "Upgrade this land for $" << upgradePrice_ << "? (y/n): ";
            string answer;
            cin >> answer;
            if (checkAnswer(answer) && (answer[0] == 'y' || answer[0] == 'Y')) {
                if (player.deduct(upgradePrice_)) {
                    upgrade();
                    cout << "Upgraded to level " << level_ << ".\n";
                } else {
                    cout << "Not enough money to upgrade.\n";
                }
            }
        } else {
            cout << "Already at max level.\n";
        }
    }
    else {
        // Player must pay the fine
        int fine = calculateFine();
        cout << "Owned by " << owner_->getName() << ". Paying fine $" << fine << ".\n";
        player.deduct(fine);
        owner_->earnings(fine);
    }
    return UPGRADABLEUNIT;
}

void UpgradableUnit::printUnit(ostream &os) const {
    os << "[UpgradableUnit] " << getName() << " | Price: $" << getPrice()
       << " | Owner: " << (owner_ ? owner_->getName() : "None")
       << " | Level: " << level_
       << " | Fine: $" << calculateFine() << "\n";
}



// ============ CollectableUnit ============
CollectableUnit::CollectableUnit(int id, const string &name, int price, int fine)
    : MapUnit(id, name, price), fine_(fine) {}

int CollectableUnit::getFine() const {
    return fine_;
}

int CollectableUnit::calculateFine() const {
    if (!owner_) {
        return 0; 
    }
    // Count the number of Collectable units owned by the player
    return owner_->getNumberOfCollectableUnits() * fine_;
}

void CollectableUnit::releaseOwner(Player* player) {
    if (owner_ == player) {
        owner_ = nullptr;
    }
    removePlayer(player);
}

int CollectableUnit::event(Player &player) {
    if (!owner_) {
        if (player.getMoney() >= price_) {
            // Player can choose to buy the unit
            cout << "This land is unowned. Buy it for $" << price_ << "? (y/n): ";
            string answer;
            cin >> answer;

            if (checkAnswer(answer) && (answer[0] == 'y' || answer[0] == 'Y')) {
                if (player.deduct(price_)) {
                    setOwner(&player);
                    player.addCollectableUnit();
                    cout << "Purchased successfully.\n";
                } else {
                    cout << "Insufficient funds.\n";
                }
            }
        }
    }
    else if (owner_ != &player) {
        // Player must pay the fine to owner
        int totalFine = calculateFine();
        cout << "Owned by " << owner_->getName() << ". Pay fine $" << totalFine << ".\n";
        player.deduct(totalFine);
        owner_->earnings(totalFine);
    } else {
        cout << "You own this Collectable Unit.\n";
    }
    return COLLECTABLEUNIT;
}

void CollectableUnit::printUnit(ostream &os) const {
    os << "[CollectableUnit] " << getName() << " | Price: $" << getPrice()
       << " | Owner: " << (owner_ ? owner_->getName() : "None")
       << " | Fine per unit: $" << fine_ << "\n";
}


// ============ RandomCostUnit ============
RandomCostUnit::RandomCostUnit(int id, const string &name, int price, int fine)
    : MapUnit(id, name, price), fine_(fine) {}

int RandomCostUnit::getFine() const {
    return fine_;
}

int RandomCostUnit::calculateFine() const {
    return rollDice() * fine_;
}

int RandomCostUnit::event(Player &player) {
    if (!owner_) {
        if (player.getMoney() >= price_) {
            // Player can choose to buy the unit.
            cout << "This land is unowned. Buy it for $" << price_ << "? (y/n): ";
            string answer;
            cin >> answer;

            if (checkAnswer(answer) && (answer[0] == 'y' || answer[0] == 'Y')) {
                if (player.deduct(price_)) {
                    setOwner(&player);
                    cout << "Purchased successfully.\n";
                } else {
                    cout << "Insufficient funds.\n";
                }
            }
        }
        else {
            cout << "You cannot afford this Random Cost Unit.\n";
        }
    }
    else if (owner_ != &player) {
        // Player must pay the fine to owner
        int totalFine = calculateFine();
        cout << "Random fine rolled. Pay $" << totalFine << ".\n";
        player.deduct(totalFine);
        owner_->earnings(totalFine);
    } else {
        cout << "You own this RandomCost Unit.\n";
    }
    return RANDOMCOSTUNIT;
}

int rollDice() {
    return rand() % 6 + 1;
}

void RandomCostUnit::printUnit(ostream &os) const {
    os << "[RandomCostUnit] " << getName() << " | Price: $" << getPrice()
       << " | Owner: " << (owner_ ? owner_->getName() : "None")
       << " | Fine Multiplier: $" << fine_ << " per dice roll\n";
}

// =========== JailUnit ============
JailUnit::JailUnit(int id, const string &name)
    : MapUnit(id, name, 0) {}

int JailUnit::event(Player &player) {
    // Handle jail event for player
    cout << player.getName() << " landed in JAIL! You will miss the next round.\n";
    player.changeStatus(jail);
    return JAILUNIT;
}

void JailUnit::printUnit(ostream &os) const {
    os << "[JailUnit] " << getName() << " | JAIL\n";
}