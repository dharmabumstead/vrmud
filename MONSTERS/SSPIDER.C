/* sspider.c */
#include "/players/slider/include/slider.h"

inherit "/obj/monster";

init() {
    ::init();
    add_action("east", "east");
}

create() {
    ::create();
    set_id(({"spider"}));
    set_short("large spider");
    set_long(
"A very large venomous spider.  A thick, white, acidic venom drips from its\n"+
"jaws.  Its eight hairy legs make a hideuos scrabbling noise on the hard cavern\n"+
"floor as it moves.\n");
    set_level(14);
    set_spell_mess1("The spider bathes its victim in acidic venom!");
    set_spell_mess2("The venom of the spider burns into your armor!");
    set_spell_chance(20);
    set_spell_dam(10);
    set_al(-300);
    add_money(850);
    set_ac(11);
}

east () {
    write("The spider blocks your way!\n");
    return(1);
}

