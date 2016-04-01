/* Silly's Cool T-Shirt Object
 * hacked 11/18/94 by Slider to allow saving description
 */

inherit "std/move";
#define QRN query_real_name()
#define TP this_player()
#define SAVE_NAME "/players/slider/logs/"+ TP->QRN + ".shirt"
 
inherit "obj/armour"; 
 
id(str){ return (str=="shirt") || (str=="t-shirt"); }
 
int counter;
 
reset(arg) {
        if (arg) return;
        set_name("t-shirt");
        set_alias("t-shirt");
        set_short("a Smiley Face t-shirt (worn)");
        set_long("It's a brand new white Smiley Face t-shirt (worn)\n");
        counter=0;
        set_value(0);
        set_weight(1);
        set_type("other");
        set_ac(0);
        set_heart_beat(1);
}
 
create() {
   int x;
   string check_name;

   check_name = SAVE_NAME + ".o";

   x = exists(check_name);
 
 
   if(x == 1) {
      restore_object(SAVE_NAME);
   } else {
      change("blank");
   write("Type 'change <message>' to change your t-shirt!\n");
   }
}
 
init(){
   add_action("change","change");
   add_action("go_slider","slider");
}
 
go_slider() {
   write("You say the magic word and are transported to Slider's workroom.\n");

   move_object(this_player(), "/players/slider/workroom");
   this_player()->look();                  
   return(1);
}

illegal(){
  return 1;  /* why? */
}
 
change(str) {
    if (!str) return 0;
    else {
        set_short("a "+str+" t-shirt (worn)");
        set_long("It's a brand new "+str+" t-shirt (worn)\n");
    }
   write("Your t-shirt now reads: '" + str + "'.\n");
   save_object(SAVE_NAME);
return 1;
}
 
drop(){
write("You can not drop this!"+ctime(time()) + "\n");
 return 1;
}
 
heart_beat() {
        counter = counter + 1;
       if (counter > 2500 ) {
            tell_object(environment(),"You feel very warm in your fuzzy t-shirt.\n");
            counter=0;
        }
 return;
}
 
query_auto_load() {
  return "/players/slider/obj/tshirt:";
}
