#include <iostream>
#include "WorldMap.h"
#include "player.h"
#include <thread>   // for std::this_thread::sleep_for
#include <chrono>   // for std::chrono::seconds

using namespace std;

int main() {
    WorldMap map;
    map.loadFromFile("map.dat");  // Make sure this file exists and is properly formatted

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
    

    // // Step 3: Simulate some player positions for test
    // players.getPlayer(0).move(2); // Player 0 to Unit 2
    // players.getPlayer(1).move(4); // Player 1 to Unit 4
    // players.getPlayer(2).move(6); // Player 2 to Unit 6
    // players.getPlayer(3).move(8); // Player 3 to Unit 8

    // cout << players << endl;

    // MapUnit* unit2 = map.getUnit(2);  // Assume Upgradable
    // if (auto* up = dynamic_cast<UpgradableUnit*>(unit2)) {
    //     up->setOwner(&players.getPlayer(0));
    //     up->upgrade(); // Optional: to see level increment
    // }

    // MapUnit* unit6 = map.getUnit(6);  // Assume Collectable
    // if (auto* c = dynamic_cast<CollectableUnit*>(unit6)) {
    //     c->setOwner(&players.getPlayer(2));
    //     c->getOwner()->addCollectableUnit(); // simulate ownership increase
    //     c->getOwner()->addCollectableUnit(); // simulate ownership increase
    // }
    
    // // Step 4: Display the map (2-column layout)
    

    // // Step 5: Print player status
    // std::cout << "\n========= Player Status =========\n";
    // std::cout << players;
    // displayScreen(map, players);
    while (true)
    {
        displayScreen(map, players);
        
        if (players.Action1())
        {
            int unitType=players.Action2();
            if (unitType==4)//jail
            {
                
            }
            ++players;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            string a;//for debugging
            cin>>a;cin.ignore();//for debugging
        }
        else if (wantExit())
        {
            break;
        }
    }
    return 0;
}
