/* babygar2.c */
inherit "/obj/monster";

create() {
    ::create();
    set_id(({"gargoyle", "baby gargoyle", "drone", "baby drone", "baby"}));
    set_short("baby winged gargoyle");
    set_long(
"It's a baby winged gargoyle.  It's got pointy ears, batlike wings sprouting\n"+
"from it's leathery red back, and mottled red skin.  It's roughly 1/3 the\n"+
"size of an adult winged gargoyle, but every bit as ugly!  It looks kind of\n"+
"harmless.\n");
    set_spell_mess1("The baby gargoyle slashes out with its claws!");
    set_spell_mess2("The baby gargoyle lashes out at you with its claws!");
    set_spell_chance(10);
    set_spell_dam(2);
    set_level(7);
    set_ac(6);
    set_spell_chance(50);
    add_money(300);
}
