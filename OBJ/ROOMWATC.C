inherit "/std/move";
/***************************************************************************
 * NAME:                                                                   
 *    roomwatc.c                                                           
 * DESCRIPTION:                                                            
 *    Slider's Room Watcher                                                
 * VERSION:                                                                
 *    1.0                                                                  
 * ENVIRONMENT:                                                            
 *    Virtual Realities -  LPMud 3.1.2-DR                                  
 * UPDATE HISTORY                                                          
 *    04/03/93  Slider  Initial version                                    
 *    04/04/93  Slider  Fixed to tell players with watcher receiver and to 
 *                      check if player's receiver is turned on            
 *    04/19/93  Slider  Added level info and logging                        
 ***************************************************************************/
string logname = "slider.roomwatch";

init() {

    int i, ulevel;
    object *players;
    object recobj;
    string uname, unameroom;

    /* Get the name and room name of the player who entered the watcher's
       environment */
    uname = this_player()->query_name();
    ulevel = this_player()->query_level();
    unameroom = environment(this_player())->short();

    log_file(logname, ctime() + "  " + uname + "("+ulevel+
       ") enters " + unameroom + ".\n");

    /* Get the list of active players */
    players = users();

    /* Check all the active players for a receiver */
    for(i = 0; i < sizeof(players); i++) {
      /* Get the receiver object */
       recobj = present("watcher receiver", players[i]);

       /* If we got it, then.... */
       if(recobj) {
           /* Check to see if this particular receiver is on */
           if(recobj->query_notify())
              /* It's on, so tell this player who's entered what room */
              tell_object(players[i], "Roomwatch says '"+uname+" ("+ulevel+")"+
                  " has just entered " +unameroom+"'.\n");
       }
    }
}

exit() {
   int i, ulevel;
   string uname, unameroom;

   /* Get the name and room name of the player who entered the watcher's
      environment */
   uname = this_player()->query_name();
   ulevel = this_player()->query_level();
   unameroom = environment(this_player())->short();

   log_file(logname,ctime()+" "+uname+ " exits " + unameroom + "\n");
}

id(str) {
    return ((str== "watcher") || (str=="room watcher"));
}

/* It's invisible and you can't pick it up */

get() {
    return 0;
}

short() {
    return(0);
}

set_logname(str) {
   if(!str) return(0);

   logname = str;
   return(1);
}

query_logname() {
   return(logname);
}

