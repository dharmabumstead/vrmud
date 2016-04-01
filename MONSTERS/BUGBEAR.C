/* Modified it so it wouldn't leave your area - Frij */
inherit "/std/light";
inherit "/std/light";
/* bugbear.c */
/* last modified 11/06/93 */
inherit "/obj/monster";
 
create() {
    ::create();
    set_id(({"bugbear", "bear"}));
    set_short("a bugbear");
    set_long(
"A squat, ugly beast that looks kind of like a porcupine on steroids!  It\n"+
"doesn't look too smart....\n");
    set_spell_chance(0);
    set_spell_dam(0);
    set_level(11);
    set_whimpy(1);
	set_allowed_rooms("/players/slider/rooms/");
	set_speed(20);
    set_al(-100);
    add_money(500);
}
