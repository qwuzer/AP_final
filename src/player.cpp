#include <iostream>
#include "player.h"
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include "map.h"
#include "WorldMap.h"

using namespace std;

Player::Player(int id, string name):id_(id), name_(name){}  
bool Player::operator==(const Player& other) const {
    return id_ == other.id_;
}  
void Player::changeName(const string& newName) 
{
    name_ = newName;
} 
bool Player::deduct(int const cost)
{
    if (cost>money_)
    {
        cout<<name_<<", you're bankrupt!"<<endl;
        status_=dead;
        return false;
    }
    money_-=cost;
    return true;
}
void Player::earnings(int const toll)
{
    money_+=toll;
}
void Player::move(int const rolledNum, WorldMap& map_)
{
    int originLoc=location_;
    location_=(location_+rolledNum)%map_.size();
    if (location_<originLoc)
    {
        earnings(2000);
    }
}
void Player::addUnit()
{
    numUnits_++;
}
void Player::addCollectableUnit()
{
    numCollectableUnits_++;
}
void Player::changeStatus(int const status)
{
    status_=status;
}

std::string Player::getName() const 
{
    return name_;
}
int Player::getID() const
{
    return id_;
}
int Player::getLocation() const
{
    return location_;
}
int Player::getMoney() const
{
    return money_;
}
int Player::getNumberOfUnits() const
{
    return numUnits_;
}
int Player::getNumberOfCollectableUnits() const
{
    return numCollectableUnits_;
}
int Player::getStatus() const
{
    return status_;
}
WorldPlayer::WorldPlayer(int numPlayers, WorldMap* map):numPlayers_(numPlayers), map_(map)
{
    for (int i = 0; i < numPlayers_; ++i) 
    {
        players_.emplace_back(i, defaultName_[i]); 
    }
}
WorldPlayer& WorldPlayer::operator++()
{
    for (int i = 1; i < maxPlayersNum; i++)
    {
        if (players_[(currentPlayer_+i)%numPlayers_].getStatus()!=dead)
        {
            if (players_[(currentPlayer_+i)%numPlayers_].getStatus()==jail)
            {
                players_[(currentPlayer_+i)%numPlayers_].changeStatus(alive);
                continue;
            }
            currentPlayer_=(currentPlayer_+i)%numPlayers_;
            break;
        }
        
    }
    return *this;
}
WorldPlayer WorldPlayer::operator++(int)
{
    WorldPlayer temp= *this;
    currentPlayer_=(currentPlayer_+1)%numPlayers_;
    return temp;
}
bool WorldPlayer::Action1()//new round
{
    cout<<players_[currentPlayer_].getName()<<", it's your turn. Do you want to roll the dice?(y/n) ";
    string answer;
    cin>>answer;cin.ignore();
    if (checkAnswer(answer))
    {
        if (answer[0]=='n'||answer[0]=='N') 
        {
            return false;
        }
        else
        {
            int rolledNum=rollDice();
            players_[currentPlayer_].move(rolledNum, *map_);
            displayScreen(*map_, *this);
            cout<<players_[currentPlayer_].getName()<<", you rolled:"<<rolledNum<<endl;
            return true;
        }
    }
    cerr<<"Invalid input."<<endl;
    return Action1();
}
int WorldPlayer::Action2()//after rolled the dice
{
    int type=(*map_).getUnit(players_[currentPlayer_].getLocation())->event(players_[currentPlayer_]);

    return type;
}
bool WorldPlayer::gameOver()
{
    int count=0;
    int winner=-1;
    for (int i = 0; i < numPlayers_; i++)
    {
        if (players_[i].getStatus()==dead)
        {
            count++;
        }
        else
        {
            winner=i;
        }
    }
    if (count>=(numPlayers_-1))
    {
        cout<<players_[winner].getName()<<", congratulations on your victory!"<<endl;
        return true;
    }
    return false;
}
Player& WorldPlayer::getPlayer(int index) 
{
    return players_.at(index);
}
int WorldPlayer::currentPlayerIs() const
{
    cout<<"It's "<<players_[currentPlayer_].getName()<<"'s turn."<<endl;
    return currentPlayer_;
}
int WorldPlayer::getCurrentPlayerID() const
{
    return currentPlayer_;
}
int WorldPlayer::getNumPlayers() const
{
    return numPlayers_;
}  
bool checkAnswer(const std::string& answer)
{
    static const std::set<char> valid{'y','Y','n','N'};
    return answer.size() == 1 && valid.count(answer[0]);
}
bool checkNum(const std::string& answer)
{
    static const std::set<char> valid{'1','2','3','4'};
    return answer.size() == 1 && valid.count(answer[0]);
}
std::ostream& operator<<(std::ostream& os,const Player& player)
{
    os<<"["<<player.getID()<<"]"<<player.getName()<<" $"<<player.getMoney()<<" with "<<player.getNumberOfUnits()<<" Units"<<endl;
    return os;
}
std::ostream& operator<<(std::ostream& os, WorldPlayer& players)
{
    for (int i = 0; i < players.getNumPlayers(); i++)
    {
        if (players.getPlayer(i).getStatus()!=dead)
        {
            os << players.getPlayer(i);
        }
    }
    return os;
}
std::istream& operator>>(std::istream& is,Player& player)
{
    string a;
    is>>a;
    player.changeName(a);
    return is;
}
bool wantExit()
{
    cout<<"End Game?(y/n)";
    string answer;
    cin>>answer;cin.ignore();
    if (checkAnswer(answer))
    {
        if (answer[0]=='y'||answer[0]=='Y') return true;
        if (answer[0]=='n'||answer[0]=='N') return false;
    }
    cout<<"Invalid input."<<endl;
    return wantExit(); 
}
void displayScreen(WorldMap &map, WorldPlayer &players)
{
    system("clear");
    map.display(players);
    cout<<players;
}