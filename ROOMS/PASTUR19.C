/* pastur19.c
 * updated 12/13/93
 * update again 8/29/95
 */
 
#include "/players/slider/include/slider.h"
#define NAP_NAME capitalize(NAP_PLAYER->query_real_name())
 
inherit "room/room";
 
object NAP_PLAYER;
 
reset(arg)
{
   while(!present("heifer 2")) {
      move_object(clone_object(MONSTERS+"heifer"), THIS);
   }
 
   if (arg) return;
}
 
init() {
   ::init();
   add_action("climb_tree", "climb");
   add_action("take_nap", "nap");
}
 
create() {
   set_short("Southeast Pasture");
 
   set_long("\
This part of the pasture is dominated by a huge oak tree.  Its enormous\n\
limbs stretch up into the sky and nearly out of site.  The light breeze\n\
and gentle rustling of the leaves might make this a nice spot for a 'nap'.\n");
 
   add_exit(ROOMS+"pastur14", "north");
   add_exit(ROOMS+"pastur20", "east");
   add_exit(ROOMS+"pastur18", "west");
   add_exit(ROOMS+"pastur15", "northeast");
   add_exit(ROOMS+"pastur13", "northwest");
 
   add_item(({"fence","wire","barbed wired"}),
      "It's a nasty looking barbed wire fence. Better leave it alone.");
 
   add_item("tree",
"It's a lovely and enormous old oak tree.  Its powerful limbs thrust upward\n\
into the sky.  The shade underneath the tree looks very comfy.");
 
   set_light(1);
   reset(0);
}
 
take_nap() {
   if(!NAP_PLAYER) {
      NAP_PLAYER = this_player();
      write("You plop down beneath the shade tree for a nice nap....\n");
 
      tell_room(environment(NAP_PLAYER), NAP_NAME +
         " plops down beneath the oak tree for a nap.\n", ({NAP_PLAYER}));
 
      call_out("nap_2", 10);
   } else {
      write(capitalize(NAP_NAME) +
         " is already sleeping here. Try again later.\n");
   }
   return(1);
}
 
nap_2(number) {
   if(left_room() == 1) return(1);
 
   tell_object(NAP_PLAYER, "Your eyelids are growing heavy.\n");
   tell_room(environment(NAP_PLAYER), NAP_NAME +
      " starts nodding off!\n", ({NAP_PLAYER}));
   call_out("nap_3", 10);
}
 
nap_3() {
   if(left_room() == 1) return;
 
   tell_object(NAP_PLAYER, "You sink into sleep....\n");
   tell_room(environment(NAP_PLAYER), NAP_NAME +
      " falls asleep!\n", ({NAP_PLAYER}));
   NAP_PLAYER->heal_self(2);
   call_out("nap_4", 10);
}
 
nap_4() {
   if(left_room() == 1) return(1);
 
   tell_object(NAP_PLAYER, "You start to dream....\n");
   tell_room(environment(NAP_PLAYER), NAP_NAME +
      " mutters something from the depths of sleep.\n", ({NAP_PLAYER}));
   NAP_PLAYER->heal_self(2);
   call_out("nap_5", 10);
}
 
nap_5() {
   if(left_room() == 1) return(1);
 
   tell_object(NAP_PLAYER, "\
A man descends from the sky on a flaming pie!  He looks vaguely familar to\n\
you, but you're not sure why.  He smiles at you for a moment, and then he\n\
speaks.  He says something, but you can't make out what it is.  His voice\n\
sounds like it's playing backwards!\n");
   tell_room(environment(NAP_PLAYER), NAP_NAME +
      " is sleeping soundly.\n", ({NAP_PLAYER}));
   NAP_PLAYER->heal_self(10);
   call_out("nap_6", 15);
}
 
nap_6() {
   if(left_room() == 1) return(1);
 
   tell_object(NAP_PLAYER, "\n\
You awake with a start, the last traces of the dream fading from your mind.\n\
What a weird dream....better lay off the spicy food for awhile! Maybe you \n\
should come back again, when you're more experienced, and take another nap?\n\
You do notice that you feel strangely refreshed...like your batteries have \n\
been recharged.\n");
 
   tell_room(environment(NAP_PLAYER), NAP_NAME +
      " awakes with a start!\n", ({NAP_PLAYER}));
 
   NAP_PLAYER = 0;
}
 
left_room() {
   /* If player leaves room, reset object holder, show message, and bail */
   if(environment(NAP_PLAYER) != this_object()) {
      tell_object(NAP_PLAYER,
         "You awake with a start! You've been sleepwalking!\n");
      NAP_PLAYER = 0;
      return(1);
   } else {
      return(0);
   }
}
 
climb_tree(str) {
   if((str == "tree") || (str == "oak")) {
      write("This area is under construction.  Watch for it soon!\n");
      return(1);
   }
}
 
