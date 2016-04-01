/* garg001.c */
#include "/players/slider/include/slider.h"
 
inherit "room/room";
 
create() {
    set_short("Forest Clearing");
 
    set_long(
"You've arrived at a hidden clearing in the forest.  An opening in the\n"+
"thick vegetation surrounding the clearing leads south, and the clearing\n"+
"continues north from here.\n");
    add_exit(ROOMS+"garg002", "north");
    add_exit(ROOMS+"path3", "south");
    set_light(1);
}
 
