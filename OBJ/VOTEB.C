inherit "/std/move";
/***************************************************************************
 * NAME:
 *    voteb.c
 * DESCRIPTION:
 *    Slider's Voting Booth Tester
 * VERSION:
 *    0.4
 * ENVIRONMENT:
 *    Virtual Realities - LPMud 3.1.2-DR
 * UPDATE HISTORY
 *    11/19/94  Slider  Initial version
 *    10/22/95  Slider  Added save/load object
 ***************************************************************************/
#include "/players/slider/include/slider.h"
#define SAVE_NAME "/players/slider/logs/voteb.sav"

object owner;
mapping issues, choices, votes, issue_keys;
int SEQ_KEY;

string new_issue_title, new_issue_text, temp_text;

id(str) {
   return ((str== "booth") || (str=="tester") || (str == "voting"));
}

string short_desc;

short() { return short_desc; }

/************************************************************/
long() {
  write("This is Slider's test voting booth v0.4. It's still being built.\n");
  
  write("Use create <issue>, remove <issue>, view <issuenum>, or list.\n");

  return 1;
}

set_short(str) {
   short_desc = str;
}

/************************************************************/
create()  {
   issues = ([]);
   choices = ([]);
   votes = ([]);
   issue_keys = ([]);
   set_short("a voting booth");
   restore_object(SAVE_NAME);
}

/************************************************************/
get() { return 0; }

/************************************************************/
drop() { return 0; }

/************************************************************/
init() {
   /* Add our commands */
   add_action("create_issue", "create");
   add_action("remove_issue", "remove");
   add_action("list_issues", "list");
   add_action("view_issue", "view");
}

create_issue(str) {
   if(!str) {
      write("Create *what* issue?\n");
      return(1);
   }
   
   temp_text = "";
   new_issue_text = "";
   new_issue_title = str;
   
   input_to("get_issue_text");
   write("Enter a description of your message. Use a . by itself to end.\n");
   new_issue_text = "";
   save_object(SAVE_NAME);
   return(1);
}

get_issue_text(str) {
   if(str == ".") {
      new_issue_text = temp_text;
      issues[new_issue_title] = new_issue_text;
      issue_keys[(get_seq_key())] = new_issue_title;
      write("Issue entered.\n");
      return;
   }

   temp_text = temp_text + str + "\n";
   input_to("get_issue_text");
}

remove_issue(str) {
   if (!str) {
      write("Remove which issue?\n");
      return(1);
   }
   
   if(undefinedp(issue_keys[atoi(str)])) {
      write("That issue doesn't exist!\n");
      return(1);
   }
   
   
   map_delete(issues, (issue_keys[atoi(str)]));
   map_delete(issue_keys, atoi(str));

   write("Issue " + str + " deleted.\n");
   /* put code in here for security, referential integrity, etc. */
   save_object(SAVE_NAME);
   return(1);
}

list_issues() {
   mixed *titles;
   int i;

   titles = keys(issue_keys);

   for(i=0;i<sizeof(titles);i++)
      write(titles[i] + ": " + issue_keys[titles[i]] + "\n");

   return(1);
}

view_issue(str) {
   if (!str) {
      write("View which issue?\n");
      return(1);
   }
   
   if(undefinedp(issue_keys[atoi(str)])) {
      write("That issue doesn't exist!\n");
      return(1);
   }

   write(str + ": " + issue_keys[atoi(str)] + "\n");
   write(issues[issue_keys[atoi(str)]] + "\n");

   return(1);
}
   
int get_seq_key() {
   SEQ_KEY = SEQ_KEY + 1;
   return(SEQ_KEY);
}
