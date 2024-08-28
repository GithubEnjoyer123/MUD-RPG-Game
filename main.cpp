/* Program name: main.cpp
* Author: Justin Phillips
* Date last updated: 5/12/2024
* Purpose: Final Project + graph algo
*/

#include "character.h"

int main(){
    string name, input;
    int choice, oldIndex = 0, max;
    character* player = new character("", 0,0,0,0,0,0,0,0);
    inventory* playerInv = new inventory(1, 1, 0);
    level* playerLevel = new level(0, 0);
    
    //This line creates our character based on the class selected
    characterClass charClass = static_cast<characterClass>(player->makeCharacter(player));

    //Saves our input from file to see which monsters we will fight (This is something that could be randomized later?)
    cout << "\n" << player->getName() << " the " << charClass << " created!";

    //This sets up our dungeon size, determined by the difficulty the player picks
    Dungeon dungeon(dungeon.dungeonDifficulty());

    //We generate our dungeon here, not making it in our constructor since we need to find our highest index value for our win condition
    max = dungeon.makeDungeon();

    //We print our characters backstory here. Just random static text.
    cout << player->printStory();

    
    while(oldIndex != max){
        bool fight = false;
        //We set our index to our new vertex, and keep track of our old one for removal
        int index = dungeon.getPath(menu(player, playerInv, playerLevel, fight), oldIndex); 
        if(index == -99){
            cout << "\nThere is nothing to fight.";
            continue;
        }else if(index == -100){
           monster monsterType = dungeon.deadEnd(dungeon.getDiff());
           fight = true;
           combatLoop(monsterType, charClass, player, playerInv, playerLevel, fight);
           cout << "\nAfter a tumultuous fight, the beast slain turns into a scroll. Upon touching the scroll, your vision blurs...";
           break;
        }
        dungeon.rmLink(index, oldIndex);
        oldIndex = index;

        //Overloads our monstertype, dictated by difficulty and the vertex value we hit
        monster monsterType = static_cast<monster>(dungeon.getMonster(index));
        fight = true;
        combatLoop(monsterType, charClass, player, playerInv, playerLevel, fight);
    }

        cout << "\nYou see a light and rush towards it. Around you is a vast grassland, bathed in sunlight. You are free!\n";

        return 0;
}
    