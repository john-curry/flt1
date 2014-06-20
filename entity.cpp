#include "entity.h"
#include "moveset.h"
#include "world.h"
#include <vector>
#include <cstdlib>
#include <sstream>
// implement this. check to see if
// health is less then max and greater then 0
void entity::check_stats() {
  if (health <= 0) health = 0;
     
}

bool entity::is_dead() {
  check_stats();
  return (health <= 0);
}

// set all stats and current health to max health
void entity::set_stats(stat max_health_,
                       stat defense_,
                       stat attack_damage_,
                       stat speed_,
                       stat magic_power_) {
    
  health =         max_health_;
  max_health =     max_health_;
  defense =        defense_;
  attack_damage =  attack_damage_;
  speed =          speed_;
  magic_power =    magic_power_;
  // obligatory stat check
  check_stats();
}
void entity::take_damage(stat damage) {
  check_stats();
  health -= damage;
  check_stats();
}


void entity::draw(std::ostream & out) {
  if (!is_dead()) { 
    out << name << " has " << health 
      << " health left." << std::endl;
  } else {
    out << name << " is dead." << std::endl;
  }
}

// soon to be depricated
// add_action is now the action adder of choice
void entity::add_actions() {
  moves.add_move(action(std::string("attack"), 
    [&] (entity_ptr ep) {
      ep->take_damage(attack_damage);
    }));

  moves.add_move(action(std::string("health"),
    [&] (entity_ptr ep) {
      ep->take_damage(-magic_power);
    }));
}

void entity::add_action(action a) {
  moves.add_move(a);
}

bool entity::update(world & w) {
  return true;  
}

bool entity::update(std::istream & in, world & w) {
  
  if (is_dead()) {
    // everything OK but this player is dead
    // so it does not get to interact 
    return true;
  }

  // printing user options to screen 
  std::stringstream turn_description;
  turn_description << name << " is selecting action from list:"
    << std::endl;
  w.send_msg(turn_description.str());
     
  std::stringstream input_opts; 
  for (int i = 0; i < moves.size(); ++i) {
    input_opts << i << ")" << moves.get_move(i).name << std::endl; 
  }
  w.send_msg(input_opts.str());
  // done printing
  
  // getting user input for action
  std::string input;
  std::getline(in, input);
  int move_sel = std::atoi(input.c_str());
  
  // showing user input for action 
  w.send_msg("Select player to act on:"); 
  std::stringstream ep_opts;
  auto wp = w.get_world();
  int j = 0;
  for (auto & p : wp) {
    ep_opts << j << ") " << p.second->name <<
      " has " << p.second->get_health() << " left" << std::endl;
    ++j; 
  }
  w.send_msg(ep_opts.str());

  // getting user input for action
  std::string ep_input;
  std::getline(in, ep_input);
  int sel = std::atoi(ep_input.c_str()); 
  int k = 0;
  // TODO: comment, document, understand 
  for (auto & l : w.get_world()) {
    if (k == sel) {
      w.push_action(moves.get_move(move_sel), l.second);
    }
    ++k;
  }
  if (sel > k) w.send_msg("GO AWAY YOU STUPID USER");
  if (sel < 0) w.send_msg("WHAT R U DOING");  
       
  return true;
}
