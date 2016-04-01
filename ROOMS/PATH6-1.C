/* path6-1.c */
#include "/players/slider/include/slider.h"

inherit "room/room";

reset(arg)
{
   while(!present("sprite 3")) 
      move_object(clone_object(MONSTERS+"firesprt"), this_object());

   if (arg) return;
}

create() {
    set_short("Burnt Path");

    set_long(
"This is a charred trail burnt through the forest.  Whatever passed through\n"+
"here has left in its wake a crisped and smoking wreckage wherever it's\n"+
"touched.  The smoldering remains of a small animal is hunched pitifully\n"+
"at the edge of the blackness.  The path leads north and south from here.\n");  
    add_exit(ROOMS+"path6-2", "north");
    add_exit(ROOMS+"path6", "south");

    set_light(1);
    reset(0);
}

