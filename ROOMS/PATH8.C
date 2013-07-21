/* path8.c */
#include "/players/slider/include/slider.h"

inherit "room/room";

reset(arg)
{
   if (arg) return;
}

create() {
    set_short("Outside Elwoode");

    set_long(
"You are on a well worn path leading west into the Village of Elwoode and \n"+
"east back into the Elwoode Forest.  There is a roadblock here with a sign\n"+
"that says 'Under Construction', but it looks like you can slip around it.\n");

    add_exit(ROOMS+"path9a", "west");
    add_exit(ROOMS+"path7", "east");

    set_light(1);
    reset(0);
}

