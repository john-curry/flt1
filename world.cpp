#include "world.h"
#include "entity.h"
#include "moveset.h"
#include <algorithm>
#include <sstream>
// constructor with output and errors 
// bool to signify  debug
world::world(std::ostream & out_, std::ostream & err_, 
             bool debug_) {
  out = &out_; err = &err_; 
  debug = debug_;
}

std::map<std::string, entity_ptr> &world::get_world() {
  return w_intern;
}

void world::log_err(std::string msg) {
  if (debug and err) { *err << msg << std::endl; }
}

void world::send_msg(std::string msg) {
  if (out) *out << msg << std::endl;
}

void world::log_msg(std::string msg) {
  if (out and debug) { *out << msg << std::endl; }
}

// add a thing to the world
bool world::add_entity(std::string k, entity_ptr e) {
  if (w_intern.find(k) == w_intern.end()) {
    w_intern[k] = e;
  } else { 
    log_err("entity already added"); 
    return false; 
  }
  return true;
}
 
// simpler adding
bool world::add_entity(entity_ptr e) {
  return add_entity(e->name, e);
}
// return an an entity of certain name
// return null if not there
entity_ptr world::get_entity(std::string k) {
  if (w_intern.find(k) != w_intern.end()) {
    return w_intern[k];
  }
  else { return nullptr; }
}

void world::push_action(action a, entity_ptr ep) {
  turn_actions.push(
    std::make_pair(a, ep)
  );
}

bool world::execute_turns() {
  // do the actions that the users told the players
  // to do
  // with hopefully be in the right order since update
  // sorts the entities before calling their update
  while (!turn_actions.empty()) {
    auto curr = turn_actions.front();
    std::stringstream turn_desc; 
    turn_desc << 
      curr.first.name << "ing " <<
      curr.second->name << std::endl;
    // TODO: add more description about the action taking place
    send_msg(turn_desc.str());
    curr.first.call(curr.second);
    turn_actions.pop(); 
  }
  return true;
}

// update fn
bool world::update(std::istream & in, world & w) {
    std::vector<entity_ptr> sorted_world;
    for (auto &e : w_intern) {
      sorted_world.push_back(e.second);
    }
    std::sort(
      sorted_world.begin(), 
      sorted_world.end(), 
      [] (entity_ptr p1, entity_ptr p2) {
        return p1 > p2; 
      }
    ); 
    if (&w) {
      for (auto &e : sorted_world) {
        if (!(e->update(in, w))) return false;
         
    }
  }
  execute_turns();
  return true;
}

// draw fn
void world::draw(std::ostream & os) {
  for (auto &e : w_intern) {
    e.second->draw(os);
  }
}

