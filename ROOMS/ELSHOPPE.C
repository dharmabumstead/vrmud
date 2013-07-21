/* elshoppe.c
 * last modified 11/07/93
 */
 
#include "/players/slider/include/slider.h"
 
inherit "room/room";
 
init() {
    ::init();
    add_action("west","west");
}
 
reset() {
   if (!present("shopkeeper"))
       move_object(MONSTERS+"shopkeep",this_object());
 
}
 
create() {
    set_short("Elwoode Village Store");
    set_long(
"This is the Elwoode Village Store.  For generations, villagers have come\n"+
"here to restock their larders from the store's extensive inventory.  The\n"+
"store has been run by Orson the shopkeep for as long as anyone can remember.\n"
+
"If you can find him, you're in business!\n");
    add_item("counter",
"The wooden counter has been worn to a gloss by years of commerce.");
    add_item("door",
"It has no door handle and can only be described as SOLID.");
    add_exit(ROOMS+"elwood01", "south");
    set_light(1);
    reset();
}
 
west() {
    if (this_player()->query_level() > 19)
        return 0;
    say(this_player()->query_name()+" walks into the stockroom door!\n");
    write("Sorry....employees only!\n");
    return 1;
}
 
