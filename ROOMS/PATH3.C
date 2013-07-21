/* path3.c */
#include "/players/slider/include/slider.h"
 
inherit "room/room";
 
create() {
    set_short("Winding Path");
 
    set_long("\
This is a winding, thickly wooded path winding east and west through the\n\
the Forest of Elwoode.  The thick canopy of leaves overhead shelters the\n\
trail almost completely from the elements.  An opening in the vegetation\n\
lies to the north.\n");
 
    add_exit(ROOMS+"garg001", "north");
    add_exit(ROOMS+"path4", "west");
    add_exit(ROOMS+"path2", "east");
 
    add_item("leaves",
"The cool, fragrant leaves protect the path from the elements.\n");
 
    add_item("path",
"The force of many feet through the ages has etched this path deeply into\n\
the earth.  You wonder where it leads.....\n");
 
    add_item("opening",
"It looks dangerous.  You feel a cautious sort of dread as you consider \n\
what may be beyond the vegetation.\n");
 
   add_item("vegetation",
"There's an opening in the vegetation that leads north.\n");
 
   set_light(1);
   reset(0);
}
 
