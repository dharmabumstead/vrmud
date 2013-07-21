/* path5.c */
#include "/players/slider/include/slider.h"

inherit "room/room";

reset(arg)
{
   if (arg) return;
}

create() {
    set_short("Winding Path");

    set_long(
"The winding path continues to the east and west here.  The glorious green\n"+
"foliage overhead gives you a sheltered feeling.  A sign, withered and faded\n"+
"by age, leans out of the soil here.\n");

    add_exit(ROOMS+"path6", "west");
    add_exit(ROOMS+"path4", "east");

    add_item("sign",
"The sign points west.  In faded, ornate script you can make out the words\n"+
"'Village of Elwoode'.");

    set_light(1);
    reset(0);
}

