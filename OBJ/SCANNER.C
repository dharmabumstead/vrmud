/***************************************************************************
 * NAME:                                                                   *
 *    scanner.c                                                            *
 * DESCRIPTION:                                                            *
 *    Slider's Inventory Scanner                                           *
 * VERSION:                                                                *
 *    1.0                                                                  *
 * ENVIRONMENT:                                                            *
 *    Virtual Realities -  LPMud 3.1.2-DR                                  *
 * UPDATE HISTORY                                                          *
 **04/06/1993   Slider  Initial version                                    *
      08/27/2002   Slider   Added inherit of std/object
 ***************************************************************************/
inherit "std/object";
status notflag;

init() {
    add_action("scan", "scan");
}

id(str) {
    return ((str=="scanner"));
}

get() {
    if(this_player()->query_level() < 21) {
        write("You burn your hands trying to pick it up!\n");
        say(this_player()->query_name() +
           " gets fried trying to pick up Slider's object scanner!\n");
        return 0;
    }

    return 1;
}

short() {
    return("an inventory scanner");
}

long() {
    write(
"A simple inventory scanner.....use 'scan <itemname>' to look for an item\n"+
"in a players inventory.\n");    

   return(0);
}

scan(str) {
    int i, items;
    object *players;
    object recobj;

    if(!str) {
        return(0);
    }

    /* Get the list of active players */
    players = users();

    write("--------------------------------------------------------------\n");
    write("Looking for matches for '" + str + "'....\n\n");

    /* Check all the active players for the item */
    for(i = 0; i < sizeof(players); i++) {
      
       recobj = present(str, players[i]);
       
       /* If we got it, then.... */
       if(recobj) {
          write("  " + capitalize(players[i]->query_real_name()) + 
             " (level " + players[i]->query_level() + ") at " + 
             environment(players[i])->short()+ "\n"+
             "   -> " + recobj->short()+".\n");
          items++;
       }
       
    }

    write("--------------------------------------------------------------\n");

    if(items)
       write("Found " + items + " matches.\n");
    else
       write("No matching items found.\n");

    write("--------------------------------------------------------------\n");

    return 1;
}

