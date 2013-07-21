inherit "room/room";

init() {
    ::init();
    add_action("shout", "shout");
    add_action("tell", "tell");
    add_action("gossip", "gossip");
    add_action("emote", "emote");
    add_action("quit", "quit");
}

create() {
    set_short("Slider's Prison");

    set_long(
"Uh-oh....you've ended up in Slider's Prison!  Maybe if you're nice, he'll\n"+
"let you out!  Then again, maybe not!\n");
    set_light(1);
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


quit(str) {
    if(this_player()->query_level() <21) {
       write("You can check out any time you like....but you can never leave!\n");
       say(this_player()->query_name()+" tries to quit.\n");
       return(1);
    }
    return 0;
}


