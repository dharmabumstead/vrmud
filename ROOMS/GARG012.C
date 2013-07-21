/* garg012.c */
#include "/players/slider/include/slider.h"

inherit "room/room";

reset(arg)
{
   if(!present("worm")) {
      move_object(clone_object(MONSTERS+"dragworm"), this_object());
    }

   if (arg) return;
}

create() {
    set_short("Lower Gargoyle Crossroads");

    set_long(
"You've come to an intersection in the cavern path.  Passages lead to all\n"+
"four points of the compass.  The air is very cool down here and feels \n"+
"electric with tension.  Many a tale of the evil creatures that lurk within\n"+
"these walls has been uttered in hushed tones throughout the realm.  Tread\n"+
"carefully within!\n");
    add_exit(ROOMS+"garg011", "south");
    add_exit(ROOMS+"garg012a", "east");
    set_light(1);
    reset(0);
}

