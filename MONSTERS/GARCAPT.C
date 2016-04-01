/* garcapt.c */
#include "/players/slider/include/slider.h"

inherit "/obj/monster";

init() {
    ::init();
    if(!present("sword"))
       move_object(clone_object(OBJ+"garglong"), this_object());
    if(!present("platemail"))
       move_object(clone_object(OBJ+"gargplat"), this_object());
}

create() {
    ::create();
    set_id(({"gargoyle", "gargoyle captain", "captain"}));
    set_short("gargoyle captain");
    set_long(
"A winged captain of the gargoyle guard.  He looks rather angry!\n");
    set_level(18);
    set_spell_mess1("The gargoyle rips its victims flesh with its fangs!");
    set_spell_mess2("The gargoyle rips your flesh with its fangs!");
    set_spell_chance(25);
    set_spell_dam(22);
    load_chat(10,({
"The gargoyle growls something in a foreign tongue.\n",
"The gargoyle's wings bristle!\n",
"The gargoyle scowls menacingly at you!\n",
"The captain takes a step toward you!\n" }));
    set_ac(13);
    init();
    command("wield longsword");
    command("wear platemail");
    set_ac(15);
    set_wc(26);
}

