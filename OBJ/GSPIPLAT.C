/* gspiplat.c */

inherit "obj/armour";
 
reset(arg) {
    ::reset(arg);
    if (arg)
        return;
    set_name("hide");
    set_type("armour");
    set_scale_ac(600);
    set_short("a plated giant spider hide");
    set_long(
"This is the hide of the fabled giant spider that is rumored to dwell in the\n"+
"caverns northeast of Elwoode.  The hide has a rock-hard natural plating that\n"+
"makes this very fine armor indeed!\n");
    set_value(8000);
    set_weight(4);
}
