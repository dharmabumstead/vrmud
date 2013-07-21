/* pastur14.c */
#include "/players/slider/include/slider.h"
 
inherit "room/room";
 
reset(arg)
{
   while(!present("cow 3"))  {
      move_object(clone_object(MONSTERS+"cow"), this_object());
   }
 
   if (arg) return;
}
 
create() {
    set_short("Southeast Pasture");
 
    set_long("\
This is the southeast section of a large pasture.  The center of the pasture\n\
lies to the west and northwest of here.  The pasture continues in all \n\
directions.\n");
 
   add_exit(ROOMS+"pastur09", "north");
   add_exit(ROOMS+"pastur19", "south");
   add_exit(ROOMS+"pastur15", "east");
   add_exit(ROOMS+"pastur13", "west");
   add_exit(ROOMS+"pastur10", "northeast");
   add_exit(ROOMS+"pastur08", "northwest");
   add_exit(ROOMS+"pastur20", "southeast");
   add_exit(ROOMS+"pastur18", "southwest");
 
   set_light(1);
   reset(0);
}
