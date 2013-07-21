inherit "obj/armour";
 
reset(arg) {
    ::reset(arg);
    if (arg)
        return;
    set_name("cloak");
    set_type("cloak");
    set_light(1);
    set_scale_ac(150);
    set_short("a flame cloak");
    set_long("A flame giant's brilliant flaming cloak.\n");
    set_value(500);
    set_weight(2);
}
