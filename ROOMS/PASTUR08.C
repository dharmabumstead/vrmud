/* pastur08.c */
#include "/players/slider/include/slider.h"
 
inherit "room/room";
 
reset(arg)
{
   while(!present("cow 3")) {
      move_object(clone_object(MONSTERS+"cow"), this_object());
   }
 
   if (arg) return;
}
 
create() {
    set_short("Nort Central Pasture");
 
    set_long("\
You are in the middle of a huge cow pasture.  It stretches in all directions\n\
from here.\n");
 
   add_exit(ROOMS+"pastur03", "north");
   add_exit(ROOMS+"pastur13", "south");
   add_exit(ROOMS+"pastur09", "east");
   add_exit(ROOMS+"pastur07", "west");
   add_exit(ROOMS+"pastur04", "northeast");
   add_exit(ROOMS+"pastur02", "northwest");
   add_exit(ROOMS+"pastur14", "southeast");
   add_exit(ROOMS+"pastur12", "southwest");
 
   set_light(1);
   reset(0);
}
