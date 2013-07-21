/* pastur10.c */
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
    set_short("Northeast Pasture");
 
    set_long("\
This is the northeast end of a large pasture.  The pasture is bounded by a\n\
barbed wire fence to the east.  The pasture continues to the north, and\n\
stretches into the distance to the south and west.\n");
 
   add_exit(ROOMS+"pastur05", "north");
   add_exit(ROOMS+"pastur15", "south");
   add_exit(ROOMS+"pastur09", "west");
   add_exit(ROOMS+"pastur04", "northwest");
   add_exit(ROOMS+"pastur14", "southwest");
 
   add_item("fence", "It's a nasty looking barbed wire fence.");
 
   set_light(1);
   reset(0);
}
