/* garg009a.c */
#include "/players/slider/include/slider.h"

inherit "room/room";

reset(arg)
{
   if(!present("captain")) {
      move_object(clone_object(MONSTERS+"garcapt"), this_object());
    }
    
   if(!present("lieutenant")) {
      move_object(clone_object(MONSTERS+"garlieut"), this_object());
   }
   

   if (arg) return;
}


create() {
    set_short("Gargoyle Cavern East");

    set_long(
"This is a cold and wet room in the gargoyle caverns.  Bones of unlucky\n"+
"travellers litter the floor here, and a steady dripping sound emanates\n"+
"from somewhere.  An exit leads west.\n");    
    add_exit(ROOMS+"garg009", "west");
    set_light(1);
    reset(0);
}

