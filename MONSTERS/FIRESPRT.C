/* firesprt.c 
 * last updated 11/06/93
 */
 
inherit "/obj/monster";
 
create() {
    ::create();
    set_id(({"sprite", "fire sprite", "fire"}));
    set_short("a fire sprite");
    set_long(
"A winged, flaming creature that vaguely resembles a bat.  It darts back\n"+
"and forth with amazing speed, leaving a searing trail across your vision.\n"+
"Your eyes start to water from looking at it, and your face begins to feel\n"+
"flushed from the intense heat.\n");
    set_spell_mess1("The fire sprite lashes out with claws of flame!");
    set_spell_mess2("The fire sprite rakes you with a burning claw!");
    set_spell_chance(20);
    set_spell_dam(10);
    set_level(14);
    set_ac(11);
    add_money(850);
}
