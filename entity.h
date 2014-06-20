#ifndef ENTITY_H
#define ENTITY_H
#include <functional>
#include <string>
#include <map>
#include <iostream>
#include <memory>
#include <set>
#include "moveset.h"
class world;

class entity {
public:
  typedef int stat;
  typedef std::shared_ptr<entity> entity_ptr;
   
  entity(std::string name_, std::string type_) : 
    name(name_) , type(type_) { }
   // players and enemys can identify each other
  const std::string name;
  
   // add some flavor with types!!
  const std::string type;
  
  // game requires player be dead for game to end
  virtual bool is_dead();
  // dynamic setting of stats  (hahaha dynamic)
  virtual void set_stats(stat, stat, stat, stat, stat);
  // generic take damage cause i have no idea
  // what this part will actually look like 
  virtual void take_damage(stat); 
  virtual void draw(std::ostream&);
  // depricated in favor of update with istream input
  virtual bool update(world&);
  virtual bool update(std::istream&, world&);
  virtual void add_actions();  
  virtual void add_action(action); 
  virtual stat get_speed() const { return speed; }
  // obligatory getters
  stat get_health()       { return health; } 
  stat get_max_health()   { return max_health; }
  stat get_defense()      { return defense; } 
  stat get_attack_damage(){ return attack_damage; }
  stat get_speed()        { return speed; }
  stat get_magic_power()  { return magic_power; }
  // setters
  void set_health(int h)  { health = h; } 

private:
  stat health;
  stat max_health;
  stat defense;
  stat attack_damage;
  stat speed;  
  stat magic_power;
  moveset moves;
     
  // make sure stats are 'regular' 
  virtual void check_stats();
};
#endif
