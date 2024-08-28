#include "character.h"

//Initialize our function values
character::character(string name, double hp, double mp, int strength, int dexterity, int intelligence, int speed, int endurance, int faith)
    : name(name), hp(hp), mp(mp), strength(strength), dexterity(dexterity), intelligence(intelligence), speed(speed), endurance(endurance), faith(faith) {}

cleric::cleric(string name) : character(name, 200, 200, 5, 10, 8, 16, 5, 16) {}

fighter::fighter(string name) : character(name, 300, 0, 16, 10, 5, 8, 15, 5) {}

magician::magician(string name) : character(name, 250, 200, 5, 10, 16, 16, 5, 8) {}

rogue::rogue(string name) : character(name, 200, 0, 10, 16, 16, 15, 8, 5) {}

//All of our getters are below
double character::getHp() const
{
    return hp;
}

double character::getMp() const
{
    return mp;
}

int character::getDexterity() const
{
    return dexterity;
}

int character::getEndurance() const
{
    return endurance;
}

int character::getFaith() const
{
    return faith*3;
}

int character::getIntelligence() const
{
    return intelligence;
}

int character::getSpeed() const
{
    return speed;
}

int character::getStrength() const
{
    return strength;
}

string character::getName() const
{
    return name;
}

//our tostring to print character stats. Using our substr below we set our precision value of double to 2 decimal places.
string character::tostring() const
{
    return "\n" + name + " stats:" +
    "\nHP: " + to_string(hp).substr(0, to_string(hp).find(".") + 2 + 1) + 
    "\nMP: " + to_string(mp).substr(0, to_string(mp).find(".") + 2 + 1) + 
    "\nStrength: " + to_string(strength) + 
    "\nDexterity: " + to_string(dexterity) + 
    "\nIntelligence: " + to_string(intelligence) + 
    "\nSpeed: " + to_string(speed) +
    "\nEndurance: " + to_string(endurance) +
    "\nFaith: " + to_string(faith) +
    "\n\n";
}

//Our functions for the 4 special attacks for our characters and their values
double cleric::heal(){
    return faith;
}

double fighter::strongAttack(){
    return 50;
}

double magician::cast(){
    return 80;
}

double rogue::steal(){
    double number = (rand() / (double)RAND_MAX) * (50 - 10) + 10;
    number = number / 100;
    return number * (dexterity + speed + intelligence);
}

int cleric::attack(){
    return 15;
}

int fighter::attack(){
    return 25;
}

int magician::attack(){
    return 25;
}

int rogue::attack(){
    return 15;
}

//Our setters, using a this pointer to point to the character class values so there is no ambiguity
void character::setDexterity(int dexterity)
{
    this->dexterity = dexterity;
}

void character::setEndurance(int endurance)
{
    this->endurance = endurance;
}

void character::setFaith(int faith)
{
    this->faith = faith;
}

void character::setHp(double hp)
{
    this->hp = hp;
}

void character::setIntelligence(int intelligence)
{
    this->intelligence = intelligence;
}

void character::setMp(double mp)
{
    this->mp = mp;
}

void character::setSpeed(int speed)
{
    this->speed = speed;
}

void character::setStrength(int strength)
{
    this->strength = strength;
}

level::level(int experience, int specials) : character("",0,0,0,0,0,0,0,0){
    this->experience = experience;
    this->special = specials;
}

int level::getLevel() const{ 
    return experience; 

}
int level::getSpecials() const{ 
    return special; 
}

void level::setLevel(int exp){ 
    int temp = getLevel();
    experience = experience + exp;
    if(getLevel() > temp){
        special += 1;
    } 
}

void level::setSpecial(int num){
    special -= num;
}


inventory::inventory(int heals, int restores, int scrolls) : character("",0,0,0,0,0,0,0,0){
    this->heals = heals;
    this->restores = restores;
    this->scrolls = scrolls;
}


void inventory::setHeals(int heals){ 
    this->heals = heals; 
}

void inventory::setRestores(int restores){
     this->restores = restores; 
}
void inventory::setScrolls(int scrolls){ 
    this->scrolls = scrolls; 
}

int inventory::getScroll() const {
    return scrolls;
}

int inventory::getHeals() const{
    return heals;
}

int inventory::getRestores() const{
    return restores;
}

//Prints our list of class choices when creating character
void printChar(){
    cout << "Choose your class\n1.Fighter\n2.Rogue\n3.Magician\n4.Cleric\n";
};

//This is our menu block during our feedback loop
int menu(character* player, inventory* inv, level* exp, bool fight){
    while(true){
        int choice;
        cout << "\n1. Check inventory\n2. Check Specials\n3. Fight\n4. Current Hp\n";
        if(fight == false){
            cout << "5. Move Forward\n";
        }
        cin >> choice;
        if(choice > 5 || choice < 1 || cin.fail()){
            cin.clear();
            cin.ignore(256, '\n');
            
            cout << "\nInvalid input.";
            continue;
        }
        switch(choice){
            case 1:
                cout << "\nScrolls: " << inv->getScroll() << "\nPotions: " << inv->getHeals() << "\nRestores: " << inv->getRestores();
                continue;
            case 2:
                cout << "\nSpecials remaining: " << exp->getSpecials();
                if(exp->getSpecials() > 0 && fight == true){
                    cout << "\nUse Special Attack (Y/N)?";
                    char select;
                    cin >> select;
                    if(select == 'y' || select == 'Y'){
                        return -50;
                    }else if(select == 'n' || select == 'N'){
                        continue;
                    }else{
                        cin.ignore(256, '\n');
                        cin.clear();
                    } 
                }
                continue;
            case 3:
                return -99;
            case 4:
                cout << "\nCurrent Health: " << player->getHp();
                continue;
            case 5:
                if(fight == true){
                    continue;
                }
                return 1;
        }
    }
    return 0;
};

//Our monsters health values, can be updated easily by changing enum values
int getMonsterHealth(int monster){
    switch(monster){
        case 0:
            return 10;
        case 1:
            return 30;
        case 2:
            return 40;
        case 3:
            return 75;
        case 4:
            return 150;
        default:
            return 0;
    }
};

//Our monsters damage values
int getMonsterAttack(int monster){
    switch(monster){
        case 0:
            return 10;
        case 1:
            return 14;
        case 2:
            return 20;
        case 3:
            return 40;
        case 4:
            return 80;
        default:
            return 0;
    }
};


//Finds our damage value for our selected class
int attack(int charClass){
    fighter myFighter("");
    rogue myRogue("");
    magician myMagician("");
    cleric myCleric("");
    switch(charClass){
        case 1:
            return myFighter.attack();
        case 2:
            return myRogue.attack();
        case 3:
            return myMagician.attack();
        case 4:
            return myCleric.attack();
        default:
            return 0;
    }
}

//Exp values for every monster
int newExp(int monster){
    switch(monster){
        case 0:
            return 50;
        case 1:
            return 100;
        case 2:
            return 200;
        case 3:
            return 350;
        case 4:
            return 1200;
        default:
            return 0;
    }
}

//Prints our current level based on exp
void getExp(int exp){
    if(exp < 100){
        cout << "\nYou are level 1";
    }
    else if(exp < 500){
        cout << "\nYou are level 2.";
    }else if(exp < 900){
        cout << "\nYou are level 3.";
    }else if(exp < 1900){
        cout << "\nYou are level 4.";
    }else if(exp < 3000){
        cout << "\nYou are level 5.";
    }
}

//Ostream prints out correct character dependent on class taken
ostream& operator<<(ostream& out, const characterClass& characterClass){
    if (characterClass == characterClass::FIGHTER) {out << "Fighter";}
    if (characterClass == characterClass::ROGUE){out << "Rogue";}
    if (characterClass == characterClass::MAGICIAN){out << "Magician";}
    if (characterClass == characterClass::CLERIC){out << "Cleric";}
    return out;  
}

//Ostream prints out correct monster depending on current monster being fought
ostream& operator<<(ostream& out, const monster& monster){
    if (monster == monster::BAT) {out << "Bat";}
    if (monster == monster::SKELETON){out << "Skeleton";}
    if (monster == monster::HELLHOUND){out << "Hellhound";}
    if (monster == monster::BEHEMOTH){out << "Behemoth";}
    if (monster == monster::DRAGON){out << "Dragon";}
    return out;  
}

//This gets the value for our special attack
double character::specialAttack(characterClass charClass) const{
    double damage = 0;
    switch(static_cast<int>(charClass)){
        case 1:{
            fighter attack("");
            damage = attack.strongAttack();
            break;
        }
        case 2:{
            rogue attack2("");
            damage = attack2.steal();
            break;
        }
        case 3:{
            magician attack3("");
            damage = attack3.cast();
            break;
        }
        case 4:{
            cleric attack4("");
            damage = attack4.heal();
            break;
        }
    }
    return damage;
}

int character::makeCharacter(character *&player){
    //This loop block takes care of creating a new character
    int choice;
    while(true){
        char decision;
        cout << "Enter your characters name: ";
        getline(cin, name);
        printChar();
        cin >> choice;  
        if(choice == 1){
            player = new fighter(name);
            cout << player->tostring();
        }else if(choice == 2){
            player = new rogue(name);
            cout << player->tostring();
        }else if(choice == 3){
            player = new magician(name);
            cout << player->tostring();
        }else if(choice == 4){
            player = new cleric(name);
            cout << player->tostring();
        }else{
            cin.ignore(256, '\n');
            cin.clear();
            cout << "Please enter a number 1-4";
            delete player;
            continue;
        }

        //Confirmation, goes to start of loop to start over if necessary
        cout << "\nAre you sure about your choices? (Y/N) ";
        cin >> decision;
        if(decision == 'y' || decision == 'Y'){
            break;
        }else if(decision == 'n' || decision == 'N'){
            cin.ignore(256, '\n');
            cin.clear();
            continue;
        }else{
            cin.ignore(256, '\n');
            cin.clear();
            cout << "Invalid choice. Restarting character creation process\n";
            continue;
        }
    }

    //Saves our class choice for use later
    return choice;
}

string character::printStory() const{
    const char *text = "Our hero finds themselves in a dimly lit corridor. Behind them, pitch black. Forward, dimly lit with torches. " 
    "A roar and a thud can be heard from behind you. The smell of old water, and disease fills the air. "  
    "You must find your way out of this dungeon, before whatever made that noise comes for your next.\n";
    return text;
}

//Our main loop for combat
void combatLoop(monster monsterType, characterClass charClass, character* player, inventory* playerInv, level* playerLevel, bool fight){
    int mhealth = getMonsterHealth(static_cast<int>(monsterType));
    int mattack = getMonsterAttack(static_cast<int>(monsterType));
    cout << "\nA " << monsterType << " has appeared! What will you do?\n";

    //Loops that plays while monster health is greater than 0
    while(mhealth > 0){

        //We enter our menu here, not exiting until we press fight
        int special = menu(player, playerInv, playerLevel, fight);

        //We fight the monster, both of us dealing 1 attack. The monster goes first
        cout << "\nYou get attacked! Your new health: " << player->getHp() - mattack;
        player->setHp(player->getHp() - mattack);

        //If your health drops below 0 after the monster attack, the program exits and you die (lose)
        if(player->getHp() < 0){
            cout << "\nYou have been defeated. Better luck next time!";
            delete player;
            exit(0);
        }

        if(special == -50){
            if(static_cast<int>(charClass) != 4){
                mhealth -= player->specialAttack(charClass);
                cout << "\nYou use your special attack on " << monsterType << "! their new health: " << mhealth;
            }else{
                playerInv->setHeals(playerInv->getHeals() + 1);
                cout << "\nYour create a health potion! Use it wisely...";
            }
            playerLevel->setSpecial(1);
            goto specialAtt;
        }

        mhealth -= attack(static_cast<int>(charClass));
        cout << "\nYou attack the " << monsterType << "! their new health: " << mhealth;

        specialAtt:
        //Asks if you'd like to heal if you have health potions
        while(playerInv->getHeals() > 0){
            char healChoice;
            cout << "\nEnd of round. Would you like to use a health potion? (Y/N) ";
            cin >> healChoice;
            if(healChoice == 'y' || healChoice == 'Y'){
                player->setHp(player->getHp() + 50);
                playerInv->setHeals(playerInv->getHeals() - 1);
                break;
            }else{
                cin.clear();
                cin.ignore(256, '\n');
                break;
            }
        }
    }
    playerLevel->setLevel(newExp(static_cast<int>(monsterType)));
    getExp(playerLevel->getLevel());
    return;
}
