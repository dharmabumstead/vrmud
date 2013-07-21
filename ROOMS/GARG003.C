/* garg003.c */
#include "/players/slider/include/slider.h"

inherit "room/room";

reset(arg)
{
   if(!present("guard"))
      move_object(clone_object(MONSTERS+"garguard"), this_object());

   if (arg) return;
}

create() {
    set_short("North Forest Clearing");

    set_long(
"You are at the north end of the forest clearing.  An ominous looking path \n"+
"leads further into the forest to the north.  The center of the clearing \n"+
"lies south of here.\n");
    add_exit(ROOMS+"garg006", "north");
    add_exit(ROOMS+"garg002", "south");
    set_light(1);
    reset(0);
}

