/* elwoods2.c */
#include "/players/slider/include/slider.h"
 
inherit "room/room";
 
reset(arg)
{
   if (arg) return;
}
 
create() {
    set_short("South of Elwoode Square");
 
    set_long("\
You are on a worn cobblestone street on the southern outskirts of Elwoode.\n\
You can proceed north into the village proper or south into the surrounding\n\
countryside.\n");
 
    add_exit(ROOMS+"elwoods1", "north");
    add_exit(ROOMS+"elwoods3", "south");
 
    set_light(1);
    reset(0);
}
 
