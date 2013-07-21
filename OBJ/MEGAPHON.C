/***************************************************************************
 * NAME:                                                                   *
 *    megaphon.c                                                           *
 * DESCRIPTION:                                                            *
 *    Slider's Megaphone                                                   *
 * VERSION:                                                                *
 *    1.0                                                                  *
 * ENVIRONMENT:                                                            *
 *    Virtual Realities -  LPMud 3.1.2-DR                                  *
 * UPDATE HISTORY                                                          *
 *    04/20/93  Slider    Initial version.                                 *
 ***************************************************************************/
inherit "std/move";

init() {
   add_action("megaphone", "mega");
   add_action("help_msg", "help");
}

megaphone(str) {
   int i, args, level, operator, checklevel;
   string message;
   object *player;

   if(!str) {
      this_object()->help_msg();
      return(0);
   }

   args = sscanf(str, "%s TO %s %d", message, operator, level);
   
/*    write("DEBUG:  message = '"  + message + "'\n");
      write("DEBUG: operator = '" + operator + "'\n");
      write("DEBUG:    level = '" + level + "'\n");
      write("DEBUG:     args = '" + args + "'\n");
*/
      
   /* Get the list of active players */
   player = users();

   /* Check all the active players */
   for(i = 0; i < sizeof(player); i++) {
      
      checklevel = player[i]->query_level() ;
      
      if(args < 3) {
         if(checklevel < 20) {
            write("Echoing to " + player[i]->query_name() + 
               " (" + checklevel + ")\n");         
            tell_object(player[i], str + "\n");
         }
      } else {
         switch(operator) {
            case "<":
               if((checklevel < level) && (checklevel < 20)) {
                  write("Echoing to " + player[i]->query_name() + 
                     " (" + checklevel + ")\n");
                  tell_object(player[i],message + "\n");
               }
               break;
            case ">":
               if((checklevel > level) && (checklevel < 20)) {
                  write("Echoing to " + player[i]->query_name() + 
                     " (" + checklevel + ")\n");
                  tell_object(player[i],message + "\n");
               }
               break;
            case "<=":
               if((checklevel <= level) && (checklevel < 20)) {
                  write("Echoing to " + player[i]->query_name() + 
                     " (" + checklevel + ")\n");               
                  tell_object(player[i],message + "\n");
               }
               break;
            case ">=":
               if((checklevel >= level) && (checklevel <20)) {
                  write("Echoing to " + player[i]->query_name() + 
                     " (" + checklevel + ")\n");
                  tell_object(player[i],message + "\n");
               }
               break;               
            case "==":
               if((checklevel == level) && (checklevel < 20)) {
                  write("Echoing to " + player[i]->query_name() + 
                     " (" + checklevel + ")\n");               
                  tell_object(player[i],message + "\n");
               }
               break;
            default:
               write("Unknown operator: '" + operator + "'\n");
               this_object()->help_msg();
               break;
         }
      }
   }
   return(1);
}

help_msg(str) {
   if (environment(this_object()) == this_player()) {
      if(id(str)) {
         write(
"This is Slider's Mortal Megaphone.  There are two ways to use it.  You can\n"+
"either use 'mega [msg]' to echo the message to all the mortals online,\n"+
"or use 'mega [msg] TO [operator] [level]' to echo a message to all mortals\n"+
"whose level matches [operator].  All of the standard comparative operators\n"+
"apply.  Spacing counts, and TO should be capitalized!  Here's some examples:\n"+
"             mega This is a test message TO < 10\n"+
"...will echo the message to all players less than level 10, while:\n"+
"             mega This is a test message TO >= 12\n"+
"...will echo the message to all players larger than or equal to level 12;\n"+
"             mega This is a test message TO == 3\n"+
"...will (you guessed it!) echo the message to all level 3 players.\n");
      return(1);
      }
   }
}
    
id(str) {
    return ((str== "megaphone") || (str=="phone") || (str == "mega"));
}

short() {
   return("Slider's Mortal Megaphone");
}

long() {
   write(
"This is Slider's Mortal Megaphone.  Type 'help mega' for help.\n");
   return(1);
}

get() {
   if(this_player()->query_level() <21) {
      write("You are not worthy of the privilege!\n");
      return(0);
   }
   return(1);
}

drop() {
   return(0);
}

