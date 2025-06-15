#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>

constexpr int initDeposit=30000;
constexpr int maxPlayersNum=4;
constexpr int minPlayersNum=1;
constexpr int alive=1;
constexpr int jail=2;
constexpr int dead=3;

class WorldMap;

class Player{
    public:
    Player(int id, std::string name);
    bool operator==(const Player& other) const;

    void changeName(const std::string& newName);
    bool deduct(int const cost);
    void earnings(int const toll);
    void move(int const rolledNum, WorldMap& map_);
    void addUnit();
    void addCollectableUnit();
    void changeStatus(int const status);

    std::string getName() const;
    int getID() const;
    int getLocation() const;
    int getMoney() const;
    int getNumberOfUnits() const;
    int getNumberOfCollectableUnits() const;
    int getStatus() const;
        
    private:
        const int id_;
        std::string name_="";
        int location_=0;
        int money_=initDeposit;
        int numUnits_=0;
        int numCollectableUnits_=0;
        int status_=alive;
};
class WorldPlayer{
    public:
        WorldPlayer(int numPlayers, WorldMap* map);
        WorldPlayer& operator++();
        WorldPlayer operator++(int);
        
        bool Action1();//new round
        int Action2();//after rolled the dice
        bool gameOver();

        Player& getPlayer(int index);
        int currentPlayerIs() const;
        int getCurrentPlayerID() const;
        int getNumPlayers() const;
        
    private:
        int numPlayers_=1;
        std::vector<Player> players_;
        const std::vector<std::string> defaultName_={"Frieren", "Himmel", "Heiter", "Eisen"};
        int currentPlayer_=0;
        WorldMap *map_=nullptr;
};

bool checkAnswer(const std::string& answer);
std::ostream& operator<<(std::ostream& os,const Player& player);
std::ostream& operator<<(std::ostream& os,WorldPlayer& players);
std::istream& operator>>(std::istream& is, Player& player);
bool wantExit();
bool checkNum(const std::string& answer);
void displayScreen(WorldMap &map, WorldPlayer &players);


#endif