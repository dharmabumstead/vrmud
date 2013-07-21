inherit "obj/armour";
 
reset(arg) {
    ::reset(arg);
    if (arg)
        return;
    set_name("swimsuit");
    set_type("armour");
    set_scale_ac(150);
    set_short("a skimpy swimsuit");
    set_long("A very skimpy swimsuit! You *might* be able to fit into it!\n");
    set_value(250);
    set_weight(2);
}
