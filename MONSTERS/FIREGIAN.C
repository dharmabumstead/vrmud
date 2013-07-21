/* firegian.c 
 * updated 11/06/93
 */
 
#include "/players/slider/include/slider.h"
 
inherit "/obj/monster";
 
init() {
    ::init();
    if(!present("cloak"))
       move_object(clone_object(OBJ+"flmcloak"), this_object());
 
    if(!present("amulet"))
       move_object(clone_object(OBJ+"flmamult"), this_object());
}
 
create() {
    ::create();
    set_id(({"giant", "fire giant", "fire"}));
    set_short("a fire giant");
    set_long(
"An enchanted bear that stands well over 7 feet tall and resembles a \n"+
"grizzly bear.  Your eyes water from its brilliantly flaming hide!\n");
    set_spell_mess1("The fire giant shakes the earth with its roar!");
    set_spell_mess2("The fire giant's breath bathes you in flame!");
    init();
    command("wear cloak");
    command("wear amulet");
    set_level(18);
    set_ac(15);
    set_wc(26);
    set_spell_chance(40);
    set_spell_dam(25);
    add_money(1000);
}
