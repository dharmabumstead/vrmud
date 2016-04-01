inherit "/std/move";
/***************************************************************************
 * NAME:                                                                   *
 *    portaprison.c                                                        *
 * DESCRIPTION:                                                            *
 *    Slider's Portable Prison                                             *
 * VERSION:                                                                *
 *    1.1                                                                  *
 * ENVIRONMENT:                                                            *
 *    End Of The Line - LPMud 3.1.2-DR                                     *
 * UPDATE HISTORY                                                          *
 *    04/02/93  Slider  Initial version                                    *
 *    04/03/93  Slider  Added login/logoff notification                    *
 *    04/27/93  Slider  Added notify toggle, owner name, and post killer   *
      02/09/00  Slider  Fixed say bug - lotta mudlib changes in 7 years!   *
 ***************************************************************************/
status notify = 1;
string owner_name = "slider";

init() {
    object owner;

    write("DEBUG: Init\n");
    add_action("shout", "shout");
    add_action("tell", "tell");
    add_action("gossip", "gossip");
    add_action("emote", "emote");
    add_action("gshout", "gshout");
    add_action("note", "note");
    add_action("say", "say");

    add_action("quit", "quit");

    if(owner_name) owner = find_living(owner_name);

    if(owner) {
        tell_object(owner, this_player()->query_name() +
           " has just logged in.\n");
    }
    return(1);
}



id(str) {
    return ((str== "portaprison") || (str=="prison"));
}

get() {
    return 1;
}

short() {
    return("a portaprison");
}

query_auto_load() {
    return 1;
}

drop() {
    if(this_player()->query_level() <21) {
       say(this_player()->query_name()+" tries to drop a portaprison!\n");
       write("Try as you might, you just can't drop it!\n");
       return 1;
    } else {
       return 0;
    }
}
note(str) {
    if(this_player()->query_level() <21) {
       write("Sorry, no bulletin board postings for prisoners!\n");
       say(this_player()->query_name()+" tries to post "+str+".\n");
       return 1;
    }
    return 0;
}

shout(str) {
    if(this_player()->query_level() <21) {
       write("Try as you might, you can't!  You're in PRISON, remember!\n");
       say(this_player()->query_name()+" tries to shout '"+str+"'.\n");
       return 1;
    }
    return 0;
}

tell(str) {
    if(this_player()->query_level() <21) {
       write("Sorry, no tell privileges for prisoners!\n");
       say(this_player()->query_name()+" tries to tell "+str+".\n");
       return 1;
    }
    return 0;
}

gossip(str) {
    if(this_player()->query_level() <21) {
       write("Ha!  That's probably what got you here in the first place. No "+
          "gossip\nprivileges for you!\n");
       say(this_player()->query_name()+" tries to gossip '"+str+"'.\n");
       return(1);
    }
    return 0;
}

emote(str) {
    if(this_player()->query_level() <21) {
       write("You can't emote!  You're in prison!\n");
       say(this_player()->query_name()+" tries to emote '"+str+"'.\n");
       return(1);
    }
    return 0;
}

gshout(str) {
    if(this_player()->query_level() <21) {
       write("Try as you might, you can't!  You're in PRISON, remember!\n");
       say(this_player()->query_name()+" tries to gshout '"+str+"'.\n");
       return 1;
    }
    return 0;
}

quit() {
    object owner;

    owner = find_living(owner_name);

    if(owner) {
        tell_object(owner, this_player()->query_name() +
           " has just left the game.\n");
    }

    return(0);
}

set_owner_notify(str) {
  if(str == "on") {
     notify = 1;
  } else {
     notify = 0;
  }
}

set_owner_name(str) {
   owner_name = str;
   return 1;
}

query_owner_name() {
   return owner_name;
}
