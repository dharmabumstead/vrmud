/* path6.c */
#include "/players/slider/include/slider.h"

inherit "room/room";

reset(arg)
{
   if (arg) return;
}

create() {
    set_short("Winding Path");

    set_long(
"The light seems to grow dim here.  The vegetation on either side of the\n"+
"trail is trampled and crushed.  Twigs and branches are snapped off from\n"+
"the charred trees to the north.  Something fairly large has burned its way\n"+
"through here recently.\n");

    add_exit(ROOMS+"path6-1", "north");
    add_exit(ROOMS+"path5", "east");
    add_exit(ROOMS+"path7", "west");

    set_light(1);
    reset(0);
}

