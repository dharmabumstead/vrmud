/* garg011.c */
#include "/players/slider/include/slider.h"

inherit "room/room";

create() {
    set_short("Lower Gargoyle Path");

    set_long(
"The path through the caverns seems to level out here, and continues to the\n"+
"north and south.\n");
    add_exit(ROOMS+"garg012", "north");
    add_exit(ROOMS+"garg010", "south");
    set_light(1);
}

