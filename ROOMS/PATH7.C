/* path7.c */
#include "/players/slider/include/slider.h"

inherit "room/room";

reset(arg)
{
   if (arg) return;
}

create() {
    set_short("Winding Path");

    set_long(
"The path seems to be a bit more well-worn here.  The way west seems to \n"+
"be more heavily travelled, while east seems somewhat dark and foreboding.\n");

    add_exit(ROOMS+"path8", "west");
    add_exit(ROOMS+"path6", "east");

    set_light(1);
    reset(0);
}

