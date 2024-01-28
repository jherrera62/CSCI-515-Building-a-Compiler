#ifndef WEAPON_H
#define WEAPON_H

#include<string>
using std::string;

class Weapon
{
  private:
    string type;
    int stamina_required;
    int hit_chance;
  public:
    Weapon(string wt,int sr,int hc); // constructor
    int get_stamina_required();
    bool did_you_hit();
    void display();
};
#endif
