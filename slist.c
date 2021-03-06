/***************************************************************************
 * NAME:                                                                   
 *    slist.c                                                              
 * DESCRIPTION:                                                            
 *    Slider's Player Lister Deluxe                                        
 * VERSION:                                                                
 *    1.1                                                                  
 * ENVIRONMENT:                                                            
 *    Virtual Realities -  LPMud 3.1.2-DR                                  
 * UPDATE HISTORY                                                          
 *    04/06/1993  Slider  Initial version                                    
 *    08/14/1993  Slider  Fixed bug in sort routine                          
 *                        Now sorts by name within levels                    
 *    12/07/1994  Slider  Fixed sort routine
      08/27/2002  Slider  Fixed some minor formatting bugs
 ***************************************************************************/
status notflag;

main(args) {

    int i, items, a;
    object *players;
    object recobj;
    string str, str2;


    say(capitalize(this_player()->query_name()) + " consults an slister.\n");

    /* Get the list of active players */
    players = sort_array(users(),"sort_by_level",this_object());
    write(
"==============================================================================\n"+
"NAME          LEV  AGE  S    EXPER  ST IN DX CN   HP/MAX   SP/MAX  MONEY FLAGS
"+

"------------------------------------------------------------------------------\n");
    /* Check all the active players for the item */
    for(i = 0; i < sizeof(players); i++) {
        str = players[i]->query_real_name();
        if (!str)
            str = "Logon";
        str = capitalize(str);
        if (players[i]->short()[0] == '#')
            str = "("+str+")";
        if (players[i]->query_ghost())
            str = ">"+str+"<";

        write(pad(str,13)+pad(players[i]->query_level(),-4));

        a = players[i]->query_age();

        if (a/43200 > 0)
            str = (a/43200)+"D";
        else if (a/1800 > 0)
            str = (a/1800)+"h";
        else
            str = (a/30)+"m";

        str2 = capitalize(players[i]->query_gender_string());

        write("  "+pad(str,-3)+"  "+pad(str2,1)+"  ");

        write(pad(players[i]->query_exp(), -7) + "  ");

        write(pad(players[i]->query_str(), -2) + " "+
              pad(players[i]->query_int(), -2) + " "+
              pad(players[i]->query_dex(), -2) + " "+
              pad(players[i]->query_con(), -2) + "  ");

        write(pad(players[i]->query_hp() + "/" + players[i]->query_max_hp(),-7))
;
        write("  ");
        write(pad(players[i]->query_sp() + "/" + players[i]->query_max_sp(),-7))
;
        write("  ");
        write(pad(players[i]->query_money(), -5));

        write("  ");
        if(players[i]->query_edit())
           write("E");
        else write(" ");

        if(players[i]->query_stuffed())
           write("F");
        else write(" ");

        if(players[i]->query_frog())
           write("G");
        else write(" ");

        if(players[i]->query_intoxination())
           write("I");
        else write(" ");

        if(players[i]->query_soaked())
           write("S");
         else write(" ");

        write("\n");
    }

write (
"------------------------------------------------------------------------------\n"+
"FLAGS:  B  Blind         F  Stuffed   S  Soaked  | SEX:  M  Male\n"+
"        E  Editing       G  Frog      I  Drunk   |       F  Female\n"+
"        () Invisible    ><  Ghost                |       I  It\n"+
"==============================================================================
\n");

    return 1;
}

sort_by_level(object ob1,object ob2) {
    int ob1lvl, ob2lvl;

    ob1lvl = ob1->query_level();
    ob2lvl = ob2->query_level();

    /* sort by real name if same level */
    if (ob1lvl == ob2lvl)
    {
      return strcmp((string) ob1->query_name(), (string) ob2->query_name());
    } 
    return (int) ob2->query_level() - (int) ob1->query_level();
}        
