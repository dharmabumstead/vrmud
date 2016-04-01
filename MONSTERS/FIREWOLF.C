/* firewolf.c 
 * last updated 11/06/93
 */
 
inherit "/obj/monster";
 
create() {
    ::create();
    set_id(({"wolf", "fire wolf", "wolf"}));
    set_short("a fire wolf");
    set_long(
"A very nasty-looking fire wolf.  Black eyes bore into you from behind\n"+
"its enchanted flaming coat.\n");
    set_spell_mess1("The fire wolf rips at its victim!");
    set_spell_mess2("The fire wolf rips at your throat!");
    set_spell_chance(20);
    set_spell_dam(15);
    set_level(16);
    set_ac(13);
    set_wc(22);
    add_money(1300);
}
