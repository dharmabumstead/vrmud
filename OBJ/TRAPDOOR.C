inherit "/std/move";
/**************************************************************************
 * NAME:
 *    trapdoor.c
 * DESCRIPTION:
 *    Slider's Trap Door
 * VERSION:
 *    1.0
 * ENVIRONMENT:
 *    Virtual Realities -  LPMud 3.1.2-DR
 * UPDATE HISTORY
 *    12/10/93  Slider  Initial version
 ***************************************************************************/
 
init() {
   add_action("enter_clock", "enter");
}
 
id(str) {
    return ((str== "trapdoor"));
}
 
/* It's invisible and you can't pick it up */
 
get() {
    return 0;
}
 
short() {
    return(0);
}
 
enter_clock(str) {
   if(str!="clock") return 0;
 
   write("\
You feel a wrenching sensation as you walk through the walls of the clock!\n");
   say(capitalize(this_player()->query_real_name()) + " disappears into\
      the clock!\n");
 
   this_player()->move_player("clock#players/slider/rooms/elsquare");
 
   return(1);
}
