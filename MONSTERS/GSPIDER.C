/* gspider.c */
/* modified 11/7/94 */
#include "/players/slider/include/slider.h"

inherit "/obj/monster";

init() {
    ::init();
    if(!present("hide"))
       move_object(clone_object(OBJ+"gspiplat"), this_object());

    if(!present("stinger"))
       move_object(clone_object(OBJ+"gstinger"), this_object());
}

create() {
    ::create();
    set_id(({"giant spider", "spider"}));
    set_short("giant spider");
    set_long(
"An enormous arachnid that towers above the cavern floor on legs twice as thick\n"+
"as a man's waist!  You can see your terrified face reflected in one of it's\n"+
"many eyes.  Venom drips from an enormous stinger and dissolves in an evil\n"+
"frenzy of steam on the cavern floor.\n");
    set_level(20);
    set_spell_mess1("The giant spider bathes its victim in acidic venom!");
    set_spell_mess2("The acidic venom of the giant spider burns into your skin!");
    set_spell_chance(20);
    set_spell_dam(40);
    set_al(-1000);
    set_aggressive(1);
    add_money(2000);
    init();
    command("wear hide");
    command("wield stinger");
    set_ac(17);
}
