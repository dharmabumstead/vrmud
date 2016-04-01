/* pastur20.c */
#include "/players/slider/include/slider.h"
 
inherit "room/room";
 
reset(arg)
{
   while(!present("cow")) {
      move_object(clone_object(MONSTERS+"cow"), this_object());
   }
 
   if (arg) return;
}
 
create() {
    set_short("Southeast Pasture");
 
    set_long("\
This is the southeast end of a large pasture.  The pasture is bounded by a\n\
barbed wire fence to the south and east.  The pasture stretches into the\n\
distance to the north and west.\n");
 
   add_exit(ROOMS+"pastur15", "north");
   add_exit(ROOMS+"pastur19", "west");
   add_exit(ROOMS+"pastur14", "northwest");
 
   add_item("fence", "It's a nasty looking barbed wire fence.");
 
   set_light(1);
   reset(0);
}
