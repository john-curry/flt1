#include "entity.h"
#include "round.h"
#include <algorithm>
bool round::add_to_team_one(entity_ptr p) {
  if (!p->is_dead()) {
    w.add_entity(p);
    team_one.push_back(p);
    return true; 
  }
  return false;
}

bool round::add_to_team_two(entity_ptr p) {
  if (!p->is_dead()) {
    w.add_entity(p);
    team_two.push_back(p);
    return true; 
  }
  return false;
}

bool round::is_team_one_dead() {
  return std::all_of(team_one.begin(), team_one.end(),
    [] (entity_ptr ep) { 
      return ep->is_dead(); 
    });
}

bool round::is_team_two_dead() {
  return std::all_of(team_two.begin(), team_two.end(),
    [] (entity_ptr ep) { 
      return ep->is_dead(); 
    });
}

bool round::update(std::istream & in) {
  if (is_team_one_dead()) {
    w.send_msg("Team two wins!");
    return false;
  }
  if (is_team_two_dead()) {
    w.send_msg("Team one wins!");
    return false;
  }
  
  if (!w.update(in, w)) {
    w.log_msg("error has occured. exiting game.");
    return false; 
  }
  return true;
}


void round::draw(std::ostream & out) {
  w.draw(out);
}

std::vector<entity_ptr> round::get_team_one() {
  return team_one;
}

std::vector<entity_ptr> round::get_team_two() {
  return team_two;
}
