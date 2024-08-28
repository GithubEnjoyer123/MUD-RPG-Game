#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include <iostream>
#include <list>
#include <algorithm>
#include <fstream>
#include <cctype>
#include <cstdlib>
#include <iomanip>
#include <unordered_map>
#include <vector>
#include <stack>

using namespace std;

//Our class to use for all of our characters

enum class characterClass {FIGHTER = 1, ROGUE, MAGICIAN, CLERIC};
enum class monster {BAT, SKELETON, HELLHOUND, BEHEMOTH, DRAGON};

ostream& operator<<(ostream& out, const characterClass& characterClass);
ostream& operator<<(ostream& out, const monster& monster);

class character
{
public:
    character(string name, double hp, double mp, int strength, int dexterity, int intelligence, int speed, int endurance, int faith);
    virtual ~character() = default;
    double getHp() const;
    double getMp() const;
    int getDexterity() const;
    int getEndurance() const;
    int getFaith() const;
    int getIntelligence() const;
    int getSpeed() const;
    int getStrength() const;
    double specialAttack(characterClass charClass) const;
    
    string getName() const;
    string tostring() const;
    string printStory() const;

    int makeCharacter(character *&player);
    void setDexterity(int dexterity);
    void setEndurance(int endurance);
    void setFaith(int faith);
    void setHp(double hp);
    void setIntelligence(int intelligence);
    void setMp(double mp);
    void setSpeed(int speed);
    void setStrength(int strength);
    
    

protected:
    double hp;
    double mp;
    int dexterity;
    int endurance;
    int faith;
    int intelligence;
    int speed;
    int strength;
    int heals;
    int restores;
    int scrolls;
    string name;
};

//Derived classes
class level : public character{
public:
    level(int experience, int specials);
    int getLevel() const;
    int getSpecials() const;

    void setSpecial(int num);
    void setLevel(int experience);

private:
    int experience;
    int special;
};

class inventory : public character{
public:
    inventory(int heals, int restores, int scrolls);
    int getHeals() const;
    int getScroll() const;
    int getRestores() const;

    void setHeals(int heals);
    void setRestores(int restores);
    void setScrolls(int scrolls);
private:

};

class cleric : public character
{
public:
    cleric(string name);
    double heal();
    int attack();
};

class fighter : public character
{
public:
    fighter(string name);
    double strongAttack();
    int attack();
};

class magician : public character
{
public:
    magician(string name);
    double cast();
    int attack();
};

class rogue : public character
{
public:
    rogue(string name);
    double steal();
    int attack();
};

class Dungeon{
    public:
        Dungeon(int vertex);
        void rmLink(int x, int y);
        monster deadEnd(int difficulty);
        void Print(int n);
        
        int getMonster(int index);
        int makeDungeon();
        int getDiff() const;


        int dungeonDifficulty();
        int getPath(int option, int index) const;

    private:    
        int vertex;
        int difficulty;
        list<int>* link;
};

//These are some lazy functions from when I last made this project for OOP... Gonna leave em here
void combatLoop(monster monsterType, characterClass charClass, character* player, inventory* playerInv, level* playerLevel, bool fight);
void printChar();
int menu(character* player, inventory* inv, level* exp, bool fight);
void getExp(int exp);
int attack(int charClass);
int getMonsterHealth(int monster);
int getMonsterAttack(int monster);
int newExp(int monster);

#endif