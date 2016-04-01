inherit "std/move";
object c;
string name;

inherit "std/object";

create () {

	set_id(({"gag","aGAGa"}));

	c = this_player();

	add_property("getable");
	add_property("undropable");
	}

set_name(arg)
{
	name = arg;
}

init() {
	add_action("g", "gossip");
	add_action("s", "shout");
	return 1;
}

g(arg)
{
write("You gossip: "+arg+"\n");
	return 1;
}

s(arg)
{
	write("You shout: "+arg+"\n");
	return 1;
}

dest(arg)
{

	if (arg != "gag")
		return 0;
	
	if (this_player() == c) 
		return 0;

	if(this_player()->query_level() < 21)
		tell_object(c, "-)"+name+" has attempted to dest the gag :(\n");
	else
		tell_object(c, "-)"+name+" has dested the gag :(\n");

}
