#ifndef MAP_H
#define MAP_H

#include <string>
#include "player.h"

constexpr int MAX_NAME_LENGTH = 10;
constexpr int MAXPLAYER = 4;
constexpr int MAXLEVEL = 5;

// ============ MapUnit ============
class MapUnit {
public:
    // Constructor & Destructor
    MapUnit(int id, const std::string &name, int price);
    virtual ~MapUnit() = default;

    virtual void event(Player &player) = 0;

    void addPlayer(Player *player);
    void removePlayer(Player *player);

    int getId() const;
    std::string getName() const;
    Player* getOwner() const;
    int getPrice() const;
    const std::vector<Player*>& getPlayersHere() const;

    void setOwner(Player *owner);

    virtual void printUnit(std::ostream &os) const;

protected:
    int id_;
    std::string name_;
    int price_;
    Player *owner_;
    std::vector<Player*> playersHere;
};

// ============ UpgradableUnit ============
class UpgradableUnit : public MapUnit {
public:
    // Constructor & Destructor
    UpgradableUnit(int id, const std::string &name, int price, int level, int upgradePrice, int baseFine);
    ~UpgradableUnit() override = default;

    bool isOwned() const;
    bool isUpgradable() const;
    int calculateFine() const;
    
    void upgrade();
    void reset();

    int getLevel() const;
    int getUpgradePrice() const;
    int getBaseFine() const;

    void event(Player &player) override;

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

    void event(Player &player) override;
    int calculateFine() const;

private:
    int fine_;
};    

// ============ RandomCostUnit ============
class RandomCostUnit : public MapUnit {
public:
    // Constructor & Destructor
    RandomCostUnit(int id, const std::string &name, int price, int fine);
    ~RandomCostUnit() override = default;

    void event(Player &player) override;
    int calculateFine() const;

private:
    int fine_;
};

// =========== JailUnit ============
class JailUnit : public MapUnit {
public:
    // Constructor & Destructor
    JailUnit(int id, const std::string &name);
    ~JailUnit() override = default;

    void event(Player &player) override;
};


#endif // MAP_H