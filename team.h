#ifndef TEAM_H
#define TEAM_H

#include <string>
#include <vector>
#include <memory>
#include "entity.h"

class team { 
public:
  // everyone wants an awesome team name
  team(std::string name_) : name(name_) { }
  // team members will be added dynamically 
  void add_member(entity_ptr);
  // end of match condition
  bool is_team_dead();
private:
  std::vector<entity_ptr> team_;
};
#endif
