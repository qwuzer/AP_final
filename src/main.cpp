#include <iostream>
#include "WorldMap.h"
#include "player.h"
#include <thread>   
#include <chrono>   

using namespace std;

int main() {
    WorldMap map;
    map.loadFromFile("map.dat");  

    int numPlayers = 0;
    system("clear");
    while (true) {
        cout << "How many players are there? ";
        cin >> numPlayers;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Invalid input." << endl;
        } else if (numPlayers < minPlayersNum || numPlayers > maxPlayersNum) {
            cout << "Support "<<minPlayersNum<<"-"<<maxPlayersNum<<" players only." << endl;
        } else {
            break;
        }
    }
    
    WorldPlayer players(numPlayers, &map);
    for (int i = 0; i < players.getNumPlayers(); i++)
    {
        cout<<players.getPlayer(i).getName()<<", do u want to change your name?(y/n) ";
        string answer;
        cin>>answer;cin.ignore();
        if (checkAnswer(answer))
        {
            if (answer[0]=='y'||answer[0]=='Y') 
            {
                cout<<"Please enter your new name: ";
                cin>>players.getPlayer(i);cin.ignore();
            }
            continue;
        }
        cout<<"Invalid input."<<endl;
        i--;
    }
    while (true)
    {
        displayScreen(map, players);
        
        if (players.Action1())
        {
            int unitType=players.Action2();
            ++players;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        else if (wantExit())
        {
            break;
        }
        if(players.gameOver())
        {
            break;
        }
    }
    return 0;
}
