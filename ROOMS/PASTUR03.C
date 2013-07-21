/* pastur03.c */
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
You are at the north end of a large pasture.  It seems very peaceful here,\n\
although you'd be well advised to watch out for some of the 'fruit' of the\n\
pasture's current residents.  The entrance to the pasture lies to the north,\n\
and the pasture stretchs out in all other directions.\n");
 
   add_exit(ROOMS+"pastur00", "north");
   add_exit(ROOMS+"pastur08", "south");
   add_exit(ROOMS+"pastur04", "east");
   add_exit(ROOMS+"pastur02", "west");
   add_exit(ROOMS+"pastur09", "southeast");
   add_exit(ROOMS+"pastur07", "southwest");
 
   add_item("entrance", "A gated entryway lies north of here.");
 
   set_light(1);
   reset(0);
}
 
