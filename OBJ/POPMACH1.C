/* Silly's Coke Machine
 * modified 11/07/93 by Slider
 */
 
inherit "obj/monster";
 
id(str) {return (str == "machine" || str == "soda machine");}
 
int cans, strength, value;
 
reset(arg)
{
    ::reset(arg);
     if (arg) return;
     cans=24;
     strength = 25;
     value = (4*strength + strength^2/10)*2;
     set_name("A soda machine");
     set_race("machine");
     set_alias("machine");
     set_short("A soda machine");
     set_long("Jolt Cola!\n"+
              "This is a soda machine.  Get your Jolt cola here!\n"+
              "There is a slot where you can deposit "+value+" coins.\n"+
              "The machine has "+cans+" cans of soda left.\n");
     set_level(12);
     set_aggressive(0);
     set_spell_mess1("The machine spits acidic soda all over you!");
     set_spell_mess2("The soda machine shoots a soda can at you!");
     set_al(0);
     add_money(0);
}
 
regen() {
  object machine;
  machine=clone_object("/players/slider/obj/popmach1");
  move_object(machine,environment(this_object()));
  tell_room(environment(this_object()),"A Jolt truck drives in and drops off a new Jolt machine.\n",);
  return 1;
}
 
second_life(){
     regen();
   ::second_life();
}
 
init() {
   ::init();
   add_action ("deposit", "deposit");
}
 
deposit (str) {
   object drink;
   if (str != "coins") return 1;
   if (cans == 0) {
      write("The machine chunks helplessly.  Looks like its empty.\n");
      return 1;
   }
   if (this_player()->query_money() < value) {
      write("Sorry, you don't have " + value + " coins to deposit into the machine.\n");
      return 1;
   }
   write ("You deposit "+value+" coins into the slot.\n");
   this_player()->add_money(-(value));
   this_object()->add_money(value);
   cans--;
   if (cans == 0) {
     set_long("Jolt Cola!\n"+
              "This is a soda machine.  It only has one type of soda though.\n"+
            "There is a slot where you can deposit "+value+ " coins.\n"
+
            "The machine is EMPTY!\n");
   } else
   if (cans == 1) {
     set_long("Jolt Cola!\n"+
              "This is a soda machine.  It only has one type of soda though.\n"+
            "There is a slot where you can deposit "+value+" coins.\n"+
            "The machine only has 1 can of soda left! Better buy it!\n");
   } else {
     set_long("Jolt Cola!!\n"+
              "This is a soda machine.  It only has one type of soda though.\n"+
            "There is a slot where you can deposit "+value+" coins.\n"+
            "The machine has "+cans+" cans of soda left.\n");
   }
   write ("As soon as the last coin is deposited a can of soda rolls out.\n");
   say (this_player()->query_name()+" gets a soda from the soda machine.\n", this_player());
   drink = clone_object ("/obj/drink");
   drink->set_name("cola");
   drink->set_alias("soda");
   drink->set_short("A can of Jolt Cola");
   drink->set_long("A can of Jolt.  All the sugar and twice the caffeine!\n");
   drink->set_value(value);
   drink->set_weight(1);
   drink->set_strength(strength);
   drink->set_drinker_mess("You pop open the can of Jolt and guzzle it down.  Your head starts to buzz!\n");
   drink->set_drinking_mess(" pops open a can of Jolt cola and powers it down.\n");
   drink->set_empty_container("can");
   transfer(drink, this_player());
   return 1;
}
