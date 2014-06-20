#include "player_factory.h"
// the interface for the player factory
// prompts the user for name and type of the character being created
// takes a world and an input stream 
entity_ptr player_factory::make_player(world & w, std::istream & in) {
  // prompt user for name of the character 
  std::string name;
  w.send_msg("Enter your character's name: "); 
  std::getline(in, name);
  // done name input
  
  // output the classes to output
  std::stringstream class_list;
  // TODO: change this to internal classes
  // string vector
  std::vector<std::string> pclasses{ 
    "warrior" , 
    "healer"   ,
    "sorcerer",
    "healer"  
  };

  // build string stream for output
  w.send_msg("class options are: "); 
  int index = 1;
  for (auto s : pclasses) {
    class_list << index << ") " << s << std::endl;
    ++index; 
  }
  // done build
  // getting class choice
  w.send_msg(class_list.str());
  w.send_msg("enter choice"); 
  std::string class_;
  std::getline(in, class_);
  // TODO: add a more rigerous way of selecting input 
  size_t sel = std::atoi(class_.c_str());
  // BUG: cant select anything higher then 2
  // BUG: 0 for player selection crashes game 
  std::string class_choice; 
  if (sel == 0) {
    class_choice = pclasses[0];
    w.log_msg("selection not within class list size");
    w.log_msg("going with default warrior class");     
  } else if (sel < pclasses.size() - 1) {
    class_choice = pclasses[sel - 1];   
  } else {
    class_choice = pclasses[0];
    w.log_msg("selection not within class list size");
    w.log_msg("going with default warrior class"); 
  }
  // done getting class choice 
  w.log_msg(name + 
            " is the name with class " + 
            class_choice
  ); 
  
  entity_ptr ret = setup_player(
    name, class_choice);

  return ret;
}

// premade warrior class 
entity_ptr player_factory::make_warrior(std::string name) {
  entity_ptr ep = std::make_shared<entity>(name, "warrior");
  ep->set_stats(100, 50, 80, 30, 5);
  ep->add_action(action("attack", [&] (entity_ptr e) {
    e->take_damage(ep->get_attack_damage());
  }));
  return ep;
}

entity_ptr player_factory::make_healer(std::string name) {
  entity_ptr ep = std::make_shared<entity>(name, "healer");
  ep->set_stats(70, 5, 5, 40, 100);
  ep->add_action(action("attack", [&] (entity_ptr e) {
    e->take_damage(ep->get_attack_damage());
  }));
  ep->add_action(action("heal", [&] (entity_ptr e) {
    e->set_health(e->get_health() + ep->get_magic_power());
  }));
  return ep;
}

entity_ptr player_factory::setup_player(std::string name, std::string type) {
  if (type == "warrior") 
    return make_warrior(name);
  if (type == "healer")
    return make_healer(name);
  return make_warrior(name);
}

