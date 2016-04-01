/* garg004.c */
#include "/players/slider/include/slider.h"

inherit "room/room";

reset(arg)
{ 
   while(!present("baby 6")) {
      move_object(clone_object(MONSTERS+"babygar2"), this_object());
   }
      
   if(!present("squish"))
      move_object(clone_object(OBJ+"squish"), this_object());
      
   if (arg) return;
}

create() {
    set_short("East Forest Clearing");

    set_long(
"You are on the east side of the forest clearing.  The thick vegetation\n"+
"prevents movement in any direction but west, towards the center of the\n"+
"clearing.\n");
    add_exit(ROOMS+"garg002", "west");
    set_light(1);
    reset(0);
}

