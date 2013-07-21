/* garg005.c */
#include "/players/slider/include/slider.h"

inherit "room/room";
reset(arg)
{ 
   while(!present("gargoyle 6"))
      move_object(clone_object(MONSTERS+"babygar2"), this_object());
      
   if (arg) return;
}


create() {
    set_short("West Forest Clearing");

    set_long(
"You are on the west side of the forest clearing.  The thick vegetation\n"+
"prevents movement in any direction but east, towards the center of the\n"+
"clearing.\n");
    add_exit(ROOMS+"garg002", "east");
    set_light(1);
    reset(0);
}

