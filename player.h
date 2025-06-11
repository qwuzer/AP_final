#ifndef PLAYER_H
#define PLAYER_H

constexpr int initDeposit=30000;
constexpr int mapSize=9;
constexpr int maxPlayersNum=4;
class WorldMap;

class Player{
    public:
    Player(int id, std::string name);
    bool operator==(const Player& other) const;

    void changeName(const std::string& newName);
    bool deduct(int const cost);
    void earnings(int const toll);
    void move(int const rolledNum);
    void addUnit();

    std::string getName() const;
    int getID() const;
    int getLocation() const;
    int getMoney() const;
    int getNumberOfUnits() const;
        
    private:
        const int id_;
        std::string name_="";
        int location_=0;
        int money_=initDeposit;
        int numUnits_=0;
};
class WorldPlayer{
    public:
        WorldPlayer(int numPlayers);
        WorldPlayer& operator++();
        WorldPlayer operator++(int);
        
        bool Action1();//new round
        bool Action2(int rolledNum, WorldMap& worldMap);//after rolled the dice
        
        Player& getPlayer(int index);
        int currentPlayerIs() const;
        int getCurrentPlayerID() const;
        int getNumPlayers() const;
        
    private:
        int numPlayers_;
        std::vector<Player> players_;
        const std::vector<std::string> defaultName_={"Frieren", "Himmel", "Heiter", "Eisen"};
        int currentPlayer_=0;
};

bool checkAnswer(const std::string& answer);
std::ostream& operator<<(std::ostream& os,const Player& player);
std::ostream& operator<<(std::ostream& os,WorldPlayer& players);
std::istream& operator>>(std::istream& is, Player& player);


#endif