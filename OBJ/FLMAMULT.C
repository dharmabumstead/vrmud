inherit "obj/armour";
 
reset(arg) {
    ::reset(arg);
    if (arg)
        return;
    set_name("amulet");
    set_type("amulet");
    set_light(1);
    set_scale_ac(100);
    set_short("a flame amulet");
    set_long("A flame giant's brightly glowing enchanted amulet.\n");
    set_value(500);
    set_weight(2);
}
