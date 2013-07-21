/* pastur04.c */
#include "/players/slider/include/slider.h"
 
inherit "room/room";
 
reset(arg)
{
   while(!present("cow 2")) {
      move_object(clone_object(MONSTERS+"cow"), this_object());
   }
 
   if (arg) return;
}
 
create() {
    set_short("Northeast Pasture");
 
    set_long("\
You are at the northeast end of a large pasture.  The pasture is green and\n\
pleasant...and who knows how many burgers come from its fragrant confines?\n\
The pasture ends in a barbed wire fence to the north, and stretches out in\n\
in all other directions.\n");
 
   add_exit(ROOMS+"pastur09", "south");
   add_exit(ROOMS+"pastur05", "east");
   add_exit(ROOMS+"pastur03", "west");
   add_exit(ROOMS+"pastur10", "southeast");
   add_exit(ROOMS+"pastur08", "southwest");
 
   add_item("fence", "It's a nasty looking barbed wire fence.");
 
   set_light(1);
   reset(0);
}
