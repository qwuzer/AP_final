#ifndef MAP_H
#define MAP_H

#include <string>
#include "player.h"

constexpr int MAX_NAME_LENGTH = 10;
constexpr int MAX_PLAYER = 4;
constexpr int MAX_LEVEL = 5;
constexpr int MIN_LEVEL = 1;

constexpr int UPGRADABLEUNIT = 1;
constexpr int COLLECTABLEUNIT = 2;
constexpr int RANDOMCOSTUNIT = 3;
constexpr int JAILUNIT = 4;

// ============ MapUnit ============
class MapUnit {
public:
    // Constructor & Destructor
    MapUnit(int id, const std::string &name, int price);
    virtual ~MapUnit() = default;

    virtual int event(Player &player) = 0;

    void addPlayer(Player *player);
    void removePlayer(Player *player);

    int getId() const;
    const std::string& getName() const;
    Player* getOwner() const;
    int getPrice() const;
    const std::vector<Player*>& whoishere() const;

    void setOwner(Player *owner);
    virtual void releaseOwner(Player *player);

    virtual void printUnit(std::ostream &os) const;

protected:
    int id_;
    std::string name_;
    int price_;
    Player *owner_;
    std::vector<Player*> whoishere_;
};

// ============ UpgradableUnit ============
class UpgradableUnit : public MapUnit {
public:
    // Constructor & Destructor
    UpgradableUnit(int id, const std::string &name, int price, int upgrade_price, int base_fine);
    ~UpgradableUnit() override = default;

    bool isOwned() const;
    bool isUpgradable() const;
    int calculateFine() const;
    
    void upgrade();
    void reset();

    int getLevel() const;
    int getUpgradePrice() const;
    int getBaseFine() const;

    void releaseOwner(Player *player) override;
    int event(Player &player) override;
    void printUnit(std::ostream &os) const override;

private:
    int level_;
    int upgradePrice_;
    int baseFine_;
};


// ============ CollectableUnit ============
class CollectableUnit : public MapUnit {
public:
    // Constructor & Destructor
    CollectableUnit(int id, const std::string &name, int price, int fine);
    ~CollectableUnit() override = default;

    void printUnit(std::ostream &os) const override;

    int getFine() const;

    int calculateFine() const;
    void releaseOwner(Player* player) override;

    int event(Player &player) override;

private:
    int fine_;
};    

// ============ RandomCostUnit ============
class RandomCostUnit : public MapUnit {
public:
    // Constructor & Destructor
    RandomCostUnit(int id, const std::string &name, int price, int fine);
    ~RandomCostUnit() override = default;

    void printUnit(std::ostream &os) const override;

    int getFine() const;

    int calculateFine() const;
    int event(Player &player) override;

private:
    int fine_;
};

// =========== JailUnit ============
class JailUnit : public MapUnit {
public:
    // Constructor & Destructor
    JailUnit(int id, const std::string &name);
    ~JailUnit() override = default;

    void printUnit(std::ostream &os) const override;
    int event(Player &player) override;
};

int rollDice();

#endif // MAP_H