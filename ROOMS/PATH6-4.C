/* path6-4.c */
#include "/players/slider/include/slider.h"

inherit "room/room";

reset(arg)
{
   if(!present("giant"))
      move_object(clone_object(MONSTERS+"firegian"), this_object());

   if (arg) return;
}

create() {
    set_short("Burnt Cliff");

    set_long(
"The scorched trail ends here at a sheer cliff set high above a vast chasm\n"+
"cut into the earth.  The vegetation that has not been burned to crisp \n"+
"clings stubbornly to the bare, rocky soil.  There doesn't appear to be any\n"+
"safe way down the cliff.\n");
    add_exit(ROOMS+"path6-3", "south");

    set_light(1);
    reset(0);
}

