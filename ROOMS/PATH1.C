/* path1.c */

#include "/players/slider/include/slider.h"

inherit "room/room";

reset(arg)
{
   while(!present("gnat 6")) {
      move_object(clone_object(MONSTERS+"gnat"), this_object());
    }

   if (arg) return;
}

init() {
   ::init();
   add_action("listen", "listen");
}

create() {
    set_short("Overgrown Path");

    set_long(
"You are on an overgrown path winding through a lush forest.  The sounds\n"+
"of birds and other wildlife fill you with a sense of well being.  The\n"+
"trail continues west.\n");
    add_item("birds", "Colorful birds are everywhere!");
    add_item("wildlife", "If you stand still and watch, you can "+
             "occasionally catch a glimpse\nof some strange and "+
             "beautiful creatures making their way through the woods.\n"); 
    add_exit("/room/newroom/main11", "east");
    add_exit(ROOMS+"path2", "west");
    set_light(1);
    add_property("outside");  // added by Frijoles
    reset(0);
}

listen() {
   if(present("gnat")) {
      write("The sound of the birds would be pleasant, if it werent' for\n"+
            "the damn gnat buzzing in your face!  Maybe you should kill it?\n");
   } else {
      write("You hear the songs of wild birds in the trees.  You think you"+
       " can hear\nsomething a little less pleasant in the background...\n"+
       "....but maybe it's just your imagination....\n");
   }
   return(1);
}
