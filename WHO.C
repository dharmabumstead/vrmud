/* List the users -- Gudu 2/1/93 */
/* more flag defaulted to off - i get lots of complaints about the more in
   the who display - and it IS really annoying - MMtSM */
/* Last edited: 11/2/93 Gudu -- reversed meaning of l option */

int sort_by_level( object ob1, object ob2) {

    return (int) ob2->query_level() - (int) ob1->query_level();
}
 
int sort_by_name( object ob1, object ob2) {

    return strcmp((string) ob1->query_name(), (string) ob2->query_name());
}

int sort_by_alignment( object ob1, object ob2) {

    return (int) ob2->query_alignment() - (int) ob1->query_alignment();
}

int sort_by_gender( object ob1, object ob2) {

    return (int) ob2->query_gender() - (int) ob1->query_gender();
}

int sort_by_xp( object ob1, object ob2) {

    return (int) ob2->query_exp() - (int) ob1->query_exp();
}

int main( string str) {

    object *player;
    int	   i, j, ind1, ind2, inc, wiz_flag, more_flag, level;
    int    num_wizards, num_players;
    string sort_func, lev_str, idle_str, *output;
    mapping arg_map; 

    player = users();
    ind1   = 0;
    ind2   = sizeof( player);
    inc    = 1;

    output = allocate(ind2 + 2);
    j      = 0;

    /* Set a default */
    sort_func = "sort_by_level";

    arg_map = parse_args( (["?":0, "a":0, "e":0, "g":0, "l":0,
			    "m":0, "n":0, "r":0, "w":0]), str);
 
    if( !undefinedp( arg_map["opts"]["?"]))
    {
        write("who -[aeglmnrw]\n");
        return 1;
        }
    if( !undefinedp( arg_map["opts"]["a"]))
	sort_func = "sort_by_alignment";
    if( !undefinedp( arg_map["opts"]["e"]))
	sort_func = "sort_by_xp";
    if( !undefinedp( arg_map["opts"]["g"]))
	sort_func = "sort_by_gender";
    if( !undefinedp( arg_map["opts"]["l"]))
	sort_func = 0;
    if( !undefinedp( arg_map["opts"]["m"]))
	more_flag = 1;
    if( !undefinedp( arg_map["opts"]["n"]))
        sort_func = "sort_by_name";
    if( !undefinedp( arg_map["opts"]["r"])) {
	ind1 = sizeof( player) - 1;
	ind2 = inc = -1;
    }
    if( !undefinedp( arg_map["opts"]["w"]))
        wiz_flag = 1;

    if( sort_func)
	player = sort_array( player, sort_func, this_object());

    output[j++] = sprintf("Level %-67s Idle\n"
			  "%'-'78s",
			  "Name", "-");
		   
    for( i = ind1; i != ind2; i += inc) {
        
	level = (int) player[i]->query_level();

	if (player[i]->query_invis() && !wizardp(this_player()))
	    continue;

	if (wiz_flag && level < 20)
	    continue;

	switch( level) {
	
	//lev_str = lev_string(level);

	case 10000:
	    lev_str = "God";
	    num_wizards++;
	    break;
	case 1000..9999:
	    lev_str = "Dem";
	    num_wizards++;
	    break;
	case 501..999:
	    lev_str = "Eld";
	    num_wizards++;
	    break;
        case 300..500:
	    lev_str = "Lrd";
	    num_wizards++;
	    break;
	case 250..299:
	    lev_str = "Sen";
	    num_wizards++;
	    break;
	case 35..249:
	    lev_str = "Awi";
	    num_wizards++;
	    break;
	case 25..34:
	    lev_str = "Wiz";
	    num_wizards++;
	    break;
	case 21..24:
	    lev_str = "Imm";
	    num_wizards++;
	    break;
	case 20:
	    lev_str = "App";
	    num_wizards++;
	    break;
	default:
	    lev_str = level+"";
	    num_players++;
	    break;
	}

	if( query_idle( player[i]) > 59)
            idle_str = query_idle(player[i]) / 60 + "m";
        else
            idle_str = "";
	
	output[j++] = sprintf("(%3s) %-67.67s %-5s", lev_str, player[i]->short(), idle_str); 
    }

    output[j++] = sprintf("%'-'78s\n"
			  "Players: %d Wizards: %d",
			  "-", num_players, num_wizards);

    if ( more_flag)
        more( implode(output, "\n")+"\n");
    else
        write( implode(output, "\n")+"\n");
    return 1;
}
