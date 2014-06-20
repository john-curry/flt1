#ifndef PLAYER_FACTORY_H
#define PLAYER_FACTORY_H
#include "entity.h"
#include "world.h"
#include "moveset.h"
#include <iostream>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <functional>
class player_factory {
  public:
    player_factory(std::vector<std::string> classes_) :
      classes(classes_) { }
    // entry point for starting a new game
    // gives the players options for making a new character
    entity_ptr make_player(world&, std::istream&);
    // does what is says 
    entity_ptr make_warrior(std::string name);
    entity_ptr make_healer(std::string name);
    // based on the type string, it sets the stats
    // and name of an entity and returns it 
    entity_ptr setup_player(std::string name, 
      std::string type);
    std::vector<std::string> classes;
};

#endif
