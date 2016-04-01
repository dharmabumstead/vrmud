/***************************************************************************
 * NAME:                                                                   *
 *    pizza.c                                                              *
 * DESCRIPTION:                                                            *
 *    A Slider's Premium Pizza!                                            *
 * VERSION:                                                                *
 *    1.2                                                                  *
 * ENVIRONMENT:                                                            *
 *    Virtual Realities - LPMud 3.1.2-DR                                   *
 * UPDATE HISTORY                                                          *
 *    04/02/1993  Slider  Initial version                                       *
      08/27/2002  Slider  Add inherit of std/object
 ***************************************************************************/
inherit "std/object";

int slices;           /* number of pieces! */
int bvalue;           /* initial value */
string short_desc;    /* Short description holder */
string long_desc;     /* Long description holder */ 

create()  
{
   slices = 12;
   bvalue = slices * 10;

   set_short("A pizza");
   set_long(
"A piping hot Slider's Pizza!  There's gobs of cheese all over it, and little\n"+
"pools of grease form tiny lakes in the pepperoni slices!  Mmmmm...I'll bet it'd\n"+
"be good with some beer!\n");
}

init()
{
   /* Add our commands */
   add_action("eat_pizza", "eat");
   return(1);
}

id(str)
{
  return((str == "pizza") || (str == "box"));
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

eat_pizza(string thing)
{
   /* Check argument */
   if(id(thing))
   {
      /* Make sure we drink the one we're holding! */ 
      if (environment(this_object()) == this_player())
      {

         /* See if the can is empty */
         if(slices == 0)
         {      
            write("The pizza is history!\n");
            say(this_player()->query_name()+" scrounges in the box for some"+
               " more pizza but fails!\n");
            return(1);
         } 
        
         /* See if this slice will finish the pizza */
         if((--slices) == 0)
         {
            write("You finish off the last of the pizza.\n");
            say(this_player()->query_name()+" finishes off the pizza.\n");
            set_short("An empty pizza box.");
            set_long("A Slider's Pizza box!  It's empty!\n");
            bvalue = 0;
         } else {    
            /* Just take a slice */
            write("You mow down a slice of the pizza.\n");
            set_long("A partially chowed-on Slider's Pizza!\n");
            set_short("A partially eaten pizza");
            bvalue = (slices * 10);
            say(this_player()->query_name()+" mows down a slice of pizza!\n");
         }
 
         return(1);
      }
      return(0);
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
