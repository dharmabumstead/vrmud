/* elpub01.c
 * last update 11/07/93
 */
 
inherit "std/inn";
 
#include "/players/slider/include/slider.h"
 
reset() {
    if (!present("list"))
        move_object(clone_object("obj/level_list"),this_object());
}
 
sit(str) {
        if ((str == "barstool") || (str == "on barstool") || (str == "stool") || (str == "on stool")) {
           write("You take a seat on the nearest barstool.\n");
        return 1;
        }
 
        if ((str == "booth") || (str == "booths")) {
           write("You slip into a comfortable booth.\n");
           return 1;
        }
        write("Sit where?\n");
        return 1;
}
 
read(str) {
   if (str == "menu") {
        display_menu();
        return 1;
   }
   else return 0;
}
 
create() {
    ::create();
    add_menu_item("beer","Slider's Draft Beer on tap!",3,"drink_alco",
                  " buys a Slider's Premium draft!",
                  "The draft goes down smoothly!");
    add_menu_item("margarita","The best damn margarita on VR!",12,"drink_alco",
                  " gets a margarita!",
                  "Salt, lime, triple sec, and a lotta tequila!  Mmmm!");
    add_menu_item("coke", "A large Coke", 25,"drink_soft",
                  " orders a large Coke",
                  "Always Coca-Cola!");
    add_menu_item("whiskey","Oak-aged Elwoode Whiskey",30,"drink_alco",
                  " downs a shot of Elwoode Whiskey!",
                  "You feel as if someone kicked you in the head!");
    add_menu_item("volcano", "The volcano!", 50, "drink_alco",
                  " manages to drink an entire volcano!",
 "The world swims away!  After a moment, you pick yourself up off the floor!");
    add_menu_item("cheese","A cheese appetizer",1,"eat_food",
                  " buys a slice of cheese.",
                  "You munch away happily.");
    add_menu_item("pretzels","A bowl of pretzels",5,"eat_food",
                  " downs a bowl of pretzels.",
                  "You scarf the pretzels down.");
    add_menu_item("bread","A loaf of freshly baked bread",10,"eat_food",
                  " rips into a loaf of bread.",
                  "The bread is very filling!");
    add_menu_item("sandwich","A wyvern-steak sandwich",25,"eat_food",
                  " enjoys a wyvern-steak sandwich!",
                  "Mmm! That really hits the spot!");
    add_menu_item("steak","A fine 22-ounce steak",50,"eat_food",
                  " orders up a fine 22-ounce steak.",
                  "The steak makes for a fine meal!");
    set_short("The Elwoode Tavern");
    set_long(
"Welcome to the Elwoode Tavern.  This renowned watering hole is THE spot for\n"+
"the Elwoode locals.  An ornately carved wooden bar stretches the length of\n"+
"the establishment, and is lined with high-backed leather stools.  Deep, \n"+
"comfortable leather and oak booths line the walls, which are covered with\n"+
"various pictures of local celebrities and regulars, as well as trophies\n"+
"from adventures both recent and long faded into legend.  A menu with the \n"+
"tavern's daily specials is on the wall.\n");
    add_item("bar","It's a magnificent oak bar.  Oh, the stories it could tell!");
    add_item("drink","There's a large selection - read the menu!");
    add_item("drinks","There's a large selection - read the menu!");
    add_item("food","It smells great!  Check the menu for the daily specials.");
    add_item("barstool","It is a tall leather barstool, worn shiny with age.");
    add_item("barstools","It is a tall leather barstool, worn shiny with age.");
    add_item("booth", "The booths look very comfortable....and private.");
    add_item("booths", "The booths look very comfortable....and private.");
    add_item("menu","Read this for the daily specials!");
    add_exit(ROOMS+"elwood01","north");
    set_light(1);
    reset();
}
 
init() {
    ::init();
    add_action("read","read");
    add_action("sit","sit");
}
 
int cost(int strength) {
    int x;
    x = (4*strength + strength*strength/10);
    return (x-(x/10));
}
