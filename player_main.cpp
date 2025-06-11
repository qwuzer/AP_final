#include <iostream>
#include <string>
#include <vector>
#include "player.h"

using namespace std;

int dice()
{
    return 4;
}
// bool checkAnswer(const string& answer)
// {
//     if (answer.size() != 1) {
//         return false;
//     }

//     char c = answer[0];
//     return c == 'n' || c == 'N' || c == 'y' || c == 'Y';
// }
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
using namespace std;

// class Player{

//     friend class WorldPlayer;
//     friend std::ostream& operator<<(std::ostream& os,const Player& player);
//     friend std::istream& operator>>(std::istream& is,const Player& player);

//     public:
//     Player(int id, string name):id_(id), name_(name){}

    
//     void changeName(const string& newName) 
//     {
//         name_ = newName;
//     } 
//     bool deduct(int const cost)
//     {
//         if (cost>money_)
//         {
//             return 0;
//         }
//         money_-=cost;
//         return 1;
//     }
//     void move(int const rolledNum)
//     {
//         location_=(location_+rolledNum)%9;//9->map size
//     }
//     void addUnit()
//     {
//         numUnits_++;
//     }

//     string getName() const 
//     {
//         return name_;
//     }
//     int getID() const
//     {
//         return id_;
//     }
//     int getLocation() const
//     {
//         return location_;
//     }
//     int getMoney() const
//     {
//         return money_;
//     }
//     int getNumberOfUnits() const
//     {
//         return numUnits_;
//     }
        
//     private:
//         const int id_;
//         string name_="";
//         int location_=0;
//         int money_=15000;//?
//         int numUnits_=0;
// };
// class WorldPlayer{
//     friend std::ostream& operator<<(std::ostream& os,const WorldPlayer& players);

//     public:
//         WorldPlayer(int numPlayers):numPlayers_(numPlayers)
//         {
//             if(numPlayers_>4)
//             {
//                 numPlayers_=4;
//                 cout<<"A maximum of four players is allowed."<<endl;
//             }
//             for (int i = 0; i < numPlayers_; ++i) {
//                 players_.emplace_back(i, defaultName_[i]); 
//             }
//         }
//         WorldPlayer& operator++()
//         {
//             currentPlayer_=(currentPlayer_+1)%numPlayers_;
//             return *this;
//         }
//         WorldPlayer operator++(int)
//         {
//             WorldPlayer temp= *this;
//             currentPlayer_=(currentPlayer_+1)%numPlayers_;
//             return temp;
//         }
        
//         bool Action1()//new round
//         {
//             cout<<players_[currentPlayer_].getName()<<", do you want to roll the dice?(y/n) ";
//             string answer;
//             cin>>answer;cin.ignore();
//             if (checkAnswer(answer))
//             {
//                 if (answer[0]=='n'||answer[0]=='N') 
//                 {
//                     cerr<<"no";
//                     return false;
//                 }
//                 else
//                 {
//                     cerr<<"yes";
//                     return true;
//                 }
//             }
//             cout<<"Invalid input."<<endl;
//             return Action1();
//         }

//         bool Action2(int rolledNum)//after rolled the dice
//         {
//             players_[currentPlayer_].move(rolledNum);
//             //
//         }

//         Player& getPlayer(int index) 
//         {
//             return players_.at(index);
//         }
//         int currentPlayerIs() const
//         {
//             cout<<"It's "<<players_[currentPlayer_].name_<<"'s turn."<<endl;
//             return currentPlayer_;
//         }
//         int getNumPlayers() const
//         {
//             return numPlayers_;
//         }
        
//     private:
//         int numPlayers_;
//         vector<Player> players_;
//         const vector<string> defaultName_={"Frieren", "Himmel", "Heiter", "Eisen"};
//         int currentPlayer_=0;
// };
// std::ostream& operator<<(std::ostream& os,const Player& player)
// {
//     cout<<"["<<player.id_<<"]"<<player.name_<<" $"<<player.money_<<" with "<<player.numUnits_<<" Units"<<endl;
//     return os;
// }
// std::ostream& operator<<(std::ostream& os,const WorldPlayer& players)
// {
//     for (int i = 0; i < players.numPlayers_; i++)
//     {
//         cout<<players.players_[i];  
//     }
//     return os;
// }
// std::istream& operator>>(std::istream& is, Player& player)
// {
//     string a;
//     is>>a;
//     player.changeName(a);
//     return is;
// }

int main()
{
    WorldPlayer players(4);
    cout<<players;
    cout<<endl;
    cout<<players.getPlayer(1);
    // cout<<players.getPlayer(1).getID();
    // cout<<players.getPlayer(1).getLocation();
    // cout<<players.getPlayer(1).getMoney();
    // cout<<players.getPlayer(1).getNumberOfUnits();

    // players.getPlayer(1).changeName("abc");
    // cout<<players.getPlayer(1);


    // cin>>players.getPlayer(1);cin.ignore();
    cout<<players.getPlayer(1);
    for (;;)
    {
        players.currentPlayerIs();
        
        if (players.Action1())
        {
            players++;
        }
        else if (wantExit())
        {
            break;
        }
    }
    
    


    return 0;
}