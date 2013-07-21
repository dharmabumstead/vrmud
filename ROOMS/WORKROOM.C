/* workroom.c
 * Slider's workroom
 * last updated 12/22/93 by Slider
 */

#include "/players/slider/include/slider.h"

inherit "room/room";

object bboard;
status privacy;

reset(arg)
{
   if (!bboard) {
      bboard = clone_object("/std/board_ob");
      bboard->set_save_name("players/slider/logs/sliderbd");
      move_object(bboard, this_object());
   }
   
   privacy = 1;

   if (arg) return;
}

init()
{
    if((this_player()->query_real_name() != "slider") && (privacy) &&
      (this_player()->query_level() < 22)) {
         write("Oof! You walk right into Slider's locked door!\n");
         move_object(this_player(), "/room/newroom/square");
         tell_room(this_object(),"You hear a muffled thud as " +
            this_player()->query_name()+" slams into the locked door!\n");
         return(1);
    "/players/slider/castle"->create();
    }
    ::init();
    add_action("set_privacy", "privacy");
    add_action("summon", "summon");
    add_action("clock", "clock");    
    add_action("read_check", "read");
    return(1);
}

read(str)
{
   if(str != "board") return(0);

   if(PLAYER_NAME != "Slider") {
      write("Hey! That's PRIVATE!\n");
      tell_room(THIS, PLAYER_NAME + 
         " tries to read the bulletin board! Nosy!\n");
      return(1);
   }
   return(0);
}

create()
{
    set_short("Slider's Laboratory");
    set_long("\
You're in Slider's MudLab.  Computer equipment of varying degrees of\n\
functionality is scattered everywhere!  Stacks of manuals and printouts\n\
are piled on nearly every available workspace.  A decrepit looking fern\n\
leans drunkenly in one corner of the room.  A computer hutch seems to be\n\
at the center of the cyclone. It holds a fairly impressive looking computer\n\
system and a stereo that looks like it's more than capable of blistering\n\
paint! A room that looks like a den lies east of here, and a shimmering\n\
blue portal reveals exits to.....just about anywhere.\n");

    add_item("fern","It bears a strange resemblance to Manute Bol!");
    add_item("manual",
"There's dozens of them scattered everywhere, with such interesting titles\n\
as _Writing Solid Code_, _Slider's LPC Bible_, and a bunch of Win32 stuff.\n");

    add_item("system",
"It's painted flat black and looks pretty dangerous.  Rumor has it that\n\
it's equipped with a prototype of Intel's new Pentium chip.  A closer\n\
look at the screen reveals that it's running Windows NT.");

    add_item("stereo",
"An elaborate blaster with CD, dual tape decks, receiver, can opener, and\n\
atomic cigarette lighter!  There's a huge stack of CDs and cassettes \n\
piled next to it.");

    add_item("stack",
"You're looking at the collection of a true musical schizoid!  The range\n\
of tastes represented is astonishingly wide.  Artists you see represented\n\
include Steely Dan, Alice In Chains, Mozart, Black Sabbath, and even some\n\
Bert Convy!  Weird....");

    add_exit(ROOMS+"den", "east");
    add_exit("/room/newroom/square","square");
    add_exit("/room/newroom/wizpost","post");
    add_exit("/room/newroom/adv_guild","main");
    add_exit(ROOMS+"elsquare","elwoode");
    add_exit("/room/newroom/god_guild","god");
    set_light(1);
    reset();
}

set_privacy(str)
{
    if(PLAYER_NAME != "Slider")
    {
       write("Sorry, only Slider is allowed to do that!\n");
       return(0);
    }

    if(!str)
    {
        if(privacy)
        {
            write("Privacy is currently ON.\n");
        }
        else
        {
            write("Privacy is currently OFF.\n");
        }
        say("Slider checks the lab's security system\n");
        return(1);
    }
    else
    {
        if(str == "on")
        {
            write("Privacy is now ON\n");
            say("Slider turns on the lab's security system.\n");
            set_short("Slider's Locked Laboratory");
            privacy = 1;
        }
        else
        {
            write("Privacy is now OFF\n");
            say("Slider switches off the security system.\n");
            set_short("Slider's Laboratory");
            privacy = 0;
        }
    }
    return(1);
}

summon(str)
{
    object ob;
    object where;
    int oldpriv;

    if(PLAYER_NAME != "Slider")
    {
       write("Sorry, only Slider is allowed to summon here!\n");
       return(0);
    }

    if (!str)
       return 0;

    ob = find_living(str);

    if (!ob)
    {
       write("They're not on right now!\n");
       return 1;
    }

    oldpriv = privacy;

    privacy = 0;
    tell_object(ob, "You are summoned to Slider's Workroom.\n");
    where=environment(ob);
    say(ob->query_name()+" has been summoned to Slider's workroom.\n");
    write(ob->query_name()+" has been summoned to Slider's workroom.\n");
    move_object(ob,THIS);
    if (ob->query_name()!="Someone")
    tell_room(where,ob->query_name()+" "+ob->query_mmsgout()+".\n");
    privacy = oldpriv;
    return 1;
}

clock() {
    object square;

    square = find_object("/room/newroom/square");

    if(square) {
        say(this_player()->query_name() + " checks the game 'clock'.\n");
        square->long("clock");
        return(1);
    }
    return(0);
}
