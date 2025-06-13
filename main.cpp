#include <iostream>
#include "WorldMap.h"
#include "player.h"

using namespace std;

int main() {
    // Step 1: Load the map
    WorldMap map;
    map.loadFromFile("map.dat");  // Make sure this file exists and is properly formatted

    // // Step 2: Create WorldPlayer (e.g., 4 players max)
    int numPlayers = 4;
    WorldPlayer players(numPlayers, &map);

    // // Step 3: Simulate some player positions for test
    players.getPlayer(0).move(2); // Player 0 to Unit 2
    players.getPlayer(1).move(4); // Player 1 to Unit 4
    players.getPlayer(2).move(6); // Player 2 to Unit 6
    players.getPlayer(3).move(8); // Player 3 to Unit 8

    cout << players << endl;

    // // Step 4: Display the map (2-column layout)
    // std::cout << "========= Game Board =========\n";
    map.display(players);

    // // Step 5: Print player status
    // std::cout << "\n========= Player Status =========\n";
    // std::cout << players;

    return 0;
}