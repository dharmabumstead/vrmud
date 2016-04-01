inherit "/std/move";
string short_desc;
/* 
* Bulletin board object by Lleldorin for Virtual Realities MUD.
* 
*/


/*
*  inheritable bull_board object by Lleldorin @ various muds.
*  converted from standard bulletin board object.
*  please don't copy without permission.
*
*/

/* edited 8/31/93 by Gudu & Aqualung -- added trash command */
/* edited 9/6/93 by Gudu -- clone /std/more instead of inherit */

#define GNOME_TIME 900      /* time for mr. gnome to reorganise */
int MINIMUM_LEVEL;         /* minimum level before a user can post */
int MAX_MESSAGES;          /* max messages on the board */
static string SAVED_OBJECT_NAME;  /* save file name */
int MIN_REMOVE_LEVEL;      /* min level before u can remove a note */
int DO_GNOME;           /* whether or not to call the gnome dude */

string messages, new_hd, new_body;
int num_messages;
object who;
int current;

id(str) {
   return str == "bulletin board" || str == "board";
}

long() {
   write("You can set up new notes with the command 'note <heading>'.\n");
   write("Read a note with 'read <num>', and remove an old note with\n");
   write("'remove <num>'.\n");
   if (num_messages == 0) {
      write("It is empty.\n");
      return;
   }
   write("The bulletin board contains " + num_messages);
   if (num_messages == 1)
      write(" note:\n\n");
   else
      write(" notes:\n\n");
   say(this_player()->query_name()+" studies the bulletin board.\n");
   headers();
}

set_short(str){ 
short_desc=str;
return 1;
} 

short() {

return "A Bulletin Board";
}

create() {
   MINIMUM_LEVEL=1;
   MAX_MESSAGES=30;
   MIN_REMOVE_LEVEL=1;
   DO_GNOME=0;
   messages="";
short_desc="A bulletin board";
/*
   call_out("gnome",GNOME_TIME);
*/
}

get() {
   write("It is secured to the ground.\n");
   return 0;
}

init() {
   add_action("new","note");
   add_action("read","read");
   add_action("remove","remove");
   add_action("trash","trash");
   add_action("next","next");
}
next() {
   current++;
   if (current > num_messages) {
      current --;
      write("At end of messages.\n");
      return 1;
   }
   write("Reading note: "+current+"\n");
   read (current);
   return 1;
}

headers() {
   string hd, body, rest;
   int i, tmp;
   
   i = 1;
   rest = messages;
   while(rest != 0 && rest != "") {
      tmp = sscanf(rest, "%s:\n**\n%s\n**\n%s", hd, body, rest);
      if (tmp != 2 && tmp != 3) {
         write("Corrupt.\n");
         return;
         }
      write(i + ":\t" + hd + "\n");
      i += 1;
   }
}

new(hd) {
   if (!hd)
      return 0;
   if (who && environment(who) == environment(this_object())) {
      write(who->query_name()+" is busy writing.\n");
      return 1;
   }
   if (this_player()->query_level() < MINIMUM_LEVEL) {
      write("You must be at least level "+MINIMUM_LEVEL+".\n");
      return 1;
   }
   if (num_messages == MAX_MESSAGES) {
      write("You have to wait, theres no room!\n");
      return 1;
   }
   if (strlen(hd) > 50) {
      write("Too long header to fit the paper.\n");
      return 1;
   }
   who = this_player();
   new_hd = hd;
   input_to("get_body");
   write("Give message, and terminate with '**' (abort with '~q').\n");
   write("]");
   new_body = "";
   return 1;
}

get_body(str) {
   if (str == "**") {
      new_hd = new_hd + "(" + capitalize(this_player()->query_real_name()) +
      ", " + extract(ctime(time()), 4, 9) + ")";
      messages = messages + new_hd + ":\n**\n" + new_body + "\n**\n";
      num_messages += 1;
      new_body = 0;
      new_hd = 0;
      if(save_object(SAVED_OBJECT_NAME)) {
       write("Saved.\n");
      }
     else {
       write("Save _FAILED_ - should never happen.\n");
      }
      write("Ok.\n");
      who = 0;
      return;
   }
   if (str=="~q") {
      write("Aborted.\n");
      who=0;
      return;
   }
   new_body = new_body + str + "\n";
   write("]");
   input_to("get_body");
}

read(str) {
   
   string hd, body, rest;
   int i, tmp;
   
   if (intp(str))
      i = str;
   else if (str==0 || (sscanf(str,"%d",i) != 1 && sscanf(str,"note %d",i) != 1))
      return 0;
   if (i < 1 || i > num_messages) {
      write("Not that number of messages.\n");
      return 1;
   }
   rest = messages;
   current = i;
   while(rest != 0 && rest != "") {
      i -= 1;
      tmp = sscanf(rest, "%s:\n**\n%s\n**\n%s", hd, body, rest);
      if (tmp != 2 && tmp != 3) {
         write("Corrupt.\n");
         return;
         }
      if (i == 0) {
         say(this_player()->query_name()+" reads a note titled '"+hd+"'.\n");
         write("The note is titled '" + hd + "':\n\n");
         this_player()->more(body);
         return 1;
         }
   }
   /* should never get here */
}

remove(str) {
   string hd, body, rest;
   int i, tmp;
   
   if (str==0 || (sscanf(str,"%d", i) !=1 && sscanf(str,"note %d", i) != 1))
      return 0;
   if (this_player()->query_level() < MIN_REMOVE_LEVEL) {
      write("You cannot remove the message.\n");
      return 1;
   }
   if (i < 1 || i > num_messages) {
      write("Not that number of messages.\n");
      return 1;
   }
   rest = messages;
   messages = "";
   while(rest != 0 && rest != "") {
      i -= 1;
      tmp=sscanf(rest, "%s:\n**\n%s\n**\n%s", hd, body, rest);
      if (tmp != 2 && tmp != 3) {
         write("Corrupt.\n");
         return;
         }
      if (i == 0) {
         string tmp1,tmp2;
         if ((sscanf(hd,"%s("+capitalize(this_player()->query_real_name())+
                     ",%s",tmp1,tmp2)!=2)
            && (this_player()->query_level()<21)) {
            write("It is not your note to remove!\n");
            messages=messages+hd+":\n**\n"+body+"\n**\n"+rest;
          }
         else {
            say(this_player()->query_name()+" removed a note titled '"+
               hd + "'.\n");
            write("Ok.\n");
            num_messages -= 1;
            messages = messages + rest;
            save_object(SAVED_OBJECT_NAME);
          }
         return 1;
         }
      messages = messages + hd + ":\n**\n" + body + "\n**\n";
   }
   /* should not happen */
}

set_save_name(arg) {
   if (!arg) {
      write("Illegal save file name!\n");
      return 1;
   }
   SAVED_OBJECT_NAME=arg;
   restore_object(SAVED_OBJECT_NAME);
   return 1;
}

set_min_level(arg) {
   MINIMUM_LEVEL=arg;
}

set_max_msgs(arg) {
   MAX_MESSAGES=arg;
}

set_min_remove_level(arg) {
   MIN_REMOVE_LEVEL=arg;
}

set_gnome(arg) {
   DO_GNOME=arg;
}

void gnome() {
   
   if (!DO_GNOME) return;
   tell_room(environment(),
      "A gnome runs in, and begins to straighten the notes on the board.\n");
   move_object(clone_object("/obj/gnome"),environment());
   call_out("gnome",GNOME_TIME);
}

/* Send a stupid message to its proper home -- Gudu & Aqualung */
trash( str) {
   
   string hd, body, rest;
   int i, tmp;
   
   /* Why is messages not an array Llel? */
   
   if (str==0 || (sscanf(str,"%d",i) != 1 && sscanf(str,"note %d",i) != 1))
      return 0;
   if (i < 1 || i > num_messages) {
      write("Not that number of messages.\n");
      return 1;
   }
   rest = messages;
   while(rest != 0 && rest != "") {
      i -= 1;
      tmp = sscanf(rest, "%s:\n**\n%s\n**\n%s", hd, body, rest);
      if (tmp != 2 && tmp != 3) {
         write("Corrupt.\n");
         return;
         }
      if (i == 0) {
         "/room/newroom/obj/stupid_shit_board"->add_trash( hd, body);
         remove( str);
         return 1;
         }
   }
   /* should never get here */
   
}

