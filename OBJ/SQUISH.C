inherit "/std/move";
/***************************************************************************
 * NAME:                                                                   *
 *    squish.c                                                             *
 * DESCRIPTION:                                                            *
 *    Slider's Squish Ball                                                 *
 * VERSION:                                                                *
 *    1.1                                                                  *
 * ENVIRONMENT:                                                            *
 *    End Of The Line - LPMud 3.1.2-DR                                     *
 * UPDATE HISTORY                                                          *
 *    01/10/93  JSB  Initial version                                       *
 *    01/19/93  JSB  Added code to display message destination player's    *
 *                   room in 'throw_ball()'                                *
 ***************************************************************************/

id(str)
{
   return((str == "ball") || (str == "squish"));
}

short()
{
   return "Slider's Squish Ball";
}

long()
{
   write("This is Slider's Squish Ball.  Type 'help ball' for info\n");
}

drop()
{
   return 0;
}

get()
{
   return 1;
}


init ()
{
   /* Add our commands */
   add_action("help_ball", "help");
   add_action("squeeze_ball", "squeeze");
   add_action("toss_ball", "toss");
   add_action("throw_ball", "throw");
}

throw_ball(string towho)
{
   object toplayer;

   /* Find the destination player */
   if((toplayer = find_player(towho)) == 0)
   {
      /* Not on, so show error message */
      write(capitalize(towho) + " is not logged in!\n");
      return(1);
   }
   
   if(toplayer->query_edit())
   {
      write(capitalize(towho) + " is editing right now...maybe later!\n");
      return(1);
   }


   /* Show source player message */
   write("You toss the squish ball to " + capitalize(towho) + ".\n");

   /* Tell source player's environment */
   say(capitalize(this_player()->query_name())+
      " tosses a squish ball to "+capitalize(towho)+".\n");

   /* Tell the destination player what's going on */
   tell_object(toplayer, "You deftly catch a squish ball thrown to you by "+
      capitalize(this_player()->query_name())+".\n");

   /* Display a message in the destination player's room, excluding the
    * destination player, of course! Note the third argument to tell_room;
    * we need to pass an array of objects to exclude from the tell_room,
    * so we create one on the fly with ({object}) to create a single-
    * element array. */
   tell_room(environment(toplayer), capitalize(towho)+" leaps into the air "+
             "and catches a squish ball thrown by "+
             capitalize(this_player()->query_name())+"!\n", ({toplayer}));

   /* Move the squish ball to the target player */
   move_object(this_object(), toplayer);
   return(1);
}

toss_ball(string thing)
{
   /* Check argument */
   if(id(thing))
   {
      /* Write player's message */
      write("You toss the squish ball into the air.  It lands in your palm"+
            " with a \nmysteriously satisfying *thunk*!\n");

      /* Write player's environment message */
      say(this_player()->query_name()+" tosses a squish ball into the air "+
          "and deftly catches it!\n");

      return(1);
   }
   return(0);
}

squeeze_ball(string thing)
{
   /* Check the command argument */
   if(thing == "ball")
   {
      /* Write player's message */
      write("You feel the tensions melt away as you squeeze the squish ball "+
	    "between\nyour fingers.\n");

      /* Write room message */
      say(this_player()->query_name()+" squeezes a squish ball and looks "+
          "more relaxed somehow.\n");

      return(1);
   }
   return(0);
}

help_ball(string thing)
{
   /* Check command argument */
   if (thing == "ball")
   {
      /* Show player message */
      write("It's a squish ball!  You can 'squeeze' it, 'toss' it, or\n");
      write("'throw <player>' to throw it to someone.\n");

      /* Show room message */
      say(this_player()->query_name()+" peers quizically at a squish ball.\n");

      return(1);
   }
   return(0);
}

query_value()
{
   return(80);
}

