#include <iostream>
#include "player.h"
#include <string>
#include <vector>
#include <set>
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
        return false;
    }
    money_-=cost;
    return true;
}
void Player::earnings(int const toll)
{
    money_+=toll;
}
void Player::move(int const rolledNum)
{
    location_=(location_+rolledNum)%mapSize;
    if (location_==0)
    {
        earnings(2000);
    }
}
void Player::addUnit()
{
    numUnits_++;
}
string Player::getName() const 
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
        



WorldPlayer::WorldPlayer(int numPlayers, WorldMap* map):numPlayers_(std::min(numPlayers, maxPlayersNum)), map_(map)
{
    if(numPlayers_>maxPlayersNum)
    {
        cerr<<"A maximum of "<<maxPlayersNum<<"players is allowed."<<endl;
    }
    for (int i = 0; i < numPlayers_; ++i) 
    {
        players_.emplace_back(i, defaultName_[i]); 
    }
}
WorldPlayer& WorldPlayer::operator++()
{
    currentPlayer_=(currentPlayer_+1)%numPlayers_;
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
    cout<<players_[currentPlayer_].getName()<<", do you want to roll the dice?(y/n) ";
    string answer;
    cin>>answer;cin.ignore();
    if (checkAnswer(answer))
    {
        if (answer[0]=='n'||answer[0]=='N') 
        {
            // cerr<<"no";
            return false;
        }
        else
        {
            // cerr<<"yes";
            return true;
        }
    }
    cerr<<"Invalid input."<<endl;
    return Action1();
}
void WorldPlayer::Action2(int rolledNum)//after rolled the dice
{
    players_[currentPlayer_].move(rolledNum);
    (*map_).getUnit(players_[currentPlayer_].getLocation())->event(players_[currentPlayer_]);
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


std::ostream& operator<<(std::ostream& os,const Player& player)
{
    os<<"["<<player.getID()<<"]"<<player.getName()<<" $"<<player.getMoney()<<" with "<<player.getNumberOfUnits()<<" Units"<<endl;
    return os;
}
std::ostream& operator<<(std::ostream& os, WorldPlayer& players)
{
    for (int i = 0; i < players.getNumPlayers(); i++)
    {
        os << players.getPlayer(i);
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
