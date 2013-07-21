/* pastur17.c */
#include "/players/slider/include/slider.h"
 
inherit "room/room";
 
reset(arg)
{
   while(!present("heifer 2")) {
      move_object(clone_object(MONSTERS+"heifer"), THIS);
   }
 
   if (arg) return;
}
 
create() {
   set_short("Southwest Pasture");
 
   set_long("\
You are at the southwest end of a large pasture.  The green splendor is \n\
marred only occasionally by the presence of a steaming pile of fresh cow\n\
'byproduct'.   The pasture stretches off into the distance to the north\n\
and east, continues to the west, and ends in some barbed wire fencing to\n\
the south.\n");
 
   add_exit(ROOMS+"pastur12", "north");
   add_exit(ROOMS+"pastur18", "east");
   add_exit(ROOMS+"pastur16", "west");
   add_exit(ROOMS+"pastur13", "northeast");
   add_exit(ROOMS+"pastur11", "northwest");
 
   add_item(({"fence", "fencing"}), "It looks painful.");
 
   set_light(1);
   reset(0);
}
