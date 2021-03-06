/*****************************************************************************
 *  Generated by Slider's 'Roomy for Windows' v0.8
 *  room created 11-05-1994 at 18:22:09
 ****************************************************************************/

#include "/players/slider/include/slider.h"

inherit "room/room";
reset(arg)
{

   if (arg) return;
}

create() {
   set_short("Slider's Bestiary Control Room");

   set_long("\
Still under construction, this room will soon house a sophisticated control\n\
panel for Slider's monster combat simulator. Right now, the room is merely\n\
unpainted drywall and lots of boxes of complicated looking equipment. An exit\n\
leads east into the bestiary proper.\n\
   ");

   add_exit(ROOMS+"bestiary","east");

   add_item("box", "\

   add_item("drywall", \
"It's, you know - drywall! As in unfinished, and pretty boring to look at.\
   \n");
 
  add_item("equipment", \
It looks expensive and obscenely complex. Most of it is still in the box.\n");

   ");

   set_light(1);
   reset(0);
}
