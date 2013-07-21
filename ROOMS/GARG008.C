/* garg008.c */
#include "/players/slider/include/slider.h"

inherit "room/room";

reset(arg)
{
   while(!present("lieutenant 2")) {
      move_object(clone_object(MONSTERS+"garlieut"), this_object());
    }

   if (arg) return;
}


create() {
    set_short("Gargoyle Entry");

    set_long(
"This appears to be the entryway to some sort of gargoyle outpost.  The\n"+
"stench is overpowering, and the bones of unlucky forest travelers litter\n"+
"the floor of the cave here.  The cave continues deeper to the north and\n"+
"an opening leads to a clearing to the south.\n");

    add_exit(ROOMS+"garg009", "north");
    add_exit(ROOMS+"garg007", "south");
    set_light(1);
    reset(0);
}

