/***************************************************************************
 * NAME:                                                                   *
 *    bcake.c                                                              *
 * DESCRIPTION:                                                            *
 *    A birthday cake!                                                     *
 * VERSION:                                                                *
 *    1.0                                                                  *
 * ENVIRONMENT:                                                            *
 *    Virtual Realities - LPMud 3.1.2-DR                                   *
 * UPDATE HISTORY                                                          *
 *    03/23/93  JSB  Initial version                                       *
 ***************************************************************************/


int lit;
int pieces;
int candles;
string cake_msg;
string short_desc;    /* Short description holder */
string long_desc;     /* Long description holder */ 

create()  
{
   lit = 1;
   pieces = 6;
   candles = 10;
   cake_msg = "This space for rent!";

   set_short("A birthday cake");
   set_long("A birthday cake with " + candles +" lit candles on "+
            " it! There's something\nwritten on it!\n");
}

init()
{
   /* Add our commands */
   add_action("eat_cake", "eat");
   add_action("blow_cake", "blow");
   add_action("read_cake", "read");
   add_action("decorate_cake", "decorate");
   add_action("light_cake", "light");
}

id(str)
{
  return((str == "cake"));
}

short()
{
   return(short_desc);
}

long()
{
   write(long_desc);
}
 

get()
{
   return(1);
}

drop()
{
   return(0);
}
   
light_cake(string thing)
{
   if(id(thing))
   {
      if (environment(this_object()) == this_player())
      {
         if(lit ==1)
         {
            write("The cake's already lit!\n");
         } else {
            write("You light the candles on the cake!\n");
            say(this_player()->query_name()+" lights the candles "+
                "on a birthdday cake!\n");
            lit = 1;
         }
         return(1);
      }
      return(0);
   }
   return(0);
}
        
      
eat_cake(string thing)
{
   /* Check argument */
   if(id(thing))
   {
      /* Make sure we drink the one we're holding! */ 
      if (environment(this_object()) == this_player())
      {

         /* See if the cake is lit */
         if(lit == 1)
         {
            write("Ow! You fry your face on the lit candles! Try"+
                  "'blow'ing out the candles\non the 'cake'!\n");
            say(this_player()->query_name()+" attempts to eat a lit"+
                  " birthday cake! Ouch!\n");
            return(1);
         }

         /* See if the cake is gone */
         if(pieces == 0)
         {      
            write("There's nothing left but a few crumbs\n");
            say(this_player()->query_name()+" scrounges a few "+
                 " crumbs from an empty cake pan.\n");
            return(1);
         } 
        
         /* See if this bite will finish the cake */
         if((--pieces) == 0)
         {
            write("You finish off the cake.\n");
            say(this_player()->query_name()+" scarfs the last of"+
                " the birthday cake!\n");
            set_short("An empty cake pan");
            set_long("This used to be a birthday cake.  There's"+
                     " nothing but a few crumbs left in the pan!\n");  
         } else {    
            /* Just take a bite */
            write("You scarf a piece of the birthday cake!\n");
            set_long("A partially scarfed birthday cake.\n");
            set_short("A partially eaten birthday cake");
            say(this_player()->query_name()+" eats a piece of the "+
                " birthday cake.\n");
         }
 
         return(1);
      }
      return(0);
   }
   return(0);
}

blow_cake(string thing)
{
   if(id(thing))
   {
      if(lit == 1)
      {
         write("You blow out the candles on the cake!\n");
         say(this_player()->query_name()+" blows out the cake!\n");
         set_long("A birthday cake with " + candles +" candles on "+
            " it! There's something\nwritten on it!\n");
         lit = 0;
      } else {
         write("The candles aren't lit!\n");
         say(this_player()->query_name()+" blows on the birthday cake!\n");
      }
      return(1);
   }
   return(0);
} 
 
read_cake(string thing)
{
   /* Check argument */
   if(id(thing))
   {
      /* Make sure we drink the one we're holding! */ 
      if (environment(this_object()) == this_player())
      {
         if(pieces ==6)
         {
            write("The cake says:\n" + cake_msg + "\n");
            say(this_player()->query_name()+" reads a birthday cake.\n");
         } else {
            write("There's not enough cake left to read!\n");
            say(this_player()->query_name()+" tries to read a partially"+
                " eaten birthday cake.\n");
         }
         return(1);
      }
      return(1);
   }
   return(0);
}

decorate_cake(string msg)
{

   /* Make sure we drink the one we're holding! */ 
   if (environment(this_object()) == this_player())
   {
      if(pieces < 6)
      {
         write("It's a little LATE for that, don't you think!?\n");
         return(0);
      }
      cake_msg = msg;
      write("The cake now says:\n" + cake_msg + "\n");
      say(this_player()->query_name()+" decorates a birthday cake.\n");
      return(1);
   }
   return(0);
}
  
set_short(str) 
{
  short_desc=str;
}

set_long(str) 
{
   long_desc = str;
}