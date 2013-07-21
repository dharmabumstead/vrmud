inherit "/std/light";
inherit "/std/light";
/* cow.c
 * last updated 12/12/93
 */
 
#include "/players/slider/include/slider.h"
 
inherit "/obj/monster";
 
int call_flag;
 
create() {
   ::create();
   call_flag = 0;
   set_id("cow");
   set_short("a cow");
   set_long("\
It's your average, everyday cow.  It eyes you with soft brown eyes as it\n\
contentedly munches its cud.  It'll probably be steaks pretty soon....\n");
   set_level(1);
   set_spell_chance(10);
   set_spell_dam(0);
   set_ac(3);
   set_wc(5);
   add_money(30);
}
 
init() {
   ::init();
 
   if((!present("cowpie 5", THIS_ENV)) && (call_flag == 0)) {
      call_flag = 1;
      call_out("cow_poop", ((random(40)) + 20));
   }
}
 
cow_poop() {
   object cowpie;
 
   /* The cow has a 50% chance of shitting */
   if((random(100)) < 51) {
 
      /* Make sure there are no more than 5 cowpies in the room */
      if(!present("cowpie 5", THIS_ENV)) {
 
         tell_room(THIS_ENV, "The cow dumps a big steaming load!\n");
 
         cowpie = clone_object(OBJ+"cowpie");
 
         move_object(cowpie, THIS_ENV);
      }
   }
   call_flag = 0;
}
 
