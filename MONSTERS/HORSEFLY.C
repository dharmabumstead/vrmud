/* horsefly.c 
 * last updated 11/06/93
 */
 
inherit "/obj/monster";
 
create() {
    ::create();
    set_id(({"horsefly", "fly"}));
    set_short("a horsefly");
    set_long(
"It's a big, hairy horsefly!  It looks like its been eating well, judging\n"+
"from the size of it!\n");
    set_level(2);
    set_spell_chance(30);
    set_spell_dam(0);
    set_spell_mess1("The horsefly takes a big bite o' scalp!");
    set_spell_mess2("The horsefly takes a big bite out of your scalp!");
    set_ac(3);
    load_chat(10,({
"A horsefly buzzes around your face!\n",
"A horsefly lands in your hair!  Yechh!\n",
"A horsefly buzzes straight into your ear!\n" }));
    add_money(60);
}
 
 
