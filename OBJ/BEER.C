inherit "/std/move";
/***************************************************************************
 * NAME:                                                                   *
 *    beer.c                                                               *
 * DESCRIPTION:                                                            *
 *    A can of Slider's Premium Beer                                       *
 * VERSION:                                                                *
 *    1.2                                                                  *
 * ENVIRONMENT:                                                            *
 *    Virtual Realities - LPMud 3.1.2-DR                                   *
 * UPDATE HISTORY                                                          *
 *    01/27/93  JSB  Initial version                                       *
 *    01/27/93  JSB  Added closed/open stuff                               *
 *    03/22/93  JSB  Converted for VR                                      *
 *    03/23/93  JSB  Added 'crush' and 'shotgun'
 ***************************************************************************/
 
int drinks;           /* six swigs a can! */
int bvalue;           /* initial value */
status isopen;        /* Is the can open or not? */
status iscrushed;     /* Is it crushed? */
string short_desc;    /* Short description holder */
string long_desc;     /* Long description holder */
 
create()
{
   drinks = 6;
   bvalue = 3000;
   isopen = 0;
 
   set_short("A can of beer");
   set_long("A fresh, cold can of Slider's Premium beer.  Condensation"+
            " glistens \nfetchingly on the can.  Wouldn't you love to pop"+
            " it open and gulp it down?\n");
}
 
init()
{
   /* Add our commands */
   add_action("drink_beer", "drink");
   add_action("open_can", "open");
   add_action("crush_can", "crush");
   add_action("shotgun", "shotgun");
}
 
id(str)
{
  return((str == "beer") || (str == "can"));
}
 
short()
{
   return(short_desc);
}
 
long()
{
   write(long_desc);
}
 
query_value()
{
   return(bvalue);
}
 
get()
{
   return(1);
}
 
drop()
{
   return(0);
}
 
crush_can(string thing)
{
   /* Check argument */
   if(id(thing))
   {
      /* Make sure we drink the one we're holding! */
      if (environment(this_object()) == this_player())
      {
         if(iscrushed) {
            write("It's already been pulverized!\n");
            say(this_player()->query_name()+
               " attempts to further torture a crushed beer can!\n");
            return 1;
         }
 
         if(isopen == 0)
         {
            write(
"You attempt to crush the full can of beer against your head and manage\n"+
"to give yourself a nasty bruise!  Ow!\n");
            say(this_player()->query_name()+
" tries to crush a full can of beer on "+this_player()->query_possessive()+
" forehead and raises a nasty\nbruise!  Ouch!\n");
            iscrushed = 1;
            return(1);
         }
 
         if(drinks != 0)
         {
            write(
"You crush the beer can against your forehead and crush it!  Unfortunately\n"+
"the remaining beer in the can has soaked you!\n");
            say(
this_player()->query_name()+" crushes a partially filled beer can against "+
this_player()->query_possessive()+" forehead and gets soaked\nwith beer!\n");
         } else {
            write("You crush the beer can against your forehead!\n");
            say(this_player()->query_name()+
" crushes an empty Slider's Premium Beer can against "+
this_player()->query_possessive()+" forehead!\n");
         }
         set_short("A crushed, empty beer can");
         set_long("A crushed Slider's Premium Beer can!\n");
         drinks = 0;
         bvalue = 0;
         iscrushed = 1;
         return(1);
      }
      return(0);
   }
   return(0);
}
 
shotgun(string thing)
{
   /* Check argument */
   if(id(thing))
   {
      /* Make sure we drink the one we're holding! */
      if (environment(this_object()) == this_player())
      {
         if(isopen != 0)
         {
            write("Too late! It's already open!\n");
            return(1);
         } else {
            write(
"You rip a hole in the bottom of the can, pop the top off the can, and\n"+
"slam the whole can in one huge gulp!\n");
            say(this_player()->query_name()+" shotguns an entire beer!\n");
            set_short("An empty Slider's Premium beer can.");
            set_long(
"The remains of a Slider's Premium beer can.  Judging from the teeth marks\n"+
"in the can, it's obviously been shotgunned!\n");
            isopen = 1;
            drinks = 0;
            bvalue = 10;
            return(1);
         }
      }
      return(0);
   }
   return(0);
}
 
 
drink_beer(string thing)
{
   /* Check argument */
   if(id(thing))
   {
      /* Make sure we drink the one we're holding! */
      if (environment(this_object()) == this_player())
      {
 
         /* See if the can is open! */
         if(isopen == 0)
         {
            write("Ow!  Maybe you should OPEN the can first!?\n");
            say(this_player()->query_name()+" attempts to drink a"+
                " can of beer without opening it first and is\n"+
                "rewarded with a fat lip!\n");
            return(1);
         }
 
         /* See if the can is empty */
         if(drinks == 0)
         {
            write("The can is empty!\n");
            say(this_player()->query_name()+" attempts to drink an empty"+
                " can of beer.\n");
            return(1);
         }
 
         /* See if this drink will empty the can */
         this_player()->drink_alco(18);
 
         if((--drinks) == 0)
         {
            write("You finish off the can of beer.\n");
            say(this_player()->query_name()+" drains a can of beer.\n");
            set_short("An empty Slider's Premium beer can.");
            set_long("A Slider's Premium beer can.  Unfortunately, it's"+
                     " empty!\n");
            bvalue = 10;
         } else {
            /* Just take a swig */
            write("You take a swig from the can of beer.\n");
            set_long("An open can of Slider's Premium beer.  Looks like"+
                     " someone's been drinking\nout of it.\n");
            set_short("An open can of beer");
            bvalue = (bvalue - 50);
            say(this_player()->query_name()+" takes a swig from a can "+
                "of beer.\n");
         }
 
         return(1);
      }
      return(0);
   }
   return(0);
}
 
open_can(string thing)
{
   /* Check argument */
   if(id(thing))
   {
      /* Make sure we drink the one we're holding! */
      if (environment(this_object()) == this_player())
      {
         if(isopen == 1)
         {
            write("It's already opened!\n");
            say(this_player()->query_name()+" tries to re-open"+
                " an open can of beer.\n");
            return(1);
         } else {
            isopen = 1;
            write("PFFFT!  You pop open a can of Slider's Premium!\n");
            say(this_player()->query_name()+" pops open a can of Slider's"+
                " Premium beer!\n");
            set_long("A cold, open can of Slider's Premium beer.  "+
                     "Condensation glistens \nfetchingly on the can.  "+
                     "Wouldn't you love to chug it down?\n");
            set_short("A full, open can of beer");
            return(1);
         }
      }
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
