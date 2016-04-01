/* bull.c
 * last updated 12/10/93
  */
 
inherit "/obj/monster";
 
create() {
   ::create();
   set_id("bull");
   set_short("a bull");
   set_long("An ornery looking bull.  He *looks* pretty mean....\n");
   set_level(2);
   set_spell_dam(0);
   set_ac(3);
   set_wc(6);
   add_money(60);
}
 
