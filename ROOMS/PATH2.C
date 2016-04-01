/* path2.c */
#include "/players/slider/include/slider.h"
 
inherit "room/room";
 
reset(arg)
{
   while(!present("horsefly 6")) {
      move_object(clone_object(MONSTERS+"horsefly"), this_object());
    }
 
   if (arg) return;
}
 
init() {
   ::init();
   add_action("listen", "listen");
}
 
create() {
    set_short("Thick Path");
 
    set_long("\
This is a thickly overgrown path through the forest.  It looks as though\n\
no one has been this way in several years.  The occasional sound of a\n\
bird or a deer reaches to you from somewhere in the underbrush. The path\n\
continues east and west from here, and you hear something strange from the\n\
south. Sounds like....cows?\n");
 
    add_exit(ROOMS+"pastur00","south");
    add_exit(ROOMS+"path3", "west");
    add_exit(ROOMS+"path1", "east");
    set_light(1);
    add_property("outside");  // added by Frijoles
    reset(0);
}
 
listen() {
   if(present("horsefly")) {
      write("You think you can hear a faint mooing sound from the south, "+
         "but it's \nbeing drowned out by an annoying horsefly!\n");
   } else {
    write("You think you can make out mooing from the south.\n");
    write("Maybe you should investigate?\n");
   }
   return(1);
}
 
