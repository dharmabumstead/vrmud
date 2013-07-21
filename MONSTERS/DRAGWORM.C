/* dragworm.c */
#include "/players/slider/include/slider.h"

inherit "/obj/monster";

create() {
    ::create();
    set_id(({"dragon worm", "worm"}));
    set_short("dragon worm");
    set_long(
"A venomous, scaly creature that resembles an odd cross between a worm and\n"+
"a dragon.  It appears quite nasty!\n");
    set_level(16);
    set_spell_mess1("The dragon worm spits venom!");
    set_spell_mess2("The dragon worm's venom sears your skin!");
    set_spell_chance(25);
    set_spell_dam(20);
    add_money(1000);
    set_ac(13);
}
