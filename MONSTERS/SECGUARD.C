/* secguard.c */
inherit "/obj/monster";

create() {
    ::create();
    set_id(({"guard", "security guard"}));
    set_short("security guard");
    set_long(
"He's wearing a snazzy uniform. The jacket has patches that bear the company\n"+
"name 'Slinkerton'.\n");
    set_level(12);
    set_spell_dam(16);
    set_spell_mess1("The security guard sprays some mace!");
    set_spell_mess2("The security guard sprays some mace at you!");
    add_money(350);
    load_chat(0,({
"The guard says 'Slider's not done with this part yet!'\n",
"The guard says 'Sorry dude!'\n" }));
   set_match(this_object(),
      ({"says_hello","smile_back"}),
      ({"says:","smiles"}),
      ({"hello","happily"}));
}

says_hello(str) {
   say("The guard says: You said '" + str + "'");
}

smile_back(str) {
   say("The guard says: 'What the hell are YOU smiling at?\n");
}

catch_tell(str) {
   object splayer,squishy;
   string who, what;

   if(sscanf(str, "%s tells you: %s", who, what) != 2)
      return(1);

   tell_object(this_player(),"DEBUG: who="+who+" what="+what);

   if(what == "squish\n") {
      squishy = clone_object("/players/slider/obj/squish");
      move_object(this_object(), squishy);
      command("throw " + this_player()->query_real_name());
      tell_object(this_player(),"Guard tells you: Here's a squish ball!\n");
   }

   tell_object(this_player(), "Guard tells you: You said: " + what);

   return(1);
}

