/* garg007.c */
#include "/players/slider/include/slider.h"

inherit "room/room";

reset(arg)
{
   while(!present("guard 4")) {
      move_object(clone_object(MONSTERS+"garguard"), this_object());
    }

   if (arg) return;
}


create() {
    set_short("Gargoyle Clearing");

    set_long(
"The path opens up here to a small clearing which serves as an entryway\n"+
"into the gargoyle's inner sanctum.  The remains of a small campfire made\n"+
"by the gargoyle guards is still smoldering.  A path leads south away from\n"+
"the clearing and a small cave opening is visible to the north.\n");

    add_exit(ROOMS+"garg008", "north");
    add_exit(ROOMS+"garg006", "south");
    set_light(1);
    reset(0);
}

