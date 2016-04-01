/* pastur13.c */
#include "/players/slider/include/slider.h"
 
inherit "room/room";
 
reset(arg)
{
   while(!present("heifer 3")) {
      move_object(clone_object(MONSTERS+"heifer"), this_object());
   }
 
   if (arg) return;
}
 
create() {
    set_short("South Central Pasture");
 
    set_long("\
You are in the middle of a huge cow pasture.  It stretches in all directions\n\
from here.\n");
 
   add_exit(ROOMS+"pastur08", "north");
   add_exit(ROOMS+"pastur18", "south");
   add_exit(ROOMS+"pastur14", "east");
   add_exit(ROOMS+"pastur12", "west");
   add_exit(ROOMS+"pastur09", "northeast");
   add_exit(ROOMS+"pastur07", "northwest");
   add_exit(ROOMS+"pastur19", "southeast");
   add_exit(ROOMS+"pastur17", "southwest");
 
   set_light(1);
   reset(0);
}
