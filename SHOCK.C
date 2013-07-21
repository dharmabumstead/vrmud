#include <lib.h>
inherit CANSPELL;

main(str)
{
object ob;

/*    if (guild_string != 0 && guild_string != "")
    	return 0;
*/  	
    if (this_player()->query_level() < 10) {
	write("You haven't learned this spell yet.\n");
    	return 1;
    	}
    	
    ob = can_spell(str);
    
    if (ob) this_player()->shock_object(ob);
	
    return 1;
}
