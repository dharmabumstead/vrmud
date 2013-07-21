/* claudia.c */
#include "/players/slider/include/slider.h"

inherit "/obj/monster";

init() {
    ::init();
    if(!present("swimsuit"))
       move_object(clone_object(OBJ+"swimsuit"), this_object());

}

create() {
    string playername;

    ::create();
    set_id(({"claudia"}));
    set_short("Claudia Shiffer");
    set_level(10);
    set_long(
"Whatta hot babe!  She's staring right at you!\n");
    load_chat(10,({
"Claudia says: 'Ooooh!  Wanna get lucky!?'\n",
"Claudia says: 'Oooh,  gimme all your hot monkey love, you wonder stud!'\n",
"Claudia hisses: 'Spank me!'\n",
"Claudia moans 'I wanna banana!'\n",
"Claudia screams 'Ooooh! I love a man who hacks Microsoft Visual C++!'\n" }));
    add_money(1000);
    init();
    command("wear swimsuit");
    set_ac(10);

}
