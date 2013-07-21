/* stockrm.c
 * last updated 11/07/93
 */
 
#include "/players/slider/include/slider.h"
 
inherit "room/room";
 
reset() {
    /* put in initial store items here */
    if (!present("torch"))
        move_object(clone_object("obj/torch"),this_object());
    if (!present("bag"))
        move_object(clone_object("obj/bag"),this_object());
/*
 *    What happened to /obj/rope.c?  -Miraclemax
    if (!present("rope"))
        move_object(clone_object("obj/rope"),this_object());
*/
}
 
create() {
        int t;
        for(t=0;t<10;t++) {
           move_object(clone_object("/players/slider/obj/sticky"), this_object());
           move_object(clone_object("/players/slider/obj/squish"), this_object());
           move_object(clone_object("obj/torch"),this_object());
           move_object(clone_object("obj/bag"),this_object());
           move_object(clone_object("obj/stuff/chain"),this_object());
           move_object(clone_object("obj/stuff/plate"),this_object());
           move_object(clone_object("obj/stuff/longsword"),this_object());
           move_object(clone_object("obj/stuff/shortsword"),this_object());
        }
   set_short("A stockroom");
   set_long(
"You are in the stockroom of the Elwoode Village Shop.  You probably\n"+
"shouldn't be in here!\n");
    add_exit(ROOMS+"elshoppe","east");
    set_light(1);
    reset();
}
