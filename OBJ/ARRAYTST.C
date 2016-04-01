/***************************************************************************
 * NAME:                                                                   *
 *    arraytst.c                                                             *
 * DESCRIPTION:                                                            *
 *    Slider's Array Experiment                                            *
 * VERSION:                                                                *
 *    1.0                                                                  *
 * ENVIRONMENT:                                                            *
 *    End Of The Line - LPMud 3.1.2-DR                                     *
 * UPDATE HISTORY                                                          *
 *    04/22/93  Slider Initial version                                     *
 ***************************************************************************/

status first;
string *list;
object owner;

id(str) { 
   return (str== "tester"); 
}

string short_desc;

short() { return short_desc; }

long() {
  write(
"This is an array tester.  You can 'add <name>', 'list', 'delete <name>',\n"+
"'change <name> <newname>.  This is so Slider can play with arrays in LPC!\n");
  return 1;
}

create()  {
   list = allocate(0);
   set_short("an array tester");
}

get() { return 0; }

drop() { return 0; }

init() {
   /* Add our commands */
   add_action("add_item", "add");
   add_action("list_items", "list");
   add_action("delete_item", "delete");
   add_action("change_item", "change");
}

add_item(str) {
   if(!str) return 0;
   list+=str;
   write("Added item " + str + " to array tester.\n");
   
/*    if(first) {
      allocate(list);
      list==str;
      first = 1;
   } else {
      list+=str;
   }
*/ 
   return 1;
}

list_items() {
   int counter;
   
   for(counter = 0; counter < sizeof(list); counter++)
      write(counter + ": " + list[counter]+"\n");
   
   return(1);
}

delete_item(target) {
   int offset;
   
   if(!target) return 0;
   
/*    if((offset = searcha(list, target)) == -1) { */
   if((offset = member_array(target, list)) == -1) {
      write(target + " not found!\n");
      return 1;
   } else {
      list-=list[offset];
      write("Removed item " + target + " from tester.\n");
   }
   return 1;
}
   
set_short(str) {
  short_desc=str;
}

query_value()
{
   return(50);
}

