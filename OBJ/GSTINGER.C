/* gstinger.c */
inherit "obj/weapon";

reset(arg) {
    ::reset(arg);
    if(arg)
        return;
    set_name("stinger");
    set_class(20);
    set_short("A giant spider's stinger");
    set_long(
"A deadly stinger from a giant spider.  Venom drips from the razor sharp edge!\n"+
"It looks as if it would render its holder almost invincible in battle!\n");
    set_weight(5);
    set_value(8000);
    set_hit_func(this_object());
}
/* weapon hit changed by llel.. was too high */

weapon_hit(victim) {
   if(random(100) < 100) {
      write("The stinger oozes venom and seeks its victim!\n");
      return(random(10));
   }
   return(0);
}
wield() {
   write("You feel a surge of nausea as you wield the stinger!\n");
   return(1);
}

