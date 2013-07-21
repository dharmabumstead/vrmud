/* pastur06.c */
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
    set_short("Northwest Pasture");
 
    set_long("\
This is the northwest section of a large pasture.  The pasture ends to the \n\
west in a barbed wire fence, continues for a little ways to the north, and\n\
stretches off into the distance to the south and east.\n");
 
   add_exit(ROOMS+"pastur01", "north");
   add_exit(ROOMS+"pastur11", "south");
   add_exit(ROOMS+"pastur07", "east");
   add_exit(ROOMS+"pastur02", "northeast");
   add_exit(ROOMS+"pastur12", "southeast");
 
   add_item("fence", "It looks sharp and nasty! Better leave it alone.");
 
   set_light(1);
   reset(0);
}
