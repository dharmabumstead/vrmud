/* path9.c */
#include "/players/slider/include/slider.h"

inherit "room/room";

reset(arg)
{
   if (arg) return;
}

create() {
    set_short("Elwoode Dead End");

    set_long(
"You've come to a dead end!  A sign here says:\n"+
"       +-------------------------------------------------------+\n"+
"       |   Coming this week!  The Village of Elwoode will be   |\n"+
"       |   open!  Chat with interesting villagers!  Marvel     |\n"+
"       |   at the super-keen shops!  Meet interesting nasty    |\n"+
"       |   monsters and kill them!  Free balloons and hot      |\n"+
"       |   dogs for the kids!                                  |\n"+
"       +-------------------------------------------------------+\n");

    add_exit(ROOMS+"path8", "east");

    set_light(1);
    reset(0);
}
