/* babygar1.c 
 * last updated 11/06/93
 */
 
inherit "/obj/monster";
 
create() {
    ::create();
    set_id(({"gargoyle", "baby gargoyle", "drone", "baby drone", "baby"}));
    set_short("baby drone gargoyle");
    set_long(
"It's a smaller, wingless version of the baby winged gargoyle.  It has mottled\n"+
"red skin, pointed ears, and an ugly disposition, even at this early age.\n"+
"Although it's definitely NOT cute, it looks relatively harmless.\n");
    set_spell_mess1("The baby drone gargoyle spits bile!");
    set_spell_mess2("The baby drone gargoyle spits bile at you!");
    set_spell_chance(5);
    set_spell_dam(2);
    set_level(7);
    set_ac(6);
    add_money(300);
}
