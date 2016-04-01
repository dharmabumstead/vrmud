inherit "obj/armour";
 
reset(arg) {
    ::reset(arg);
    if (arg)
        return;
    set_name("platemail");
    set_type("armour");
    set_scale_ac(410);
    set_short("a suit of gargoyle platemail");
    set_long("Fine quality gargoyle platemail. It looks very strong.\n");
    set_value(800);
    set_weight(4);
}
