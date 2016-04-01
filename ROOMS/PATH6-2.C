/* path6-2.c */
#include "/players/slider/include/slider.h"

inherit "room/room";

reset(arg)
{
   if(!present("wolf"))
      move_object(clone_object(MONSTERS+"firewolf"), this_object());

   if (arg) return;
}

create() {
    set_short("More Burnt Path");

    set_long(
"The charred trail continues to the north and south here.  The temperature\n"+
"seems to rise to the north, and you think you hear a strange crackling\n"+
"noise coming from that direction.  The trail continues north and south.\n");
    add_exit(ROOMS+"path6-3", "north");
    add_exit(ROOMS+"path6-1", "south");

    set_light(1);
    reset(0);
}

