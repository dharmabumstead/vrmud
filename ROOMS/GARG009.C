/* garg009.c */
#include "/players/slider/include/slider.h"

inherit "room/room";

reset(arg)
{
   if(!present("captain")) {
      move_object(clone_object(MONSTERS+"garcapt"), this_object());
    }

   if (arg) return;
}


create() {
    set_short("Gargoyle Cavern");

    set_long(
"The temperature seems to have dropped several degrees here.  As your eyes\n"+
"adjust to the darkness, you notice more corpses littering the floor of the\n"+
"cave here.  A steady dripping sound emanates from somewhere.  The cave \n"+
"continues east, west,  down into the darkness, and south to an entryway.\n");
    add_exit(ROOMS+"garg009a", "east");
    add_exit(ROOMS+"garg009b", "west");
    add_exit(ROOMS+"garg010", "down");
    add_exit(ROOMS+"garg008", "south");
    set_light(1);
    reset(0);
}

