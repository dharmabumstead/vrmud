/* pastur07.c */
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
    set_short("Northwest Pasture");
 
    set_long("\
This is the northwest section of a large pasture.  The center of the pasture\n\
lies to the east and southeast of here.  The pasture continues in all \n\
other directions.\n");
 
   add_exit(ROOMS+"pastur02", "north");
   add_exit(ROOMS+"pastur12", "south");
   add_exit(ROOMS+"pastur08", "east");
   add_exit(ROOMS+"pastur06", "west");
   add_exit(ROOMS+"pastur03", "northeast");
   add_exit(ROOMS+"pastur01", "northwest");
   add_exit(ROOMS+"pastur13", "southeast");
   add_exit(ROOMS+"pastur11", "southwest");
 
   set_light(1);
   reset(0);
}
