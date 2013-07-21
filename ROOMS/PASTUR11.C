/* pastur11.c */
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
    set_short("Southwest Pasture");
 
    set_long("\
This is the southwest section of a large pasture.  The pasture ends to the \n\
west in a barbed wire fence, continues for a little ways to the south, and\n\
stretches off into the distance to the south and east.\n");
 
   add_exit(ROOMS+"pastur06", "north");
   add_exit(ROOMS+"pastur16", "south");
   add_exit(ROOMS+"pastur12", "east");
   add_exit(ROOMS+"pastur07", "northeast");
   add_exit(ROOMS+"pastur17", "southeast");
 
   add_item("fence", "It looks sharp and nasty! Better leave it alone.");
 
   set_light(1);
   reset(0);
}
