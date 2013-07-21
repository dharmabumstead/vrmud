/* pastur02.c */
#include "/players/slider/include/slider.h"
 
inherit "room/room";
 
reset(arg)
{
   while(!present("cow 2")) {
      move_object(clone_object(MONSTERS+"cow"), this_object());
   }
 
   if (arg) return;
}
 
create() {
   set_short("Northwest Pasture");
 
   set_long("\
You are at the northwest end of a large pasture.  The green splendor is \n\
marred only occasionally by the presence of a steaming pile of fresh cow\n\
'byproduct'.   The pasture stretches off into the distance to the south\n\
and east, continues to the west, and ends in some barbed wire fencing to\n\
the north.\n");
 
   add_exit(ROOMS+"pastur07", "south");
   add_exit(ROOMS+"pastur03", "east");
   add_exit(ROOMS+"pastur01", "west");
   add_exit(ROOMS+"pastur08", "southeast");
   add_exit(ROOMS+"pastur06", "southwest");
 
   add_item(({"fence", "fencing"}), "It looks painful.");
 
   set_light(1);
   reset(0);
}
 
