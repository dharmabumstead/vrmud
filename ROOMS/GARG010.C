/* garg010.c */
#include "/players/slider/include/slider.h"

inherit "room/room";

create() {
   set_short("Lower Gargoyle Entrance");

   set_long(
"This is a dark, vile-smelling passage that slopes down to the north and\n"+
"back up to the south.  A flickering light from the north casts dancing\n"+
"shadows on the cavern walls.\n");
   add_exit(ROOMS+"garg011", "north");
   add_exit(ROOMS+"garg009", "up");
   set_light(1);
}
