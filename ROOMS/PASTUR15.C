/* pastur15.c */
#include "/players/slider/include/slider.h"
 
inherit "room/room";
 
reset(arg)
{
   while(!present("heifer 2")) {
      move_object(clone_object(MONSTERS+"heifer"), this_object());
   }
 
   if (arg) return;
}
 
create() {
    set_short("Southeast Pasture");
 
    set_long("\
This is the southeast end of a large pasture.  The pasture is bounded by a\n\
barbed wire fence to the east.  The pasture continues to the south, and\n\
stretches into the distance to the north and west.\n");
 
   add_exit(ROOMS+"pastur10", "north");
   add_exit(ROOMS+"pastur20", "south");
   add_exit(ROOMS+"pastur14", "west");
   add_exit(ROOMS+"pastur09", "northwest");
   add_exit(ROOMS+"pastur19", "southwest");
 
   add_item("fence", "It's a nasty looking barbed wire fence.");
 
   set_light(1);
   reset(0);
}
