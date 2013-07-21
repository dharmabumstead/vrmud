/* path10a.c */
#include "/players/slider/include/slider.h"

inherit "room/room";

reset(arg)
{
   if (arg) return;
}

create() {
    set_short("Elwoode Gates");

    set_long(
"Your are standing just inside the gates of Elwoode.  The worn cobblestone\n"+
"feels warm against your feet.  Small cottages and homes line the street\n"+
"here.  The street leads west into the village proper and east back into\n"+
"the forest.\n");

    add_exit(ROOMS+"elwood01", "west");
    add_exit(ROOMS+"path9a", "east");

    set_light(1);
    reset(0);
}

