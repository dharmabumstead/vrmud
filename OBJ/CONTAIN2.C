int value, max_weight, local_weight;
string name_of_container ,cap_name ,alt_name ,alias_name;
string short_desc, long_desc;
string read_msg;
status open;   /* Open or closed - added by Slider 3/30/93 */

long() {
    write(long_desc);
    /* if ((first_inventory(this_object())) && (open==1)) */
    if (open==1)
       write("It is open.\n");
    else
       write("It is closed.\n");
}

reset(arg) {
    if (arg)
	return;
    local_weight = 0;
}

query_weight() { return local_weight; }

query_max_weight() { return max_weight; }

add_weight(w) {
    if (local_weight + w > max_weight)
	return 0;
    local_weight += w;
    return 1;
}

short() { return short_desc; }

id(str) {
   return str == name_of_container || str == alt_name || str == alias_name;
}

query_value() { return value; }

can_put_and_get() {
   if(open)
      return 1;
   else
      return 0;
}

get() { return 1; }

prevent_insert() {
    if (local_weight > 0) {
       write("You can't when there are things in the " +
          name_of_container + ".\n");
       return 1;
    }
    return 0;
}

set_weight(w) { local_weight = w; }

set_max_weight(w) { max_weight = w; }

set_value(v) { value = v; }

set_name(n) {
    name_of_container = n;
    cap_name = capitalize(n);
    short_desc = cap_name;
    long_desc = cap_name +"\n";
}

set_alt_name(n) { alt_name = n; }

set_alias(n) { alias_name = n; }

set_short(sh) { short_desc = sh; long_desc = short_desc + "\n"; }

set_long(lo) { long_desc = lo; }

set_read(str) {
    read_msg = str;
}

init() {
    open = 0;
    add_action("read", "read");
    add_action("open", "open");
    add_action("close", "close");
}

read(str) {
    if (str != name_of_container &&  str != alt_name && str != alias_name)
        return 0;
    write(read_msg);
    return 1;
}

open(str) {
    if (str != name_of_container &&  str != alt_name && str != alias_name)
        return 0;

    if(open) {
        write("It's already opened!\n");
        return 1;
    }

    open = 1;
    write("OK, " + name_of_container + " is now open.\n");
    say(this_player()->query_name()+" opens a " + name_of_container+ ".\n");
    return 1;
}

close(str) {
    if (str != name_of_container &&  str != alt_name && str != alias_name)
        return 0;

    if (!open) {
        write("It's already closed!\n");
        return 1;
    }

    open = 0;
    write("OK, " + name_of_container + " is now closed.\n");
    say(this_player()->query_name()+" closes a " + name_of_container+ ".\n");
    return 1;
}
