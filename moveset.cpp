#include "moveset.h"
#include "entity.h"
bool moveset::add_move(action a) {
  actions.push_back(a);
  return true;
}

action &moveset::get_move(int i) {
  return actions[i];
}


