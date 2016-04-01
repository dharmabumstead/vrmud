inherit "obj/weapon";
 
reset(arg) {
    ::reset(arg);
    if(arg)
        return;
    set_name("shortsword");
    set_class(12);
    set_short("a gargoyle shortsword");
    set_long("A gargolye shortsword.  It looks very sharp!\n");
    set_alias("sword");
    set_weight(3);
    set_value(800);
}
 
 
