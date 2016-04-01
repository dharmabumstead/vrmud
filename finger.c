/* Finger daemon by Lleldorin */
/* most of info code moved to /daemons/fingerd */
/* revamped to use query_wizard_level() */

/* support for -m (more) option added by Qwag 21/12/01 */
 
/*  Revamped display and added IP name (for admins) - Slider 8/27/2002  */

#include <daemons.h>

#define TP this_player()

main(str){
    string arg,rest;
    int more;

    if(!str){
	finger_all();
	return 1;
    }
    if (sscanf(str,"-m %s",arg)==1) {
        more=1;
        str=arg;
    }
    if (sscanf(str,"%s %s",arg,rest) >=1)
	str=arg;
if(str=="roy") { write("Don't be Roy.\n"); return 1; }
    finger_ob(str,more);
    return 1;
}                                                              

finger_all() {
    object *usr;
    int i;
    int idle;
    string line;
    int wizlevel;
    int iswizard;

    iswizard=wizardp(TP);
   if(iswizard)
 write("LOGIN         IDLE  SINCE                 LEVEL   FROM                         \n");
    else
      write("LOGIN         IDLE  SINCE                 LEVEL\n");
write("---------------------------------------------------------------------------------\n");
    usr=users();
    for(i=0;i<sizeof(usr);i++) {
	line="";
	if (usr[i]->query_invis() && !iswizard)
	    continue;
	if (!environment(usr[i]))
	    continue;
	line+=(capitalize(pad(usr[i]->query_real_name(),13)));    
	line+=(" ");

	line+=(" ");
	idle=query_idle(usr[i])/60;
	if (idle)
	    line+=(pad(idle+" ",-4));
	else
	    line+=(pad("",4));
	line+=(" ");
	line+=(pad(extract(usr[i]->query_last_login(),4,23),21));
	line+=(" ");
	if (wizardp(usr[i]))
            line+=pad(show_level(query_wizard_level(usr[i])),8);
	else
	    line+=pad(usr[i]->query_level(),8);
        if(iswizard)
           line+=pad(query_ip_name(usr[i]), 40);
	write(line+"\n");
    }
}

show_level(level) {                                        
    if (level > 1001)
	return " God ";
    if (level > 999)
	return " D-God";
    if (level > 500)
	return "Elder";
    if (level==303)
	return " God ";
    if (level > 299)
	return "Lord";
    if (level > 200)
	return "Senr.";
    if (level > 20)
	return " Wiz ";
    if (level==20)
	return "Appr.";
    else
	return pad(level,-4);
}

varargs finger_ob(str,more) {
    if (BANISH_D->name_banned(str)) {        
	write("That player has been banished!\n");
	return;
    }
    // uhh.. why are we logging this?
    /*
       log_file("FIN", sprintf("%-15s %-15s %-30s\n",
		TP->query_real_name(),str,ctime()));
    */
    if ("/daemons/fingerd"->finger_ob(str,more))
	return;
    write("No such player!\n");
}                        

