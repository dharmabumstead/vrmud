/* elwood04.c
 * update 12/10/93
 */
 
#include "/players/slider/include/slider.h"
 
inherit "room/room";
 
reset(arg)
{
 
   if (arg) return;
}
 
create() {
   set_short("North Elwoode Street");
 
   set_long("\
You are on a pleasant thoroughfare on the north end of the village of \n\
Elwoode.  The street is a bit quieter here than the center of town; the\n\
shops are a bit more seedy-looking.  The street continues north out of\n\
town and south towards the center of town.  A dark alley gapes hollowly\n\
to the west.\n");
 
   add_exit(ROOMS+"elwood03", "south");

/* This must not be done, removed since was getting player bug things
   add_exit(ROOMS + "elwood05","north");
*/
   add_exit(ROOMS+"elwood4a", "west");
 
   add_item("street",
"Yep - it's a street all right!  You're standing on it!");
 
   add_item("alley",
"It looks dark and more than a little dangerous.  You may not want to go\n\
in there alone!");
 
   add_item("shops",
"They're not much to look at.  None of them appear to be open for business.");
    
   set_light(1);
   reset(0);
}
