#include "/players/slider/include/slider.h"

inherit "room/room";

object fridge;

reset(arg)
{
   if (!fridge)
   {
      fridge=clone_object(OBJ+"fridge");
      move_object(fridge, this_object());
      while(!present("beer 6", fridge))
         move_object(clone_object(OBJ+"beer"), fridge);
   }
   if (arg) return;
}

create() {
    set_short("Slider's Kitchen");

    set_long(
"This is Slider's kitchen!  Slider has been known to whip up a mean batch\n"+
"of Thai Fried Rice or Chicken Parmigiana here.  An exit leads west into\n"+
"the den, and a perfectly normal looking door leads south.\n");

    add_exit(ROOMS+"den", "west");
    add_exit(ROOMS+"path1", "south");
    set_light(1);
    reset(0);
}

