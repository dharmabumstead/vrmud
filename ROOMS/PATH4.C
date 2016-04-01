/* path4.c */
#include "/players/slider/include/slider.h"

inherit "room/room";

reset(arg)
{
   if(!present("bugbear")) {
      move_object(clone_object(MONSTERS+"bugbear"), this_object());
   }

   if (arg) return;
}

create() {
    set_short("Winding Path");

    set_long(
"This is a fragrant path winding through the thick forest.  The sound of\n"+
"leaves gently stirring in the light breeze wafts gently through the\n"+
"forest.  The path continues to the east and west.\n");

    add_exit(ROOMS+"path5", "west");
    add_exit(ROOMS+"path3", "east");

    add_item("leaves",
"The cool, fragrant sway gently in the breeze.\n");

    add_item("path",
"The force of many feet through the ages has etched this path deeply into\n"+
"the earth.  You wonder where it leads.....\n");

    set_light(1);
    add_property("outside");  // added by Frijoles
    reset(0);
}

