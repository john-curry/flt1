#ifndef MOVESET_H
#define MOVESET_H
#include <memory>
#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <functional>

class entity;
class action;
typedef std::shared_ptr<entity> entity_ptr; 

class moveset {
  public:
    // for ease of writing and consiseness
    moveset() = default;
    bool add_move(action);
    action &get_move(int i);
    int size() { return actions.size(); }
  private:
    std::vector<action> actions;
};

class action {
  public: 
   action(std::string name_, std::function<void (entity_ptr)> actn_) :
     name(name_) , actn(actn_) { }
   const std::string name;
   void call(entity_ptr & ep) { actn(ep); }
  private:
   std::function<void (entity_ptr)> actn;
};
#endif
