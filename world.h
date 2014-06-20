#ifndef WORLD_H
#define WORLD_H
#include <map>
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <queue>
#include <utility>
class entity;
class action;
typedef std::shared_ptr<entity> entity_ptr;
class world {
  public:
    world(std::ostream & out, std::ostream & err, bool);
    
    bool add_entity(std::string, entity_ptr);
    bool add_entity(entity_ptr); 
    entity_ptr get_entity(std::string); 
    bool update(std::istream&, world&);
    bool update(world&);
    void draw(std::ostream&);
     
    // send message to std::err
    void log_err(std::string);
    // send message to std::out for regular gameplay
    void send_msg(std::string);
    // log for debug purposes
    void log_msg(std::string);
    // turns input as a string into a vector of words
    // space signifies the end of a word
    std::map<std::string, entity_ptr> &get_world();
    // to be used in the updates of the entity_ptrs
    // to add the action of their choosing 
    void push_action(action, entity_ptr);
    // ran at end of turn 
    bool execute_turns();
  private:
    std::map<std::string, entity_ptr> w_intern;
    // actions to be taken at the end of the turn
    std::queue<std::pair<action, entity_ptr>> turn_actions;
    std::ostream * out; 
    std::ostream * err;
    // determines the output to the screen
    // if debug is on, extra game info will be printed 
    bool debug;
         
          
};
#endif
