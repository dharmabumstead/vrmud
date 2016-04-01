/* pastur01.c */
#include "/players/slider/include/slider.h"
 
inherit "room/room";
 
reset(arg)
{
   while(!present("heifer")) {
      move_object(clone_object(MONSTERS+"heifer"), this_object());
   }
 
   if (arg) return;
}
 
init() {
   ::init();
}
 
create() {
    set_short("Northwest Pasture");
 
    set_long("\
You are at the northwest end of a large pasture.  The grass is a bit\n\
greener on this side of the pasture.  The pasture stretches off into the\n\
distance to the south and east, and ends in some barbed wire fencing to \n\
the north.\n");
 
    add_exit(ROOMS+"pastur02", "east");
    add_exit(ROOMS+"pastur06", "south");
    add_exit(ROOMS+"pastur07", "southeast");
 
    add_item(({"fence", "fencing"}), "It looks painful.");
 
    set_light(1);
    reset(0);
}
