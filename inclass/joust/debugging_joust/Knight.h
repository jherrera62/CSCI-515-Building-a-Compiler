#include<string>

using namespace std;

#include "Weapon.h"

#ifndef KNIGHT_H
#define KNIGHT_H

class Knight
{
  private:
    string name;
    int stamina;
    bool on_horse;
    Weapon weapon_in_hand;

  public:
    Knight(string kn,int s,string wt,int sr,int hc); // constructor
    bool are_you_on_your_horse();
    bool are_you_exhausted();
    bool wield();
    void unhorse_yourself();
    void display();
};
#endif
