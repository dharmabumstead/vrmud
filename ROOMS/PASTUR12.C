/* pastur12.c */
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
    set_short("Southwest Pasture");
 
    set_long("\
This is the southwest section of a large pasture.  The center of the pasture\n\
lies to the east and northeast of here.  The pasture continues in all \n\
other directions.\n");
 
   add_exit(ROOMS+"pastur07", "north");
   add_exit(ROOMS+"pastur17", "south");
   add_exit(ROOMS+"pastur13", "east");
   add_exit(ROOMS+"pastur11", "west");
   add_exit(ROOMS+"pastur08", "northeast");
   add_exit(ROOMS+"pastur06", "northwest");
   add_exit(ROOMS+"pastur18", "southeast");
   add_exit(ROOMS+"pastur16", "southwest");
 
   set_light(1);
   reset(0);
}
