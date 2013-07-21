inherit "std/object";

create() {
   set_id(({ "shovel"}));
   set_short("a shovel");
   set_long("A Slider's True Value shovel!\n");
   set_value(50);
   add_property("getable"); /* Allow us to be picked up */
}


