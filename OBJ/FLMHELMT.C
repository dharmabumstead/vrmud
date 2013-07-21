inherit "obj/armour";
 
reset(arg) {
    ::reset(arg);
    if (arg)
        return;
    set_name("helmet");
    set_type("helmet");
    set_light(1);
    set_scale_ac(120);
    set_short("a helmet of flame");
    set_long("A flame zombie's helmet.  It gives off quite a bit of light.\n");
    set_value(600);
    set_weight(2);
}
