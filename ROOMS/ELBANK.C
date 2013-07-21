/*Skyler takes full responsibility for putting this off of the square */
#include "/players/slider/include/slider.h"

inherit "room/room";

reset(arg)
{
   if(!present("teller"))
      move_object(clone_object(OBJ+"bankmach"), this_object());
   if(!present("roomwatch"))
      move_object(clone_object(OBJ+"roomwatc"), this_object());

   if (arg) return;
}

create() {
    set_short("First Bank of Elwoode");

    set_long(
"Slider's bank of Elwoode has TEMPORARILY been moved here so that \n"+
"players can use it until Slider's area is reopened. \n"+
" \n"+
"You are in the First Bank of Elwoode's automated teller station.  A door\n"+
"leads you back to the square. \n");
add_exit(ROOMS+"elwood02","south");
add_exit("room/newroom/square.c","square");

    set_light(1);
    reset(0);
}

