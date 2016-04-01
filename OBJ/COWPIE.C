#include "/players/slider/include/slider.h"
inherit "std/object";

#define LOGFILE "slider.newbie"
 
 
create() {
   set_id(({ "cowpie"}));
   set_short("a cowpie");
   set_long("A big, steaming cowpie.  Very rich in nutrients!\n");
   set_value(5);
   add_property("getable"); /* Allow us to be picked up */
}
 
 
init() {
   add_action("eat_cowpie", "eat");
}
 
eat_cowpie(str) {
   if(!id(str)) return 0;

   if(PLAYER->query_level() >5) {
      write("You attempt to eat the cowflop.  Blech!  You feel ill!\n");
      say(PLAYER_NAME+" tries to eat a cowpie and gets sick!!\n");
	PLAYER->add_hp(5);
	PLAYER->add_sp(3);
      log_file(LOGFILE, ctime()+" "+PLAYER_NAME+"("+PLAYER->query_level()+") "+
         "tries to eat a cowpie!\n");
      return(1);
   }
 
   write("\
You plug your nose, close your eyes, and gulp it down.  Hey...that wasn't\n\
so bad!  You feel.....stronger!\n");
   say(capitalize(this_player()->query_real_name())+" wolfs down a cowpie!\n");
   this_player()->heal_self(3);
   destruct(this_object());
   return(1);
}
 
