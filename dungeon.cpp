#include "character.h"

Dungeon::Dungeon(int vertex){
    this->vertex = vertex;
    link = new list<int>[vertex];
}

//Removes previous path, as backtracking would face you against the "boss"
void Dungeon::rmLink(int x, int y){
    link[x].remove(y);


    auto it = find(link[y].begin(), link[y].end(), x);
    if (it != link[y].end()){
        link[y].erase(it);
    }
}

//This prints our test values recursively to make sure we're generating stuff correctly. Not in use during actual game
//Using this during the game would actually worsen the efficiency I believe
void Dungeon::Print(int n){
    
    for(auto i = link[n].begin(); i != link[n].end(); ++i){
        int o = *i;

        if(o!= -1){
            cout << n << " " << o << " \n";
            rmLink(n,o);
            Print(o);
        }  
    }
}

int Dungeon::makeDungeon(){
    int i = 0;
    int max = -1;
    //Adds links and sets edges as long as we're < vertex.
    while(i < vertex){
        int temp = rand() % (vertex-2);
        link[i].push_back(temp);
        link[temp].push_back(i);
        if(max <= temp){
            max = temp;
        }

        if(link[i] == link[temp]){
            continue;
        }
        i++;
    }
    
    //We find the largest linked value in our graph for our "game win" condition. This could be optimized but I was having issues getting it to work.
    for(auto i = link[0].begin(); i != link[0].end(); ++i){
        int o = *i;
        for (int i = 0; i < vertex; i++){
            if(std::max(o, i) > max){
                max = std::max(o, i);
            }else if(std::max(i, o) > max){
                max = std::max(i, o);
            }

        }
    }
    return max;
    
}

//Sets our difficulty of the dungeon, so we know how many paths to make (less chance of dead ends, more monsters to face, harder end boss, more harder mosters in general etc)
int Dungeon::dungeonDifficulty(){
    int choice;
    cout << "\nPlease choose a difficulty for this dungeon\n1. Easy\n2. Medium\n3. Hard\n";
    cin >> choice;
    this->difficulty = choice;
    switch(choice){
        case 1:
            return 5;
        case 2:
            return 15;
        case 3:
            return 25;
        default:
            cin.ignore(256, '\n');
            cin.clear();
            return 7;
    }
}

//Returns the difficulty set above
int Dungeon::getDiff() const{
    return difficulty;
}

//Gets our next path from current index, based on how many vertexes are connected
int Dungeon::getPath(int option, int index) const{
    int getPaths = 0;
    stack<int> temp;
    //We check if we fight out of combat with -99 to know we need to ignore and continue our loop
    if(option == -99){
        return -99;
    }
    //We set a stack to process our paths
    else if(option == 1){
        for (auto it = link[index].begin(); it != link[index].end(); it++){
            getPaths++;
            temp.push(*it);
        }
    //Depends on amount of paths available depends on if choice is even or not. If no paths then you hit a dead end and fight the boss
    cout << "\nBefore you lies " << getPaths << " path(s).";
        if(getPaths == 1){
            cout << " You continue forward.";
            return temp.top();
        }else if(getPaths > 1){
            int choice;
            for(int i = 0; i < getPaths; i++){
                cout << "\nPath " << i + 1;
            }
            cout << "\nChoose your path: ";
            cin >> choice;
            for(int i = 0; i < choice - 1; i++){
                temp.pop();
            }
            return temp.top();
            
        }else if(getPaths == 0){
            cout << "\nYou've hit a dead end!";
            return -100;
        }

        return temp.top();
    }
    return 0;
}

//To get our monster we subtract by the ASCII that we get from string to get our number (in this case it's 48)
int Dungeon::getMonster(int index){
    int parse = 0;

    if(difficulty == 1 || difficulty == 2){
        parse = 3;
    }else{
        parse = 4;
    }

    parse = index % parse;
    return parse;
}

//Logic for summoning our final boss monster
monster Dungeon::deadEnd(int difficulty){
    cout << "\nYou heard the thudding of footsteps echo behind you...\n";
    if(difficulty < 2){
        return monster::BEHEMOTH;
    }else{
        return monster::DRAGON;
    }
}