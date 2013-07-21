/* pastur09.c */
#include "/players/slider/include/slider.h"
 
inherit "room/room";
 
reset(arg)
{
   while(!present("heifer 3")) {
      move_object(clone_object(MONSTERS+"heifer"), this_object());
   }
 
   if (arg) return;
}
 
create() {
    set_short("Northeast Pasture");
 
    set_long("\
This is the northeast section of a large pasture.  The center of the pasture\n\
lies to the west and southwest of here.  The pasture continues in all \n\
directions.\n");
 
   add_exit(ROOMS+"pastur04", "north");
   add_exit(ROOMS+"pastur14", "south");
   add_exit(ROOMS+"pastur10", "east");
   add_exit(ROOMS+"pastur08", "west");
   add_exit(ROOMS+"pastur05", "northeast");
   add_exit(ROOMS+"pastur03", "northwest");
   add_exit(ROOMS+"pastur15", "southeast");
   add_exit(ROOMS+"pastur13", "southwest");
 
   set_light(1);
   reset(0);
}
