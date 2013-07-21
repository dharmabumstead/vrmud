/* garg006.c */
#include "/players/slider/include/slider.h"

inherit "room/room";

create() {
    set_short("Ominous Path");

    set_long(
"You are on a dark and ominous path that winds in a north-south direction\n"+
"through the forest.  The air feels cool and electric on your skin as you\n"+
"make your way along.  As your eyes adjust to the gloom, you think you can\n"+
"catch a glimpse of eyes following your progress.  The path continues north\n"+
"into the gloom of the forest or south into a clearing.\n");

    add_exit(ROOMS+"garg007", "north");
    add_exit(ROOMS+"garg003", "south");
    set_light(1);
}

