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
 ***************************************************************************/
#define SAVE_NAME "players/slider/logs/slidrbnk"
#define LOG_NAME "slider.bank"
#include "/players/slider/include/slider.h"
#define MAX_BALANCE 30000

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
"This is a First Bank of Elwoode 24-hour teller machine.  To open an account, \n"+
"type 'open <amount>'.  You can also use 'balance', 'withdraw <amount>', and\n"+
"'deposit <amount>'.  Withdrawing all of your funds closes your account.\n");

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
     "   Use 'create <name> <amount>' to create an account.\n"+
     "   Use 'change <name> <amount>' to change an account.\n"+
     "   Use 'remove <name>' to remove an account.\n");
  }

  return 1;
}

/************************************************************/
create()  {
   list = allocate(0);
   set_short("a teller machine");
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
      write("You have no account with First of Elwoode!\n");
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
      write("You have no account with First of Elwoode!\n");
      return(1);
   }

   sscanf(list[record], "%s %d", name, balance);

   if(amt > balance) {
      write("You have insufficient funds for that transaction!\n");
      return(1);
   }

   this_player()->add_money(amt);

   balance-=amt;

   if (balance == 0) {
      write("You close out your account.\n");
      list-=list[record];
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
bank_balance() {
   string name, dummy;
   int record, balance;

   name = this_player()->query_real_name();

   if((record = find_account(name)) == -1) {
      write("You have no account with First of Elwoode!\n");
      return(1);
   }

   sscanf(list[record], "%s %d", dummy, balance);
   write("Your account balance stands at " + balance+ " coins.\n");
   log_file(LOG_NAME, ctime()+" "+capitalize(name)+" balance " + 
      balance + "\n");

   return(1);
}

/************************************************************/
open_account(str) {
   int i, balance, amt, p_amt;
   string name;
 
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

      list+=this_player()->query_real_name() + " " + amt;
      save_object(SAVE_NAME);
      write("Thanks for banking with First Bank of Elwoode!\n");

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
   int counter, amount, total;
   string *templist;
   string name;

   if((this_player()->query_level()) <21) return 0;

   total = 0;

   templist = sort_array(list,"sort_by_name",this_object());

   write("========================\n");
   write(pad("NAME", 15) + " " + pad("BALANCE", -8)+"\n");
   write("------------------------\n");

   for(counter = 0; counter < sizeof(templist); counter++) {
      sscanf(templist[counter], "%s %d", name, amount);
      write(pad(capitalize(name), 15) + " " + pad(amount, -8)+"\n");
      total+=amount;
   }

   write("------------------------\n");
   write("TOTAL "+pad(total, -18)+"\n");
   write("========================\n");
   
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

   list-=list[record];
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

   list+=name + " " + amt;

   write("OK - account created for " + capitalize(name) +
      " with amount of " + amt+".\n");
   save_object(SAVE_NAME);

   log_file(LOG_NAME,ctime()+" "+capitalize(this_player()->query_real_name())+
      " creates account for "+capitalize(name)+" with "+amt+"\n"); 
   return 1;
}


sort_by_name(ob1,ob2) {
    return (ob1 > ob2);
}



