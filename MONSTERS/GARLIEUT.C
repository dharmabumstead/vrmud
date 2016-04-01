/* garlieut.c */
#include "/players/slider/include/slider.h"

inherit "/obj/monster";

init() {
    ::init();
    if(!present("shortsword"))
       move_object(clone_object(OBJ+"garshort"), this_object());
       
    if(!present("chainmail"))
       move_object(clone_object(OBJ+"garchain"), this_object());
}

create() {
    ::create();
    set_id(({"gargoyle", "gargoyle lieutenant", "lieutenant"}));
    set_short("gargoyle lieutenant");
    set_long(
"An unpleasant looking gargoyle lieutenant.  It's winged, stands about \n"+
"six feet tall, and has fire engine red skin and a bad attitude.  It looks\n"+
"as though it's not about to let you past without a fight!\n");
    set_level(17);
    set_spell_chance(30);
    set_spell_dam(10);
    set_spell_mess1("The gargoyle rips its victims flesh with its fangs!");
    set_spell_mess2("The gargoyle rips your flesh with its fangs!");
    load_chat(10,({
"The gargoyle growls something in a foreign tongue.\n",
"The gargoyle's wings bristle!\n",
"The gargoyle scowls menacingly at you!\n",
"The lieutenant takes a step toward you!\n" }));
    add_money(300);
    init();
    command("wield shortsword");
    command("wear chainmail");
    set_ac(14);
    set_wc(24);

}

