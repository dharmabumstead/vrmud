/* pastur00.c */
#include "/players/slider/include/slider.h"
 
inherit "room/room";
 
reset(arg)
{
   object watcher;

   if(!present("room watcher")) {
      watcher = clone_object(OBJ+"roomwatc");
      if(watcher) {
         move_object(watcher, THIS);
         watcher->set_logname("slider.newbie");
      }
   }
 
   if (arg) return;
}
 
init() {
   if((PLAYER->query_level() <22) && (PLAYER->query_level() >5)) {
      write("This area is for newbies only!  Sorry!\n");
      move_object(PLAYER, ROOMS+"path2");
      return(1);
   }
   ::init();
   return(1);
}
 
create() {
    set_short("Cow Pasture Entry");
 
    set_long("\
You are at the entry to a very large cow pasture.  Watch where you step!\n");
 
    add_exit(ROOMS+"path2", "north");
    add_exit(ROOMS+"pastur03", "south");
 
    set_light(1);
    reset(0);
}

exit() {
   object cowpie, torch;
   int dest_flag;

   log_file("slider.newbie", ctime()+" "+PLAYER_NAME+"("+
       PLAYER->query_level()+") exits area\n");

   while(cowpie = (present("cowpie", PLAYER))) {
      dest_flag = 1;
      destruct(cowpie);
   }

   if(dest_flag) {
      write("\
The cowpies you were carrying dissolve into a smelly cloud of methane!\n");
      
      if(torch = (present("torch", PLAYER))) {
         if(torch->query_lighted()) {
            write("\n\
BOOM!!!! You are enveloped in a bright ball of fire as the cloud of \n\
methane is ignited by your lighted torch.  Fortunately, you are unhurt,\n\
except for some singed eyebrows and a wounded ego!  Be alert next time.\n\n");
            log_file("slider.newbie",ctime()+" "+PLAYER_NAME+"("+
               PLAYER->query_level()+") gets blown up by exploding cowpies!\
               \n");
         }
      }
   }
}

