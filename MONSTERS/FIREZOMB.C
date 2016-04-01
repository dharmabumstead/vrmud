/* firezomb.c 
 * updated 11/06/93
 */
 
#include "/players/slider/include/slider.h"
 
inherit "/obj/monster";
 
init() {
    ::init();
    if(!present("helmet"))
       move_object(clone_object(OBJ+"flmhelmt"), this_object());
}
 
create() {
    ::create();
    set_id(({"zombie", "fire zombie", "zombie"}));
    set_short("a fire zombie");
    set_long(
"It is an enchanted undead warrior, cursed to flame forever.\n");
    set_spell_mess1("The fire zombie lashes at its victim!");
    set_spell_mess2("The fire zombie lunges at you!");
    init();
    command("wear helmet");
    set_level(17);
    set_ac(14);
    set_wc(24);
    set_spell_chance(20);
    set_spell_dam(15);
    add_money(1000);
}
