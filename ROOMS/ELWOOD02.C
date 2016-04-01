/* elwood02.c */
#include "/players/slider/include/slider.h"

inherit "room/room";

reset(arg)
{
   if (arg) return;
}

create() {
    set_short("Elwoode Main Street West");

    set_long(
"You are on Elwoode's main thoroughfare.  The smooth cobblestone street is\n"+
"lined with shops and taverns on either side.  The village bank lies to the\n"+
"north.  The street leads west to the village square and east to some more\n"+
"shops.\n");

    add_exit(ROOMS+"elbank", "north");
    add_exit(ROOMS+"elsquare", "west");
    add_exit(ROOMS+"elwood01", "east");

    set_light(1);
    reset(0);
}
