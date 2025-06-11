#include <iostream>
#include <string>
#include <vector>
#include "player.h"

using namespace std;

int dice()
{
    return 4;
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