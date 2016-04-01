/* path10.c */
#include "/players/slider/include/slider.h"

inherit "room/room";

reset(arg)
{
   if (arg) return;
}

create() {
    set_short("Elwoode Gates");

    set_long(
"You are at the gates to the village of Elwoode.  A large, ornately carved\n"+
"wooden sign is posted next to the trail here, which leads west into Elwoode\n"+
"and back east into the forest.\n");

    add_exit(ROOMS+"path10a", "west");
    add_exit(ROOMS+"path9a", "east");

    set_light(1);
    reset(0);
}

