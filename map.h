#ifndef MAP_H
#define MAP_H

#include <string>

constexpr int MAXLEVEL = 5;

// ============ MapUnit ============
class MapUnit {
public:
    // Constructor & Destructor
    MapUnit(int id, const std::string &name, int price);
    virtual ~MapUnit() = default;

    // Function triggered when a player lands on this unit
    virtual void event(Player &player) = 0;

    // Basic Operations
    void addPlayer(Player *player);
    void removePlayer(Player *player);

    // Getters
    int getId() const;
    std::string getName() const;
    Player* getOwner() const;
    int getPrice() const;
    const std::vector<Player*>& getPlayersHere() const;

    // Setters
    void setOwner(Player *owner);

    // Virtual print function
    virtual void print(std::ostream &os) const;

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

    // Getters
    int getLevel() const;
    int getUpgradePrice() const;
    int getBaseFine() const;

    void event(Player *p) override;

protected:
    int level_;
    int upgradePrice_;
    int baseFine_;
};


#endif // MAP_H