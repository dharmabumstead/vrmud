inherit "/std/move";
/***************************************************************************
 * NAME:                                                                   *
 *    watchrec.c                                                           *
 * DESCRIPTION:                                                            *
 *    Slider's Room Watcher Receiver                                       *
 * VERSION:                                                                *
 *    1.0                                                                  *
 * ENVIRONMENT:                                                            *
 *    Virtual Realities -  LPMud 3.1.2-DR                                  *
 * UPDATE HISTORY                                                          *
 *    04/03/93  Slider  Initial version                                    *
 *    04/04/93  Slider  Add long descript, query_notify function, etc      *
 * IDEAS                                                                   *
 *    04/04/93  Slider  Have it return a list of all the room watchers on  *
 *                      the mud (and maybe even remotely dest 'em!)        *
 ***************************************************************************/
status notflag;

init() {
    add_action("turn", "turn");
}

id(str) {
    return ((str=="receiver") || (str=="watcher receiver"));
}

get() {
    return 1;
}

short() {
    return("a room watcher receiver");
}

long() {
    write(
"A room watcher receiver.  Use this to receive messages from any room watchers\n"+
"that exist on the mud.  Use 'turn receiver [on|off]' to turn it on or off!\n");

    if(notflag) {
       write("The room watcher receiver is currently 'on'\n");
    } else {
       write("The room watcher receiver is currently 'off'\n");
    }
   return(0);
}

turn(str) {
    string idstr, toggle;

    if(!str) {
        return(0);
    }

    sscanf(str, "%s %s", idstr, toggle);

    if(id(idstr)) {
        if(toggle == "on") {
           write("The room watcher receiver is now 'on'\n");
           notflag = 1;
        } else {
           write("The room watcher receiver is now 'off'\n");
           notflag = 0;
        }
        return 1;
    }
    return 0;
}

query_notify() {
    /* This is called from the room watcher to see if we need to notify
       this receiver */
    return notflag;
}
