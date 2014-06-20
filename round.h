#ifndef ROUND_H
#define ROUND_H

#include <memory>
#include <vector>
#include <iostream>
#include "world.h"

class entity;
typedef std::shared_ptr<entity> entity_ptr;

class round {
  public:
    round(std::ostream & out, std::ostream & err) :
      w(out, err, true) { }
    bool add_to_team_one(entity_ptr);
    bool add_to_team_two(entity_ptr);
    bool is_team_one_dead();
    bool is_team_two_dead();
    std::vector<entity_ptr> get_team_one();
    std::vector<entity_ptr> get_team_two();
    void draw(std::ostream&);
    bool update(std::istream&);
  private:
    world w;
    std::vector<entity_ptr> team_one;
    std::vector<entity_ptr> team_two;

};
#endif
