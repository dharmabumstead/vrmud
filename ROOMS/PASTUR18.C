/* pastur18.c */
#include "/players/slider/include/slider.h"
 
inherit "room/room";
 
reset(arg)
{
   while(!present("cow 3")) {
      move_object(clone_object(MONSTERS+"cow"), THIS);
   }
 
   if (arg) return;
}
 
create() {
    set_short("South Pasture");
 
    set_long("\
You are at the south end of a large pasture.  It seems very peaceful here,\n\
although you'd be well advised to watch out for some of the 'fruit' of the\n\
pasture's current residents.  The pasture ends in some barbed wire fencing\n\
to the south, and stretches out in all other directions.\n");
 
   add_exit(ROOMS+"pastur13", "north");
   add_exit(ROOMS+"pastur19", "east");
   add_exit(ROOMS+"pastur17", "west");
   add_exit(ROOMS+"pastur14", "northeast");
   add_exit(ROOMS+"pastur12", "northwest");
 
   add_item("fence", "It looks nasty. Don't touch it!");
 
   set_light(1);
   reset(0);
}
 
