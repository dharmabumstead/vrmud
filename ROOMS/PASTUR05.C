/* pastur05.c */
#include "/players/slider/include/slider.h"
 
inherit "room/room";
 
reset(arg)
{
   while(!present("heifer")) {
      move_object(clone_object(MONSTERS+"heifer"), this_object());
   }
 
   if (arg) return;
}
 
create() {
    set_short("Northeast Pasture");
 
    set_long("\
This is the northeast end of a large pasture.  The pasture is bounded by a\n\
barbed wire fence to the north and east.  The pasture stretches into the\n\
distance to the south and west.\n");
 
   add_exit(ROOMS+"pastur10", "south");
   add_exit(ROOMS+"pastur04", "west");
   add_exit(ROOMS+"pastur09", "southwest");
 
   add_item("fence", "It's a nasty looking barbed wire fence.");
 
   set_light(1);
   reset(0);
}
