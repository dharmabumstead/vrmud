/* heifer.c
 * last updated 12/13/93
 */
 
#include "/players/slider/include/slider.h"
 
inherit "/obj/monster";
 
int drinks;
int call_flag;
string long_desc;
 
init() {
   ::init();
   add_action("milk_cow", "milk");
   if((!present("cowpie 5", THIS_ENV)) && (call_flag == 0)) {
      call_flag = 1;
      call_out("cow_poop", ((random(40)) + 20));
   }
}
 
create() {
    ::create();
    drinks = 3;
    call_flag = 0;
    set_id("heifer");
    set_short("a heifer");
    set_long("\
A fine milking heifer!  Kind of makes you thirsty....maybe you could?....nah!\n");
    set_level(2);
    set_spell_chance(10);
    set_spell_dam(0);
    set_ac(3);
    set_wc(6);
    add_money(60);
}
 
milk_cow(str) {
 
   if (!id(str)) return(0);
 
   if(drinks == 0) {
      write("The poor thing's been milked dry! Give it time to make more!\n");
   } else {
      write("You greedily suck the milk right out of the heifer's udder!\n");
      say(PLAYER_NAME + " milks the heifer!\n", PLAYER);
      PLAYER->heal_self(3);
      drinks--;
   }
   return(1);
}
 
cow_poop() {
   object cowpie;
 
 
   /* The cow has a 50% chance of shitting */
   if((random(100)) < 51) {
 
      /* Make sure there are no more than 5 cowpies in the room */
      if(!present("cowpie 5", THIS_ENV)) {
 
         tell_room(THIS_ENV,"The heifer dumps a big steaming load!\n");
 
         cowpie = clone_object(OBJ+"cowpie");
 
         move_object(cowpie, THIS_ENV);
      }
   }
   call_flag = 0;
}
 
