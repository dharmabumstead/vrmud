/* garg012a.c */
#include "/players/slider/include/slider.h"

inherit "room/room";

reset(arg)
{
   while(!present("spider 3")) {
      move_object(clone_object(MONSTERS+"sspider"), this_object());
    }

   if (arg) return;
}

create() {
    set_short("Outer Spider's Lair");

    set_long(
"An enormous mass of cobwebs makes passage here very difficult.  Strange\n"+
"scorched pock marks decorate the floor here, as if they were burned into\n"+
"the cavern with some sort of acid.  An exit leads west to another part of\n"+
"the cavern, and you can make out a passage east throught the cobwebs.\n");
    add_exit(ROOMS+"garg012", "west");
    add_exit(ROOMS+"garg012b", "east");
    set_light(1);
    reset(0);
}

