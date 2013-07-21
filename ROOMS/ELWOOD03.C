/* elwood03.c */
#include "/players/slider/include/slider.h"
 
inherit "room/room";
 
reset(arg)
{
   if(!present("bugbear")) {
      move_object(clone_object(MONSTERS+"bugbear"), this_object());
   }
 
   if (arg) return;
}
 
create() {
    set_short("North of Elwoode Square");
 
    set_long("\
You are on a pleasant cobblestone street just north of the Elwoode Village\n\
Square.  Townspeople of all descriptions rush on about their business, \n\
seemingly oblivious to you.  Shops, pubs, inns, and all manner of business\n\
thrive up and down the street, which runs north and south from here.\n");
 
    add_exit(ROOMS+"elsquare", "south");
    add_exit(ROOMS+"elwood04", "north");
 
    add_item("townspeople",
"They all look much too busy to talk to you!");
 
    add_item("people",
"They all look much too busy to talk to you!");
 
    add_item("shops",
"You feel the money burning a whole in your pocket as you eye the shops!");
 
    add_item("street",
"The cobblestones have been worn smooth by countless feet over the ages.\n\
They feel warm beneath your feet.");
    
    set_light(1);
    reset(0);
}
 
