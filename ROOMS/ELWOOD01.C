/* elwood01.c */
#include "/players/slider/include/slider.h"

inherit "room/room";

reset(arg)
{
   if (arg) return;
}

create() {
    set_short("Elwoode Main Street West");

    set_long(
"This is the main street running through the village of Elwoode.  The cobble-\n"+
"stone has been worn smooth by generations of traffic, attracted to Elwoode\n"+
"as a major trading center for the denizens of the enormous Elwoode Forest.\n"+
"The Elwoode Village Shoppe lies north of here, a tavern lies to the south,\n"+
"and the street continues east towards some houses and west towards the\n"+
"village center.\n");

    add_exit(ROOMS+"elwood02", "west");
    add_exit(ROOMS+"path10a", "east");
    add_exit(ROOMS+"elshoppe", "north");
    add_exit(ROOMS+"elpub01", "south");

    set_light(1);
    reset(0);
}

