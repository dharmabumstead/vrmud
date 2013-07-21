/* garg012c.c */
#include "/players/slider/include/slider.h"

inherit "room/room";

reset(arg)
{
   if(!present("spider")) {
      move_object(clone_object(MONSTERS+"gspider"), this_object());
    }

   if (arg) return;
}

create() {
    set_short("Giant Spider's Lair");

    set_long(
"The passageway opens up here to an enormous cavern.  Every available surface\n"+
"seems covered with a sticky, silky substance.\n");
    add_exit(ROOMS+"garg012b", "west");
    set_light(1);
    reset(0);
}
