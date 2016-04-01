/* garg002.c */
#include "/players/slider/include/slider.h"

inherit "room/room";

reset(arg)
{ 
   while(!present("baby 6")) {
      move_object(clone_object(MONSTERS+"babygar1"), this_object());
   }
      
   if (arg) return;
}

create() {
    set_short("Forest Clearing");

    set_long(
"You are now in the middle of a large clearing hidden in the forest.  A canopy\n"+
"of branches overhead shelters the entire clearing from the elements.  The\n"+
"stretches north, east, and west here, as well as back to the south.\n");
    add_exit(ROOMS+"garg003", "north");
    add_exit(ROOMS+"garg004", "east");
    add_exit(ROOMS+"garg005", "west");
    add_exit(ROOMS+"garg001", "south");
    set_light(1);
    reset(0);
}

