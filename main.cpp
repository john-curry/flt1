#include <vector>
#include <memory>
#include <string>
#include <queue>
#include <iostream>
#include <set>
#include <map>
#include <stdexcept>
#include "entity.h"
#include "world.h"
#include "round.h"
#include "player_factory.h"

int main() {
  using namespace std;
  vector<string> classes{ 
    "warrior" , "spirit", "asshole" 
  }; 
  world startup(cout, cerr, true);
   
  player_factory pf(classes);
  entity_ptr player_char1 = pf.make_player(startup, cin);
  entity_ptr player_char2 = pf.make_player(startup, cin);
  entity_ptr player_char3 = pf.make_player(startup, cin);
  
  entity_ptr en_one   = pf.make_warrior("grunt 1");
  entity_ptr en_two   = pf.make_warrior("grunt 2"); 
  entity_ptr en_three = pf.make_warrior("grunt 3"); 
  round r1(cout, cerr);
  r1.add_to_team_one(player_char1);
  r1.add_to_team_one(player_char2);
  r1.add_to_team_one(player_char3);
  r1.add_to_team_two(en_one  );
  r1.add_to_team_two(en_two  );
  r1.add_to_team_two(en_three);
  cout << "Round one START!" << endl;
  r1.draw(cout);   
  while (r1.update(cin)) {
    r1.draw(cout);
  }

  return 0;
}

