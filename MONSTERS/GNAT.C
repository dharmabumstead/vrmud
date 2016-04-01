/* gnat.c
 * last updated 11/09/93
 */
 
inherit "/obj/monster";
 
create() {
    ::create();
    set_id(({"gnat"}));
    set_short("a gnat");
    set_long(
"It's small and kind of hard to see, but it appears to be a gnat.  It buzzes\n"+
"around your head annoyingly!\n");
    set_level(1);
    set_spell_chance(30);
    set_spell_dam(0);
    set_spell_mess1("The gnat feasts on an unlucky adventurer!");
    set_spell_mess2("The gnat lunches on you!  Ouch!");
    set_ac(3);
    set_wc(5);
    load_chat(5,({
"The gnat buzzes around your face!\n",
"A gnat flies up your nose!\n",
"Blech!  You spit out a gnat that flew into your mouth!\n" }));
    add_money(30);
}
 
