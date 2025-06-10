#include <string>

// ============ MapUnit ============
class MapUnit {
public:
    // Constructor & Destructor
    MapUnit(int id, const std::string &name, int price);
    virtual ~MapUnit() = default;

    // Function triggered when a player lands on this unit
    virtual void trigger(Player &player) = 0;

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

MapUnit::MapUnit(int id, const std::string &name, int price)
    : id_(id), name_(name), price_(price), owner_(nullptr) {}

void MapUnit::addPlayer(Player *player) {
    playersHere.push_back(player);
}

void MapUnit::removePlayer(Player *player) {
    auto it = std::remove(playersHere.begin(), playersHere.end(), player);
    if (it != playersHere.end()) {
        playersHere.erase(it);
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
    return playersHere;
}

void MapUnit::setOwner(Player *owner) {
    owner_ = owner;
}


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

    void triggerEvent(Player *p) ovverride;

protected:
    int level_;
    int upgradePrice_;
    int baseFine_;
};

