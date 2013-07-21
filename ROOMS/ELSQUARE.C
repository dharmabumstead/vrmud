/* elsquare.c
 * last updated 12/10/93
 */
 
#include "/players/slider/include/slider.h"
 
inherit "room/room";
 
object bboard;
 
reset(arg)
{
 
   if (!bboard) {
      bboard = clone_object("/std/board_ob");
      bboard->set_save_name("players/slider/logs/elwoodbd");
      move_object(bboard, this_object());
   }
   if (arg) return;
}
 
init() {
   ::init();
   add_action("clock", "clock");
   add_action("enter_clock", "enter");
}
 
create() {
   set_short("Elwoode Square");
 
   set_long("\
You've arrived at the Elwoode Village Square.  A huge 'clock' dominates the\n\
square.  At the base of the clock is a kiosk with a bulletin board.  Wrought\n\
iron and wood benches are placed at strategic points in the center of the\n\
square.  The path leads to all directions here.\n");
 
   add_exit(ROOMS+"elwood02", "east");
   add_exit(ROOMS+"elwood03", "north");
   add_exit(ROOMS+"elwoods1", "south");
 
   add_item("benches", "They look rather uncomfortable.");
 
   add_item("clock",
"It seems strangely....resonant...like you could almost step inside it.\n\
Type 'clock' to get the game time.");
 
   add_item("kiosk","There's a bulletin board here.");
 
    set_light(1);
    reset(0);
}
 
clock() {
    object square;
 
    square = find_object("/room/newroom/square");
 
    if(square) {
        say(this_player()->query_name() + " checks the game 'clock'.\n");
        square->long("clock");
        return(1);
    }
    return(0);
}
 
enter_clock(str) {
 
   if (str != "clock") return 0;
 
   write("\
You feel a strange sense of spatial disharmony as you walk right through the\n\
the concrete wall of the clock tower!\n");
 
   say(this_player()->query_real_name() + " disappears into the clock!\n");
   this_player()->move_player("clock#room/newroom/square");
   return(1);
}
 
