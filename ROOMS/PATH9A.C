/* path9a.c */
#include "/players/slider/include/slider.h"

inherit "room/room";

reset(arg)
{
   if (arg) return;
}

create() {
    set_short("Elwoode Gates");

    set_long("\
You are standing at the gates to the village of Elwoode.  The magnificent \n\
stone arch stands, silent sentinel over the small village.  The path\n\
continues west into the village, and east into the forest.\n");

    add_exit(ROOMS+"path10a", "west");
    add_exit(ROOMS+"path8", "east");

    set_light(1);
    reset(0);
}

