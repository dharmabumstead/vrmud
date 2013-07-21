inherit "std/move";
/***************************************************************************
 * NAME:                                                                   *
 *    fingtrik.c                                                             *
 * DESCRIPTION:                                                            *
 *    Slider's Chinese Finger Torture                                      *
 * VERSION:                                                                *
 *    1.0                                                                  *
 * ENVIRONMENT:                                                            *
 *    End Of The Line - LPMud 3.1.2-DR                                     *
 * UPDATE HISTORY                                                          *
 *    04/22/93  Slider Initial version                                     *
 ***************************************************************************/

status trapped;
object owner;

id(str) { return ((str== "gadget") || (str=="thing") || 
          (str == "trick") || (str == "gag") || (str == "torture")); 
}

string short_desc;

short() { return short_desc; }

long() {
  write(
"This is a neat little gadget of some sort.  It looks like a weird spring\n"+
"wrapped in decorative crepe paper, with openings at both ends.  There's\n"+
"some Chinese writing on it.  Maybe you could 'use' the thing?\n");
  return 1;
}

create()  {
   set_short("some sort of Chinese gadget");
}

get() { return 1; }

drop() { return 0; }

init() {
   /* Add our commands */
   add_action("use", "use");
   add_action("pull", "pull");
   add_action("push", "push");
   add_action("trap_get", "take");
   add_action("trap_get", "sell");
   add_action("trap_get", "buy");
   add_action("trap_get", "drop");
   add_action("trap_get", "get");
   add_action("trap_get", "give");
   add_action("trap_get", "kill");
   add_action("trap_get", "wave");
   add_action("trap_get", "hug");
   add_action("read", "read");
   owner = this_player();
}

read(string thing) {
   if (environment(this_object()) == this_player())
   {

      if(!thing) return(0);
      
      if(id(thing)) {
         write("The Chinese writing is much too tiny to read!\n");
         say(owner->query_name()+" peers quizically at a strange toy.\n");
         return(1);
      }
   }
}


push(string thing) {
   if (environment(this_object()) == this_player())
   {

      if(!thing) return(0);
      
      if(id(thing)) {
         write(
"Phew!  The blood slowly returns to your fingers as you slip out of the\n"+
"Chinese finger torture.\n");
         say(this_player()->query_name() + 
            " manages to slip out of the Chinese finger torture!\n");
         trapped = 0;
         set_short("some sort of Chinese gadget");
         return(1);
      }
   }
}

pull(string thing) {
   if (environment(this_object()) == this_player())
   {

      if(!thing) return(0);
      
      if(id(thing)) {
         write(
"You pull furiously at the finger gag, only to have it tighten itself on\n"+
"your fingers!  Ouch!\n");
         say(this_player()->query_name() + " struggles frantically with a"+
            " Chinese finger torture!\n");
         return(1);
      }
   }
}

trap_get() {
   if(trapped) {
      write(
"You can't do much of anything with your fingers stuck in this stupid toy!\n");
      say(this_player()->query_name()+ " flails about clumsily while trapped "+
         "in a Chinese finger torture!\n");
      return(1);
   }
   return(0);
}

use(string thing) {
   if (environment(this_object()) == this_player())
   {

      if(!thing) return(0);
      
      if(!trapped) {
         if(id(thing)) {
            write(
"You slip your fingers into either end of the gizmo.  Ho hum.  Big deal!\n");
            call_out("use2", 5);
            return(1);
         }
      } else {
         if(id(thing)) {
            write("You pull on the gadget, but only succeed in getting more"+
               " stuck!\n");
            say(owner->query_name()+ " fumbles with a Chinese finger gadget!\n");
            return(1);
         }
      }
   } 
}

use2() {
   tell_object(owner,
"To your horror, you discover that your fingers are STUCK in the gizmo! \n"+
"You pull on the gadget, but to no avail!  On closer inspection, you \n"+
"realize that you've just fallen for the old Chinese finger torture gag!\n");
   tell_room(environment(owner), capitalize(owner->query_name())+
      " becomes trapped in a Chinese finger gag!\n", ({owner}));
   trapped = 1;
   set_short("a Chinese finger torture gag");
}

set_short(str) {
  short_desc=str;
}

query_value()
{
   return(50);
}

