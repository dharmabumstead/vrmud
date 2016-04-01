/***************************************************************************
 * NAME:                                                                   *
 *    bankard.c                                                            *
 * DESCRIPTION:                                                            *
 *    Slider's Bank Card                                                   *
 * VERSION:                                                                *
 *    1.0                                                                  *
 * ENVIRONMENT:                                                            *
 *    Virtual Realities - LPMud 3.1.2-DR                                   *
 * UPDATE HISTORY                                                          *
 *    04/27/93  Slider Initial version                                     *
 ***************************************************************************/
#define BANK_LOC "/players/slider/rooms/elbank"
string short_desc;

id(str) {
   return ((str== "card") || (str=="bancard") || (str=="slidercard"));
}

short() { return short_desc; }

long() {
  write(
"This is a First Bank of Elwoode 24-hour bank card.  With it you can use \n"+
"'balance', 'withdraw <amount>', and 'deposit <amount>' for quick access\n"+
"to your cash from anywhere!  Please note that withdrawing all of your \n"+
"funds closes your account.\n");
  return 1;
}

create()  {
   set_short("a bank card");
}

get() { return 1; }

drop() {
   write("You wouldn't want to drop your bank card!\n");
   return 1;
}

query_auto_load () { return 1; }

init() {
   /* Add our commands */
   add_action("c_deposit_cash", "deposit");
   add_action("c_bank_balance", "balance");
   add_action("c_withdraw_cash", "withdraw");
}


set_short(str) {
  short_desc=str;
}

c_bank_balance() {
   object bankroom;
   string currloc;

   bankroom = find_object(BANK_LOC);

   if(!bankroom) {
      write("The bank is down for service right now.  Try later.\n");
      return(1);
   }

   currloc = environment(this_player());

   transfer(this_player(), bankroom);
   command("balance", this_player());
   transfer(this_player(), currloc);

   return(1);
}

c_withdraw_cash(str) {
   object bankroom;
   string currloc, bcmd;

   bcmd = "withdraw " + str;

   bankroom = find_object(BANK_LOC);

   if(!bankroom) {
      write("The bank is down for service right now.  Try later.\n");
      return(1);
   }

   currloc = environment(this_player());

   transfer(this_player(), bankroom);
   command(bcmd, this_player());
   transfer(this_player(), currloc);

   return(1);
}

c_deposit_cash(str) {
   object bankroom;
   string currloc, bcmd;

   bcmd = "deposit " + str;

   bankroom = find_object(BANK_LOC);

   if(!bankroom) {
      write("The bank is down for service right now.  Try later.\n");
      return(1);
   }

   currloc = environment(this_player());

   transfer(this_player(), bankroom);
   command(bcmd, this_player());
   transfer(this_player(), currloc);

   return(1);
}

