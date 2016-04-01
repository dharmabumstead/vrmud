/* babygar1.c */
inherit "/obj/monster";

create() {
    ::create();
    set_id(({"gargoyle", "baby gargoyle", "drone", "baby drone"}));
    set_short("baby drone gargoyle");
    set_long(
"It's a smaller, wingless version of the baby winged gargoyle.  It has mottled\n"+
"red skin, pointed ears, and an ugly disposition, even at this early age.\n"+
"Although it's definitely NOT cute, it looks relatively harmless.\n");
    set_level(7);
    add_money(250);
}
