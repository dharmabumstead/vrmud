inherit "obj/armour";
 
reset(arg) {
    ::reset(arg);
    if (arg)
        return;
    set_name("chainmail");
    set_type("armour");
     set_scale_ac(305);
    set_short("a suit of gargoyle chainmail");
    set_long("A sturdy looking suit of gargoyle chainmail.\n");
    set_value(480);
    set_weight(4);
}
 
