inherit "/obj/monster";
inherit "/std/store_manager";
#include "path.h"

#define NAME "Orson the shopkeep"
#define SOUL_COMMANDS ({ "bop","curious","expect","glare","jump","kick",\
"mutter","peer","poke","strangle","tear" })

static void
soul_action() {
    command(SOUL_COMMANDS[random(sizeof(SOUL_COMMANDS))]+" "+
            this_player()->query_real_name());
}

list(str) {
    int    i;
    object *items;

    items = list_inventory(str);
    if (!str && !sizeof(items)) {
        write(NAME+" tells you: The stores are empty.\n");
        command("sob "+this_player()->query_real_name());
        return 1;
    }
    say(NAME+" shows "+this_player()->query_name()+
        " a list.\n",this_player());
    write(NAME+" shows you a list.\n");
    write("\n"+pad("Cost",-6)+pad("Quantity",-10)+"  Description\n"+
          pad("",78,'-')+"\n");
    if (!sizeof(items)) {
        write("\t-none-\n");
        return 1;
    }
    for (i=0; i<sizeof(items); i+=2)
        write(pad(items[i+1][0],-6)+pad(items[i+1][1],-10)+"  "+items[i]+"\n");
    write(pad("",78,'-')+"\n");
    return 1;
}

browse(str) {
    if (!str) {
        soul_action();
        return 1;
    }
    if (!browse_item(str))
        write("You fail to find it.\n");
    return 1;
}

value(str) {
    int offer;

    if (!str) {
        soul_action();
        return 1;
    }
    offer = value_player_item(str);
    if (offer == 0)
        write(NAME+" says: worthless to me\n");
    else if (offer == -1)
        write(NAME+" says: value what?\n");
    else if (offer == -2)
        write(NAME+" says: I don't deal in such items\n");
    else
        write(NAME+" says: I am prepared to pay "+offer+
              " coins for such an item\n");
    return 1;
}

sell(str) {
    int coins;

    if (!str) {
        soul_action();
        return 1;
    }
    if (str == "all") {
        coins = sell_all_items();
        if (coins == 0)
            write(NAME+" says: you have nothing worth selling\n");
        else if (coins == -1)
            write(NAME+" says: I had trouble taking one of your possessions "+
                  " ... better call a wizard\n");
        else {
            say(this_player()->query_name()+
                " sells everything.\n",this_player());
            write(NAME+" says: and here is your money\n");
            write(NAME+" gives you "+coins+" coin");
            if (coins != 1)
                write("s");
            write(".\n");
        }
        return 1;
    }
    coins = sell_item(str);
    if (coins == 0)
        write(NAME+" says: sell what?\n");
    else if (coins == -1)
        write(NAME+" says: I don't deal in such things\n");
    else if (coins == -2)
        write(NAME+" says: I can't take it off you ... better call a wizard\n");
    else {
        say(this_player()->query_name()+" sells something.\n",this_player());
        write(NAME+" gives you "+coins+" coins.\n");
    }
    return 1;
}

buy(str) {
    int cost;

    if (!str) {
        soul_action();
        return 1;
    }
    cost = buy_item(str);
    if (cost == 0)
        write(NAME+" says: I haven't one to sell\n");
    else if (cost == -1)
        write(NAME+" says: You can't afford it\n");
    else if (cost == -2)
        write(NAME+" says: It is too heavy for you to carry\n");
    else {
        say(this_player()->query_name()+" buys something.\n",this_player());
        write(NAME+" says: and that will be "+cost+" coins thankyou\n");
        write("You pay the amount.\n");
    }
    return 1;
}

create() {
    reset(0);
    set_name("orson");
    set_level(20);
    set_alias("shopkeep");
    set_race("human");
    set_male();
    set_hp(1500);
    set_ep(0);
    set_al(0);
    set_short("Orson the shopkeeper");
    set_long(
"This is Orson.  He's run the shop for as long as anyone can remember.  He\n"+
"appears to be older than dirt.  His stooped figure and snowy-white hair are\n"+
"betrayed by the sparkling green eyes of a shrewd negotiator.  He notices you\n"+
"staring at him and croaks:\n"+
" \"You can 'list' what I have, 'browse' over one particular item, 'value' one\"\n"+
" \"of your possessions, 'sell' one of your possessions, or 'buy' an item that\"\n"+
" \"catches your fancy.  Just ask.\"\n");
    set_wc(30);
    set_ac(17);
    set_chance(50);
    set_spell_mess1(NAME+" straightens out a rude customer!");
    set_spell_mess2("Orson expertly chops you in the neck!");
    set_spell_dam(100);
    load_chat(1,({ NAME+" says: Are you here to buy or loiter!?\n" }));
    set_store("/players/slider/rooms/stockrm");
    move_object(clone_object("obj/soul"),this_object());
}

init() {
    add_action("list","list");
    add_action("browse","browse");
    add_action("value","value");
    add_action("buy","buy");
    add_action("sell","sell");
}
