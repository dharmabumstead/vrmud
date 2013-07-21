/* path6-3.c */
#include "/players/slider/include/slider.h"

inherit "room/room";

reset(arg)
{
   if(!present("zombie"))
      move_object(clone_object(MONSTERS+"firezomb"), this_object());

   if (arg) return;
}

create() {
    set_short("Burnt Path 3");

    set_long(
"The devastation is almost complete here.  Nothing remains of the forest\n"+
"at this point save for a few smoking tree stumps.  The scorched eartth\n"+
"crunches under your feet as you make your way along here.\n");
    add_exit(ROOMS+"path6-4", "north");
    add_exit(ROOMS+"path6-2", "south");

    set_light(1);
    reset(0);
}

