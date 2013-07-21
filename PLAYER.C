#include <log.h>
#include <living.h>
#include <security.h>
#include <uid.h>
#include <channel_d.h>
#include <config.h>
#include <quests.h>
#include <daemons.h>


#define WIZ            1    
#define ARCH           0
#define LOCKOUT_LEVEL  0
#define MAX_SCAR      10

inherit "/std/light";
inherit "std/player/autoload";
inherit "std/player/more";
inherit "obj/living";
inherit "std/player/channel";

int 	idnum, stats_is_updated;/* Object number of player, uptodate stats */
int 	headache, intoxicated, max_headache, stuffed, soaked;
int 	*edit_save_channels; /* Gudu 11/92 */
int 	scar;
int 	brief;
int 	tot_value;/* Saved values of this player. */
static 	int blind;/* Blind add Gudu */
static 	int debug_cmd_hook_flag;
static 	int time_to_save;/* Time to autosave. */

object 	other_copy, plyr;/* dumb hacks */
static 	object last_ob, *ob_list;
static 	object myself;/* Ourselfs. */

string called_from_ip;/* IP number was used last time */
string description;/* Player's own description cutesy Rob U*/
string edalign, edtitle;/* title and alignment for when editing */
string guild_string;/* guild string */
string last_login;/* last login time/date */
int last_login_time;
string mailaddr;/* Email address of player */
string msgclone, msgdest;
string pretitle, title, al_title;
static string real_name;/* for finger */
string quests;/* A list of all quests */
string lquests;  /* level quests */
string current_path;/* Current directory */
static string it;/* Last thing referenced. */
static string last_file;/* Last file edited */
static string saved_where;/* Temp... */
static int kill_flag;
int edit_on;
int no_remote_soul;
int is_invis;
mapping env_vars;
object shell_ob;
int version;

/* Prototypes */

static int get_new_player_object(string arg);
void get_backup_shell_ob();
void show_scar();
save_me(arg);
int check_access();

void create() {
  myself = this_object();
  seteuid(0);
}

int set_name(string str) {
  if( geteuid( previous_object()) != ROOT_UID)
    return 0;
  name = str;
  cap_name = capitalize( name);
  return 1;
}

/*
 *  You can do updates to players here without cluttering
 *  up the setup() function. In principle this could be
 *  daemonized. -- Artagel 1/94
 */

void consistency_check() {
  if(!version) 
    version = 0;
  switch(version) {
  case 0:
    if( undefinedp( env_vars["SHELL"]))
      env_vars["SHELL"] = STD_SHELL;
    else if( env_vars["SHELL"] == "/std/ssh")
      env_vars["SHELL"] = STD_SHELL;
  default:
    version = 1;
  }
}

void setup() {
   int wiz_level;
   string err;
   
   seteuid( getuid());

   restore_object( PDATA_DIR+"/"+getuid());

// consistency_check(); This was barfing and I don't know what its point is.
// Gudu 1/13/93

   enable_commands();
   set_living_name( name);
   set_heart_beat(1);

   add_action("cmd_hook", "", 1);
   add_action("shell", "shell");

	new("/obj/soul")->move( myself);

   wiz_level = query_wizard_level( getuid());
   if( wiz_level && level != wiz_level)
      level = wiz_level;

   autoload::load_auto_obj();

   if( !mapp( channel_data)) {
      channel::add_standard_channels();
      if( wizardp( myself))
         channel::add_wizard_channels();
   }
   channel::remove_illegal_channels();

   if( !current_path)
      current_path = "/man";

   if( !mapp( env_vars))
      env_vars = allocate_mapping(10);
   if( undefinedp( env_vars["SHELL"]))
       env_vars["SHELL"] = STD_SHELL;

   err = catch( ( shell_ob = new( env_vars["SHELL"]))->move( myself));
   if( err) {
      printf("Error loading shell object %s: %s\n", env_vars["SHELL"], err);
      get_backup_shell_ob();
   }
}

int _enable_wizard() {
   if( geteuid( previous_object()) != ROOT_UID)
      return 0;
   enable_wizard();
}

int _disable_wizard() {
   if( geteuid( previous_object()) != ROOT_UID)
      return 0;
   disable_wizard();
}

string short() {
   string *str, tmpalign, tmptitle;
   
   str = allocate(10);
   
   if (is_invis)
      str[0] = "#";
   else
      str[0] = "";

   if (ghost)
      return str[0] + "ghost of " + capitalize(name);
   else if (frog) 
      return str[0] + capitalize(name) + " the frog";

   /* modified by Lleldorin - Heimdall's version thrown out the window. ;) */
   /* optomised by Gadget - Lleldorins version probly not recognizable anymore 
                      its a whopping 4.5% faster too - whoopie */
   
    if (pretitle != "") {
	str[1] = pretitle;
	str[2] = " ";
    }

    str[3] = capitalize(name);

    if (edit_on) {
	tmptitle = edtitle;
	tmpalign = edalign;
    } else {
	tmptitle = title;
	tmpalign = al_title;
    }
   
    if (tmptitle && tmptitle != "") {
	str[4] = " ";
	str[5] = tmptitle;
    }
      
    if (tmpalign && tmpalign != "") {
	str[6] = " (";
	str[7] = tmpalign;
	str[8] = ")";
    }

    if (!interactive(this_object()))
	str[9] = " (Netdead)";
	
    return implode(str,"");
}

query_gender_string() {
  if(query_pronoun() == "he") return "male";
  if(query_pronoun() == "she") return "female";
  return "it";
}

int filter_null_strings(mixed arg) {
   return stringp(arg);
}

string extra_long() {
   mixed *list;

   list = all_inventory(this_object())->extra_look();
   list = filter_array(list, "filter_null_strings", this_object());
   if(sizeof(list))
      return implode(list, "\n") + "\n";
   return "";
}

void long() {
    string cap_pronoun;

    cap_pronoun = capitalize(query_pronoun());
    write(short() + ".\n");
    if((description))
         write(description);
    write(extra_long());
    if (ghost || frog)
	return;
    show_scar();
    if (hit_point < max_hp/10) {
	write(cap_pronoun + " is in very bad shape.\n");
	return;
    }
    if (hit_point < max_hp/5) {
	write(cap_pronoun + " is in bad shape.\n");
	return;
    }
    if (hit_point < max_hp/2) {
	write(cap_pronoun + " is not in a good shape.\n");
	return;
    }
    if (hit_point < max_hp - 20) {
	write(cap_pronoun + " is slightly hurt.\n");
	return;
    }
    write(cap_pronoun + " is in good shape.\n");
}

/* Identify ourself. */
 id( str,  lvl) {

    if (str == name)			return 1;
    if (str =="PLAYER") 		return 1;
    if (ghost)				return str == "ghost of " + name;

    return 0;
}

int set_level( int lev) {

    if( ( lev >= APPRENTICE || level >= APPRENTICE) && 
       geteuid( previous_object()) != ROOT_UID)
	return 0;

    level = lev;

    return 1;
}


set_title(t) {

  if (this_player()->query_real_name()!=name) {
    if (this_player()->query_real_name()) {
      log_file("TITLE", ctime(time())+" "+this_player()->query_real_name()+" changed "+name+"'s title.\n");
    } else {
      log_file("TITLE", ctime(time())+" "+name+"'s title has been changed by an object:\n");
      log_file("TITLE", "   Prev: "+file_name(previous_object())+"\n");
      if (environment(previous_object())) {
	log_file("TITLE", "   Env : "+file_name(environment(previous_object()))+"\n");
	if (environment(previous_object())->query_real_name()) {
	  log_file("TITLE", "  Name: "+environment(previous_object())->query_real_name()+"\n");
	}
      }
    }
    log_file("TITLE", "   New Title: "+t+"\n");
  }

  if( !t)
      title = "";
  else
      title = t;

  return 1;
}

set_pretitle( str) {

    if( !str) 
	pretitle = "";
    else
	pretitle = str;

    return 1;
}

set_align( str) {

    if( !str) 
	al_title = "";
    else
	al_title=str;

    return 1;
}

static quit() { command("quit"); }

static add_intox(int i) {
    if (monitor) monitor->draw_player_state();
    intoxicated += i;
    intoxicated = max(intoxicated,0);
}

static add_stuff(int i) {
    if (monitor) monitor->draw_player_state();
    stuffed += i;
    stuffed = max(stuffed,0);
}

static add_soak(int i) {
    if (monitor) monitor->draw_player_state();
    soaked += i;
    soaked = max(soaked,0);
}

static void heart_beat() {
int i, size, no_queue;

    // Picard 12/9/94
    no_queue=(env_vars["NO_CHANNEL_QUEUE"]=="1") ||
    ((!in_edit() || env_vars["NO_CHANNEL_QUEUE"]=="edit") &&
    (!in_input() || env_vars["NO_CHANNEL_QUEUE"]=="input"));

    // Gudu 1/30/94
    if( channel_queue && no_queue) {
	for( size = sizeof( channel_queue); i < size; i++)
	    receive( channel_queue[i]);
	channel_queue = 0;
    }

    if (ghost) return;
    if (hit_point > max_hp)
	hit_point = max_hp; /* should be unnecessary. */

    if (spell_points > max_sp)
	spell_points=max_sp;
  
    hunting_time--;  /* test to fix 15 room bug - Llel */
    dead = ghost;
  
    if (++age > time_to_save) {
	if (level < 20) {
	    if (!brief)
		write("Autosave.\n");
	    save_me(1);
	}
	time_to_save = age + 500;
    }

    kill_flag = 0;  /* fix multi attack bug - Lleldorin */
    if (!query_ip_number(this_object())) {
	say ("Link death comes in and happily cuts the link for "+cap_name+".\n");
	message("info", sprintf("Info: %|11s [%|4d] has gone link dead.\n",cap_name, level), users());
	set_heart_beat(0);
	call_out("quit",1800);
	return;
    }
    if (query_idle(this_object()) >= 1800 && level < APPRENTICE) {
	tell_object(myself,"Your character implodes from sheer boredom.\n");
	say(cap_name+ " implodes from sheer boredom.\n");
	quit();
	return;
    }
    if (intoxicated) {
	switch(random(280)) {
	    case 0:
	        say(cap_name + " hiccups.\n");
	        write("You hiccup.\n");
	        break;
	    case 1:
	        say(cap_name + " seems to fall, but takes a step and recovers.\n");
	        write("You stumble.\n");
	        break;
	    case 3:
	        write("You feel drunk.\n");
	        say(cap_name + " looks drunk.\n");
	        break;
	    case 5:
	        say(cap_name + " burps.\n");
	        write("You burp.\n");
	        break;
 	}
    }

    /* No obvious effects of being stuffed or soaked */

    if (hit_point < max_hp || spell_points < max_sp || intoxicated || headache) {
	if (--time_to_heal < 0) {
	    if (headache)
		if (!(--headache))
		    tell_object(myself, "You no longer have a headache.\n");
		if (hit_point < max_hp)
		    add_hp( (intoxicated) ? 4 : 1 );               
		if (spell_points < max_sp)
		    add_sp( (intoxicated) ? 4 : 1 );
                if (intoxicated) {
                    add_intox(-1);
                    if (intoxicated == 0) {
			headache = max_headache;
			max_headache = 0;
			tell_object(myself, "You suddenly without reason get a bad headache.\n");
					(hit_point < 3) ? add_hp(-hit_point) : add_hp(-3);
		    }
                }
      		time_to_heal = INTERVAL_BETWEEN_HEALING;
	}
    }

    if (stuffed)
	add_stuff(-1);

    if (soaked)
	add_soak(-1);

    if (attacker_ob)
	attack();
    
    if (attacker_ob && whimpy && hit_point < max_hp / 5)
	run_away();
}

/*
 * Update our aligment.
 */

add_alignment(int a) {

    alignment = alignment*9/10 + a;
    if (level > 20)
	return;

    if (alignment > KILL_NEUTRAL_ALIGNMENT * 100) {
	al_title = "saintly";
	return;
    }
    if (alignment > KILL_NEUTRAL_ALIGNMENT * 20) {
	al_title = "good";
	return;
    }
    if (alignment > KILL_NEUTRAL_ALIGNMENT * 4) {
	al_title = "nice";
	return;
    }
    if (alignment > - KILL_NEUTRAL_ALIGNMENT * 4) {
	al_title = "neutral";
	return;
    }
    if (alignment > - KILL_NEUTRAL_ALIGNMENT * 20) {
	al_title = "nasty";
	return;
    }
    if (alignment > - KILL_NEUTRAL_ALIGNMENT * 100) {
	al_title = "evil";
	return;
    }
    al_title = "demonic";
}

test_dark() {

    if( set_light(0) <= 0 || blind)   /* Blind stuff Gudu 12/92 */
	return 1;

    return 0;
}

/* Added by Henry, 10 October 1992 */
nomask query_file_name(str) {

    if (!str) return last_file;

    last_file = str;
    return 1;
}

toggle_whimpy() {

    whimpy = !whimpy;
    if (whimpy)
	write("Wimpy mode.\n");
    else
	write("Brave mode.\n");
    return 1;
}

toggle_brief() {

    brief = !brief;
    if (brief)
	write("Brief mode.\n");
    else
	write("Verbose mode.\n");
    return 1;
}

int add_exp( int exp) {

    object tp1,party_ob;
    string dummy;
    
    tp1 = this_player(1);
    if( exp > 20000 || ( tp1 && tp1 != this_object() && level < APPRENTICE))
	log_file("EXPERIENCE", sprintf("%s given %d by %s %s\n",
				       getuid(), exp, getuid( tp1), ctime()));
    if ((party_ob=present("party object",this_object())) &&
	sscanf(file_name(party_ob),"/players/picard/party#%s",dummy) &&
	(exp>0) &&
	!sscanf(file_name(previous_object()),"/players/picard/party#%s",dummy))
    {
       party_ob->add_exp(exp);
    }
    else add_experience( exp);
}

add_intoxination(int i) {

    if(i < 0) {
	if (-i > intoxicated / 10)
	    i = -intoxicated / 10;
    }
    add_intox(i);
}

add_stuffed(int i) {

    if(i < 0) {
	if (-i > stuffed / 10)
	    i = -stuffed / 10;
    }
    add_stuff(i);
}

add_soaked(int i) {

    if(i < 0) {
	if (-i > soaked / 10)
	    i = -soaked / 10;
    }
    add_soak(i);
}

second_life() {

/*   object death_mark;  - * Fordster */

    if( level < 20) {
	make_scar();
	if (level > 1)
	    level = level - 1;
	if (Str > 1)
	    set_str(Str-1);
	if (Con > 1)
	    set_con(Con-1);
	if (Dex > 1)
	    set_dex(Dex-1);
	if (Int > 1)
	    set_int(Int-1);
    }
    ghost = 1;
    msgin = "drifts around";
    msgout = "blows";
    headache = 0;
    add_intox(-intoxicated);
    add_stuff(-stuffed);
    add_soak(-soaked);
    hunter = 0;
    hunted = 0;

    if (attacker_ob)
	log_file("KILLS", ctime()+" "+name + "(" + level + ")" + " killed by " +
		 attacker_ob->short() + "(" +
		 attacker_ob->query_level() + "), creator: " +
		 creator(attacker_ob) + "\n");

    attacker_ob = 0;
    alt_attacker_ob = 0;
    tell_object(myself, "\nYou die.\nYou have a strange feeling.\n" +
		"You can see your own dead body from above.\n\n");


/*
/    death_mark = clone_object("/room/death/death_mark");
/    move_object(death_mark, myself);
/
/  ** Fordster - wot no Death Mark */

   tell_object(myself, "The Death sequence aint here right now.\n");

    return 1;
}

remove_ghost() {
    if (!ghost)
	return 0;
    write("You feel a very strong force.\n");
    write("You are sucked away...\n");
    write("You reappear in a more solid form.\n");
    say("Some mist disappears.\n");
    say(cap_name + " appears in a solid form.\n");
    ghost = 0;
    dead = 0;
    msgin = "arrives";
    msgout = "leaves";
    save_me(1);
    return 1;
}

drink_alco(strength) {
	
    if (intoxicated + strength > level * 3) {
	write("You fail to reach the drink with your mouth.\n");
	return 0;
    }

    add_intox(strength / 2);

    if (intoxicated == 0)
	write("You are completely sober.\n");

    if (intoxicated > 0 && headache)  {
	headache = 0;
	tell_object(myself, "Your headache disappears.\n");
    }

    if (intoxicated > max_headache)
	max_headache = intoxicated;

    if (max_headache > 8)
	max_headache = 8;

    return 1;
}

drink_soft(strength) {

    if (soaked + strength > level * 8) {
	write("You can't possibly drink that much right now!\n" + 
	      "You feel crosslegged enough as it is.\n");
	return 0;
    }

    add_soaked(strength * 2);

    if (soaked == 0)
	write("You feel a bit dry in the mouth.\n");

    return 1;
}

eat_food(strength) {

    if (stuffed + strength > level * 8) {
	write("This is much too rich for you right now! Perhaps something lighter?\n");
	return 0;
    }

    add_stuff(strength * 2);

    if (stuffed == 0)
	write("Your stomach makes a rumbling sound.\n");

    return 1;
}

/*
 *  This calculates the value the the player would get selling his
 *  whole inventory to the shop.  It is what takes care of crash
 *  reimburismemnt mostly.
 *
 *  Recoded for MudOS by Artagel 1-5-94
 */

int filter_worthless(int arg) {
  return arg;
}

compute_values() {
  int i, *values, tot_value;

  values = filter_array(deep_inventory(this_object())->query_value(), "filter_worthless", this_object());
  i = sizeof(values);
  tot_value = 0;

  while(i--)
    tot_value += (values[i] > 1000) ? 1000 : values[i];

  return tot_value;
}

save_me( value_items) {
/* Sils */
/* commented out - it's annoying everyone...
#ifdef SAVE_EXP
    if ((experience<200) && (level==1)) {
        tell_object(this_object(), "You need a minimum of 200 exp before you will be saved.\n");
        return 1;
    }
#endif
*/

    if (money > 30000) {
        tell_object( this_object(), "You can't carry all this money\nYou drop some.\n");
        this_object()->add_money(25000 + random(5000) - money);
    }
    if (value_items && first_inventory(this_object()) )
        tot_value = compute_values(first_inventory(this_object()));
    else
        tot_value = 0;
    compute_auto_str();
    check_weight();
    save_object( PDATA_DIR+"/"+name);
}

query_quests(str) {

    if(!stringp(str))
	return quests;

    if(!stringp(quests))
        return 0;

    return (strsrch(quests, str) != -1);
}

int query_quest_points() {
/*
 * A new function to return the players quest points total
 * Ford Dec 93 @ VR
 *
 */
   string *quest_arr;
   int foo, baa, rrdd, county, do_write;
 
    if( !quests)
	return 0;
   quest_arr=explode(quests, "#");
   foo = sizeof(quest_arr);
   if(this_player()->query_level()>500)
     do_write = 1;

   for (baa = 0; baa < foo; baa++){
     if(do_write)
       write("Checking quest : "+quest_arr[baa]+"\n");
     county = (int)QUEST_D->get_quest_num(quest_arr[baa]);
     if( county > -1) {
       rrdd = rrdd + (int)QUEST_D->get_value(county);
         if ( do_write)
           write("Value of "+(int)QUEST_D->get_value(county)+" added.\n");
         }
     }
   return rrdd;
}

int set_quest( string quest) {

    object tp1, prev_ob;
    string tp1_uid;

    if( !quest || query_quests( quest))
	return 0;

    prev_ob = previous_object();
    tp1 = this_player(1);

    if( prev_ob) {
	if( tp1)
	    tp1_uid = getuid( tp1);
	else
	    tp1_uid = "NOONE";
	log_file("QUESTS", sprintf("%s given %s by %s (e: %s tp1: %s) %s\n",
				   name, quest, file_name( prev_ob),
				   geteuid( prev_ob), tp1_uid, ctime()));
    }
    if( !quests)
	quests = quest;
    else
	quests += "#" + quest;

    return 1;
}

static make_scar() {
    if (level < 10)
	return;
    scar |= 1 << random(MAX_SCAR);
}

void show_scar() {
    int i, j, first, old_value;
    string *scar_desc;

    scar_desc = ({ "left leg", "right leg", "nose", "left arm", "right arm",
		   "left hand", "right hand", "forhead", "left cheek",
		   "right cheek" });
    j = 1;
    first = 1;
    old_value = scar;
    while(i < MAX_SCAR) {
	if (scar & j) {
	    old_value &= ~j;
	    if (first) {
		write(cap_name + " has a scar on " + query_possessive() +
		      " " + scar_desc[i]);
		first = 0;
	    } else if (old_value) {
		write(", " + query_possessive() + " " + scar_desc[i]);
	    } else {
		write(" and " + query_possessive() + " " + scar_desc[i]);
	    }
	}
	j *= 2;
	i += 1;
    }
    if (!first)
	write(".\n");
}

kickstart_my_heart(arg) {  /* thanks to motley crue. ;) - Llel */
    set_heart_beat(1);
    remove_call_out("quit"); 
    return 1;
}

nomask string process_input( string str) {

    if( !shell_ob)
	get_backup_shell_ob();
    return (string)shell_ob->parse_input( str);
}

void get_backup_shell_ob() {

    ( shell_ob = new( STD_SHELL))->move( myself, 1);
}

// Command to get a shell.
int shell() {

    get_backup_shell_ob();
    write("Ok.\n");
    return 1;
}

nomask int cmd_hook( string str) {

    if( !check_access()) {
	perror("%s (euid: %s): Illegal call of cmd_hook()",
	       file_name( previous_object()), geteuid( previous_object()));
	return 0;
    }
    if( !shell_ob)
        get_backup_shell_ob();

    return (int)shell_ob->cmd_hook( str);
}

/* Gudu -- for my gudusoul -- 8/31/93 */
string query_env_name() {

    if( environment())
	return file_name( environment());
    else
	return "limbo";
}

/* Most of the set commands lumper together -- Gadget */

set_al		(i)	{ if (!intp(i)) return; alignment = i;	}
set_alignment	(str) 	{ al_title 	= str; 	return 1;	}
set_alt_name	()	{ 			return 0;	}
set_blind 	(i)	{ blind   	= i;	return i;	}

int set_current_path( string str) {

    if( !check_access())
	return 0;

    current_path = str;
    return 1;
}

int set_env_var( string var, string str) {

    env_vars[var] = str;
    return 1;
}

int remove_env_var( string var) {

    map_delete( env_vars, var);
    return 1;
}

string query_env_var( string var) {

    if( !env_vars)
	return 0;

    return env_vars[var];
}

mapping query_env_vars() {

    return copy( env_vars);
}

int set_cwd(string str) { set_current_path( str); }
int set_debug_cmd_hook	( int n) { debug_cmd_hook_flag 	 = n;	return 1; }
set_edtitle	(str)	{ edtitle 	= str;	return 1;	}
set_edalign	(str)	{ edalign 	= str;	return 1;	}
set_guild_string(str) 	{ guild_string	= str;	return 0;	}
set_id		()	{ 			return 0; 	}
set_last_login	(str)	{ last_login = str;	return 1;	}

set_last_login_time() {

    if( !check_access())
	return 0;

    last_login_time = time();

    return 1;
}

set_called_from_ip() {  

    if( !check_access())
	return 0;

    called_from_ip = query_ip_number();
    return 1;
}

int set_last_ob( object ob) { last_ob 	= ob;	return 1; 	}
int set_ob_list( object *ob) { ob_list 	= ob;	return 1;	}
set_long	()	{ 			return 0; 	}
set_mailaddr	(str) 	{ mailaddr 	= str;	return 0;	}
setmin		(str)	{ msgin 	= str;	return 1;	}
setmout		(str)	{ msgout 	= str;	return 1;	}
setmmin		(str)	{ mmsgin 	= str;	return 1;	}
setmmout	(str)	{ mmsgout 	= str;	return 1;	}
setmsgclone	(str)	{ msgclone	= str;	return 1;	}
setmsgdest	(str)	{ msgdest	= str;	return 1;	}

set_race	()	{ 			return 0; 	}
set_short	()	{ 			return 0; 	}

/* Most of the query commands lumper together -- Gadget */

query_attacker_ob()	{ return attacker_ob; }
query_blind()		{ return blind; 		}
set_brief(arg)		{ brief=arg; }
query_brief() 		{ return brief;			}
query_Con()		{ return Con; }
nomask query_current_path()    { return current_path;          }
set_desc(str)		{ description=str; }
query_Dex()		{ return Dex; }
set_edit(arg)		{ edit_on=arg; }
query_edit()		{ return edit_on;		}
query_experience()	{ return experience; }
query_ghost()		{ return ghost; }
query_guild_string() 	{ return guild_string;		}
query_hit_point()	{ return hit_point;		}
set_hunted(arg)		{ hunted=arg; }
query_hunted()		{ return hunted; }
query_Int()		{ return Int; }
query_intoxination()	{ return intoxicated;		}
query_intoxication()	    { return intoxicated;          }
query_invis()		{ return is_invis;		}
nomask string query_last_file()	{ return last_file;		}
nomask query_last_login()	{ return last_login;		}
nomask query_last_login_time(){ return last_login_time;}
nomask query_called_from_ip() { return called_from_ip;}
nomask object query_last_ob()	{ return last_ob;		}
nomask object *query_ob_list() { return ob_list;		}
query_mailaddr()	{ return mailaddr;		}
query_msgclone()	{ return msgclone;		}
query_msgdest()		{ return msgdest;		}
query_msgin()		{ return msgin;			}
query_msgout()		{ return msgout;		}
query_mmsgin()		{ return mmsgin;		}
query_mmsgout()		{ return mmsgout;		}
query_no_remote_soul()	{ return no_remote_soul; 	}
set_no_remote_soul(arg) { no_remote_soul=arg; }
trs(arg){ no_remote_soul=arg;}
nomask string query_path()		{ return current_path;		}
query_pretitle()	{ return pretitle;		}
nomask string query_real_name()	{ return name;	                }
nomask string query_cap_name() { return capitalize(name);      }
nomask string query_realname()	{ return real_name;		}
query_Str()		{ return Str; }
query_stuffed()		{ return stuffed;		}
query_soaked()		{ return soaked;		}
query_title()		{ return title;			}
query_wc()		{ return weapon_class;		}
int query_kill_flag()   { return kill_flag; }

void set_kill_flag(int flag) { kill_flag=flag; return; }

int set_invis(int vis) { 
    if (wizardp(this_object()))
	is_invis = vis;
    else
	is_invis = 0;
    return vis;
}

int set_last_file( string str) { 

    if( !check_access())
	return 0;

    last_file = str;
    return 1 ;
}

int check_access() {

    string my_euid, their_euid;
    object prev_ob;

    my_euid = geteuid();
    if( prev_ob = previous_object())
        their_euid = geteuid( prev_ob);
    else
	their_euid = my_euid;
    
    if( their_euid == ROOT_UID || their_euid == my_euid || 
       query_wizard_level( their_euid) > query_wizard_level( my_euid))
	return 1;
    else
	return 0;
}

// localcmds lfun added by Chuck. 24th Feb 94.
mixed *local_commands() {
  if(geteuid(previous_object()) != ROOT_UID &&
     geteuid(previous_object()) != getuid(this_object()) ) {
    message("my_action", "You aren't authorized to check this information.",
            this_object());
    return ({});
  }
  return commands();
}

int command_me( string cmd) { 

    if( !check_access())
	return 0;

    return efun::command( cmd);
}
 
/* Added by Slider 9/17/95 */

set_scar(i) {scar = i;} 

