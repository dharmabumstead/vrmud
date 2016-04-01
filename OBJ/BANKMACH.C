inherit "/std/move";
/***************************************************************************
 * NAME:                                                                   
 *    bankmach.c                                                           
 * DESCRIPTION:                                                            
 *    Slider's Bank Object                                                 
 * VERSION:                                                                
 *    1.3                                                                  
 * ENVIRONMENT:                                                            
 *    Virtual Realities - LPMud 3.1.2-DR                                   
 * UPDATE HISTORY                                                          
 *    04/22/93  Slider  Initial version                                    
 *    04/27/93  Slider  Added create_account                               
 *    07/??/93  Llel    Added 30K coin cap
 *    08/29/93  Slider  Added logging to wiz commands
 *    12/04/93  Slider  Added 'new card' feature for players with lost 
 *                      autoloads 
 *    12/22/93  Slider  Added optional player name argument to balance
 *                      so wizzes can get player balances
 *    01/14/94  Slider  Changed array insert/deletes to use implicitly
 *                      declared arrays 
 *    12/28/94  Slider  Added 'open' and 'close' to enabled dynamically
 *                      closing down bank if necessary. Still need to 
 *                      update the rest of this thing!
 *	  02/12/96	Slider	Added 'more' support to report output
 *     6/5/97  Frijoles  Moved to Barrowmere, change description for city
 *    11/-/97  Frijoles  Attempting a clean way to raise max balance
 ***************************************************************************/
// Added front slash to SAVE_NAME - Picard 12/30/94
#define SAVE_NAME "/players/slider/logs/slidrbnk"
#define LOG_NAME "slider.bank"
#include "/players/slider/include/slider.h"
/*
#define MAX_BALANCE 30000
*/
#define BALANCE_CUTOFF_LEVEL 25 // max balance stops raising at this point
#define MAX_BALANCE find_balance()
#define BALANCE_MULTIPLIER 2.75

int closed;
string *list;
object owner;

id(str) {
   return ((str== "bank") || (str=="sliderbank") ||
      (str=="teller") || (str=="machine"));
}

string short_desc;

short() { return short_desc; }

/************************************************************/
long() {
  write(
"This is a Barrowmere ahead-of-time teller machine. To open an account, \n"+
"type 'open <amount>'.  You can also use 'balance', 'withdraw <amount>', and\n"+
"'deposit <amount>'.  Withdrawing all of your funds closes your account.\n");

   
  if(closed) {
     write("The bank is currently closed.\n");
  }

  write("\nLose your card? Type 'card' to get a new one!\n");

  if(present("bankcard", this_player())) {
     write("\n"+
"You'll have to go to Drfeelgood's bank, withdraw your cash, and come back\n"+
"and 'shred' your old Drfeelgood bankcard before opening an account here.\n");
  }
     
  if(this_player()->query_level() >20) {
     write("\nWizzes: use 'report' to see an account report.\n");
  }

  if((this_player()->query_level() >200) ||
     (this_player()->query_real_name() == "slider")) {
     write("\nSeniors and above:\n"+
     "   Use 'balance <name>' to get a player's balance.\n"+
     "   Use 'create <name> <amount>' to create an account.\n"+
     "   Use 'open' or 'close' to open and close the bank.\n"+
     "   Use 'change <name> <amount>' to change an account.\n"+
     "   Use 'remove <name>' to remove an account.\n");
  }

  return 1;
}

/************************************************************/
create()  {
   list = allocate(0);
   set_short("a 24-hour bank machine");
   restore_object(SAVE_NAME);
}

/************************************************************/
get() { return 0; }

/************************************************************/
drop() { return 0; }

/************************************************************/
init() {
   /* Add our commands */
   add_action("deposit_cash", "deposit");
   add_action("bank_balance", "balance");
   add_action("withdraw_cash", "withdraw");
   add_action("open_account", "open");
   add_action("remove_account", "remove");
   add_action("change_account", "change");
   add_action("list_accounts", "report");
   add_action("create_account", "create");
   add_action("shred_card", "shred");
   add_action("close_bank", "close");
   add_action("open_bank", "open");
   add_action("new_card", "card");
}

/************************************************************/
new_card() {
  
   /* Make sure they have an account here first! */ 
   if(find_account(this_player()->query_real_name()) == -1) {
      write("To get a card, you need to open an account!\n");
      return(1);
   } 
 
   /* Check to see if we already have a bank card (sp bancard to avoid
      confusion w/Drfeelgood's old one) */
 
   if(!present("bancard", this_player())) {
      move_object(clone_object(OBJ+"bankcard"), this_player());
      write("You receive a NEW bank card!  Try not to lose it!\n");
      log_file(LOG_NAME, ctime()+" "+
         capitalize(this_player()->query_real_name()) + " gets a new card.\n");
   } else {
      write("You've already got a bank card!\n");
   }

   return(1);
}


/************************************************************/
shred_card() {
  object oldcard;
  
  oldcard = present("bankcard", this_player());
  
  if(oldcard) {
     destruct(oldcard);
     
     write(
"A small arm darts out of the bank machine and grabs your old bank card!\n"+
"There's a munching sound from inside the machine!\n");
  } else {
     write("You don't have an old bankcard to destroy!\n");
  }
  return(1);
}

/************************************************************/
deposit_cash(str) {
   int record, p_amt, amt, balance;
   string name;

   if (!str) {
      write("We need to know how much to deposit!\n");
      return(1);
   }

   amt = atoi(str);

   if(amt <= 0) {
      write("You need to deposit a _positive_ amount!\n");
      return(1);
   }

   if((record = find_account(this_player()->query_real_name())) == -1) {
	write("You have no account with the Barrowmere Bank!\n");
      return(1);
   }
   if(closed) {
      write("Sorry, the bank is closed right now!\n");
      return(1);
   }


   sscanf(list[record], "%s %d", name, balance);
/* llel */
   if (balance+amt > MAX_BALANCE) {
       write("Sorry, the maximum balance you may have is "+MAX_BALANCE+
         " coins.\n");
       return 1;
   }

   p_amt = this_player()->query_money();

   if(amt > p_amt) {
      write("You're embarassed to find that you don't have that many coins!\n");
      return(1);
   }

   this_player()->add_money(-(amt));

   balance+=amt;

   list[record] = this_player()->query_real_name() + " " + balance;
   if(wizardp(this_player())) write("Save name is: " + SAVE_NAME + "\n");
   save_object(SAVE_NAME);

   log_file(LOG_NAME, ctime()+" "+capitalize(name)+" deposits "+amt+
    " balance " + balance + "\n");

   write("You deposit "+amt+" coins.  Your balance is now " + balance+
      " coins.\n");

   return(1);
}

/************************************************************/
withdraw_cash(str) {
   int record, balance, amt;
   string name;

   if (!str) {
      write("How much money do you need?\n");
      return(1);
   }

   amt = atoi(str);

   if(amt <= 0) {
      write("You need to withdraw a _positive_ amount!\n");
      return(1);
   }

   if((record = find_account(this_player()->query_real_name())) == -1) {
	write("You have no account with the Barrowmere Bank!\n");
      return(1);
   }

   
   if(closed) {
     write("Sorry, the bank is closed right now!\n");
      return(1);
   }

   sscanf(list[record], "%s %d", name, balance);

   if(amt > balance) {
      write("You have insufficient funds for that transaction!\n");
      return(1);
   }

   this_player()->add_money(amt);

   balance-=amt;
   save_object(SAVE_NAME);

   if (balance == 0) {
      write("You close out your account.\n");
      list-=({list[record]});
      log_file(LOG_NAME, ctime()+" "+capitalize(name)+
         " closes their account.\n");
      save_object(SAVE_NAME);
      return(1);
   }

   list[record] = this_player()->query_real_name() + " " + balance;
   save_object(SAVE_NAME);

   log_file(LOG_NAME, ctime()+" "+capitalize(name)+" withdraws "+
      amt+" balance " + balance + "\n");

   write("You withdraw "+amt+" coins.  Your balance is now " + balance +
      " coins.\n");

   return(1);
}

/************************************************************/
bank_balance(str) {
   string name, dummy;
   int record, balance;

   if(!str) {
      name = this_player()->query_real_name();
   } else {
      if(PLAYER->query_level() >20) name = str;
   }

   if((record = find_account(name)) == -1) {
write(capitalize(name) + " has no account with the Barrowmere Bank.\n");
      return(-1);
   }

   sscanf(list[record], "%s %d", dummy, balance);
   write("Our records show that " + capitalize(name)+"'s balance stands at " + 
      balance+ " coins.\nYour max bank deposit is "+MAX_BALANCE+" coins.\n");

   if(str) {
      log_file(LOG_NAME, ctime() + " "+PLAYER_NAME + " checks " +
         capitalize(name) + "'s balance: "+balance+" coins\n");
   } else {
      log_file(LOG_NAME, ctime()+" "+capitalize(name)+" balance " + 
         balance + "\n");
   }

   return(balance);
}

/************************************************************/
open_account(str) {
   int i, balance, amt, p_amt;
   string name;
 

   if(closed) {
      write("Sorry, the bank is closed right now!\n");
      return(1);
   }

   if(present("bankcard", this_player())) {
      write(
"You'll have to go to Drfeelgood's bank, withdraw your cash, and come back\n"+
"and 'shred' your old Drfeelgood bankcard before opening an account here.\n");
      return(1);
   }

   if (!str) {
      write("You need to open the account with some money!\n");
      return(1);
   }

   amt = atoi(str);

   if(amt <= 0) {
      write("You need to open the account with a _positive_ balance!\n");
      return(1);
   }

   if(find_account(this_player()->query_real_name()) != -1) {
      write("You already have an account with us!\n");
      return(1);
   } else {

      p_amt = this_player()->query_money();

      if(amt > p_amt) {
         write("You are embarassed to find that you don't have that many "+
            "coins!\n");
         return(1);
      }

      this_player()->add_money(-(amt));

      list+=({this_player()->query_real_name() + " " + amt});
      save_object(SAVE_NAME);
	write("Thanks for banking with the Barrowmere Bank!\n");

      /* Check to see if we have a bank card (sp bancard to avoid
         confusion w/Drfeelgood's old one) */

      if(!present("bancard", this_player())) {
         move_object(clone_object(OBJ+"bankcard"), this_player());
         write("You receive a bank card!  Look at it for instructions.\n");
      }

      log_file(LOG_NAME, ctime()+" "+
        capitalize(this_player()->query_real_name())
        +" opens account with " + amt + " coins\n");
   }
   return 1;
}

/************************************************************/
list_accounts() {
   int counter, amount, total, lines, i;
   string *templist, *output;
   string name;

   if((this_player()->query_level()) <21) return 0;

   total = 0;
   i = 0;

   templist = sort_array(list,"sort_by_name",this_object());

   output = allocate(sizeof(templist) + 20);

   output[i++] = sprintf("%s", "========================\n");
   output[i++] = sprintf("%s", pad("NAME", 15) + " " + pad("BALANCE", -8)+"\n");
   output[i++] = sprintf("%s", "------------------------\n");

   for(counter = 0; counter < sizeof(templist); counter++) {
      sscanf(templist[counter], "%s %d", name, amount);
      output[i++] = sprintf("%s", pad(capitalize(name), 15) + " " + pad(amount, -8)+"\n");
      total+=amount;
   }

   output[i++] = sprintf("%s", "------------------------\n");
   output[i++] = sprintf("%s", "TOTAL "+pad(total, -18)+"\n");

   more(implode(output, ""));
   
   log_file(LOG_NAME,ctime()+" "+capitalize(this_player()->query_real_name())+
      " lists accounts.\n");

   return(1);
}

/************************************************************/
remove_account(str) {
   int record;

   if(!str) return 0;

   if((this_player()->query_level() < 250) &&
      (this_player()->query_real_name() != "slider")) return 0;

   if((record = find_account(str)) == -1) {
      write("Account not found for " + capitalize(str) + ".\n");
      return(1);
   }

   list-=({list[record]});
   write("Removed account of " + str + ".\n");
   save_object(SAVE_NAME);

   log_file(LOG_NAME,ctime()+" "+capitalize(this_player()->query_real_name())+
      " removes account of "+capitalize(str)+"\n"); 
   return(1);
}

/************************************************************/
change_account(str) {
   int record, amount;
   string name;

   if((!str)) return 0;

   if((this_player()->query_level() < 250) &&
      (this_player()->query_real_name() != "slider")) return 0;

   if(sscanf(str, "%s %d", name, amount) != 2) return 0;

   if((record = find_account(name)) == -1) {
      write("Account not found for " + capitalize(name) + ".\n");
      return(1);
   }

   list[record] = name + " " + amount;
   write("Record for account of " + capitalize(name) + " updated to " +
      amount + ".\n");
   save_object(SAVE_NAME);
   log_file(LOG_NAME,ctime()+" "+capitalize(this_player()->query_real_name())+
      " changes account of "+capitalize(name)+" to "+amount+"\n"); 
   return(1);
}

/************************************************************/
set_short(str) {
  short_desc=str;
}

/************************************************************/
int find_account(string find) {
   int i, balance;
   string name;

   for(i=0;i<sizeof(list);i++) {
      sscanf(list[i], "%s %d", name, balance);
      if(name == find) {
         return(i);
      }
   }
   return(-1);
}

/************************************************************/
create_account(str) {
   int i, balance, amt, p_amt;
   string name;

   if (!str) {
      return(0);
   }

   sscanf(str, "%s %d", name, amt);

   if(amt <= 0) {
      write("You need to open the account with a _positive_ balance!\n");
      return(1);
   }

   if(find_account(name) != -1) {
      write(capitalize(name) + " already has an account with us!\n");
      return(1);
   }

   this_player()->add_money(-(amt));

   list+=({name + " " + amt});

   write("OK - account created for " + capitalize(name) +
      " with amount of " + amt+".\n");
   save_object(SAVE_NAME);

   log_file(LOG_NAME,ctime()+" "+capitalize(this_player()->query_real_name())+
      " creates account for "+capitalize(name)+" with "+amt+"\n"); 
   return 1;
}

int sort_by_name( object ob1, object ob2) {
    return strcmp((string) ob1, (string) ob2);
}

close_bank() {
   if(this_player()->query_level() >299) {
      write("The bank is now closed!\n");
      closed = 1;
      return(1);
   }
   return(0);
}

open_bank() {
   if(this_player()->query_level() > 299) {
      write("The bank is now open.\n");
      closed = 0;
      return(1);
   }
   return(0);
}

int find_balance() {
	int tmp;
	tmp = this_player()->query_level();
	if(tmp > BALANCE_CUTOFF_LEVEL) tmp = BALANCE_CUTOFF_LEVEL;
	return to_int(to_float(tmp*(BALANCE_MULTIPLIER)))*1000;
}
