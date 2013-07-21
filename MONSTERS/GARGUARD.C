/* garguard1.c */
#include "/players/slider/include/slider.h"

inherit "/obj/monster";

init() {
    ::init();
    if(!present("knife"))
       move_object(clone_object("/obj/stuff/knife"), this_object());
}

create() {
    ::create();
    set_id(({"gargoyle", "gargoyle guardian", "guard", "guardian"}));
    set_short("gargoyle guardian");
    set_long(
"An unpleasant looking gargoyle guardian.  This is a drone guardian, so it's\n"+
"not winged.  It looks determined to keep you from going any further.\n");
    set_level(12);
    set_spell_chance(30);
    set_spell_dam(5);
    set_spell_mess1("The gargoyle tears at its victim with its sharp claws!");
    set_spell_mess2("The gargoyle tears at you with its razor sharp claws!");
    load_chat(10,({
"The gargoyle growls something in a foreign tongue.\n",
"In broken English, the guard says 'Leave or die, intruder!'\n",
"The gargoyle scowls menacingly at you!\n" }));
    add_money(500);
    init();
    command("wield knife");
    set_ac(9);
    set_wc(16);
}

