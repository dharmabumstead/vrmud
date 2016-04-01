/* pastur16.c */
#include "/players/slider/include/slider.h"
 
inherit "room/room";
 
reset(arg)
{
   while(!present("heifer")) {
      move_object(clone_object(MONSTERS+"heifer"), this_object());
   }
 
}
 
init() {
   ::init();
}
 
create() {
    set_short("Southwest Pasture");
 
    set_long("\
You are at the southwest end of a large pasture.  The grass is a bit\n\
greener on this side of the pasture.  The pasture stretches off into the\n\
distance to the north and east, and ends in some barbed wire fencing to \n\
the south.\n");
 
    add_exit(ROOMS+"pastur17", "east");
    add_exit(ROOMS+"pastur11", "north");
    add_exit(ROOMS+"pastur12", "northeast");
 
    add_item(({"fence", "fencing"}), "It looks painful.");
 
    set_light(1);
    reset(0);
}
