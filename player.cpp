#include <iostream>
#include "player.h"
#include <string>
#include <vector>
#include <set>

using namespace std;

Player::Player(int id, string name):id_(id), name_(name){}    
void Player::changeName(const string& newName) 
{
    name_ = newName;
} 
bool Player::deduct(int const cost)
{
    if (cost>money_)
    {
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
        



WorldPlayer::WorldPlayer(int numPlayers):numPlayers_(std::min(numPlayers, maxPlayersNum))
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
bool WorldPlayer::Action2(int rolledNum)//worldmap&//after rolled the dice //not done yet
{
    players_[currentPlayer_].move(rolledNum);
    //
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
