/* gstinger.c */
inherit "obj/weapon";

reset(arg) {
    ::reset(arg);
    if(arg)
        return;
    set_name("stinger");
    set_class(21);
    set_short("A giant spider's stinger");
    set_long(
"A deadly stinger from a giant spider.  Venom drips from the razor sharp edge!\n"+
"It looks as if it would render its holder almost invincible in battle!\n");
    set_weight(5);
    set_value(8000);
    set_hit_func(this_object());
/* Picard didn't think this over well enough.. removing - Frij
    make_unique(1); // This is probably the most powerful weapon
                    // in the game.  Uniqueness is probably a
                    // good idea. :) Picard 3/21/97
*/
}
// Changed hit and chance values since this weapon is only available
// after wading through 3 level 16 monsters and one mean level 18.
// This was originally cleared with several Elders+ in 1993.  - Slider 3/27/96

// Changed the write message to use the melee channel. -- Frij 2/2008

weapon_hit(victim) {
   if(random(100) < 50) {
      message("melee", "The stinger oozes venom and seeks its victim!\n", this_player());
      return(random(50));
   }
   return(0);
}
wield(str) {
	if (!id(str)) 
		return 0;
   write("You feel a surge of power as you wield the stinger!\n");
   return ::wield(str);
}

