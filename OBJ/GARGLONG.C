inherit "obj/weapon";
 
reset(arg) {
    ::reset(arg);
    if(arg)
        return;
    set_name("longsword");
    set_class(16);
    set_short("A gargoyles longsword");
    set_long(
"A deadly-looking curved gargoyle longsword.  From the quality, it looks as\n"+
"if this once belonged to a gargoyle officer.\n");
    set_alias("sword");
    set_weight(4);
    set_value(1100);
}
 
 
