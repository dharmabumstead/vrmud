/* Slider's Castle - the very definition of 'simple' *grin* */
/* glommed from Gudu and modified 4/2/93 */
/* update 12/10/93 */
 
#define ENTRY "/room/circ/roads/west1b"
#define ENTRY_LONG "A small path leads north through some trees.\n"
 
reset(arg)
{
   if (arg) return;
}
 
create() {
    string old_long, tmp;
    object square;
 
   "/players/slider/rooms/elbank"->mosh_mosh();
 
    square = find_object("/room/newroom/square");
 
 
    old_long = ENTRY->query_long();
 
    if( sscanf( old_long, "%s"+ENTRY_LONG, tmp) != 1) {
       ENTRY->set_long( old_long+ENTRY_LONG);
	ENTRY->add_exit("/players/slider/rooms/path3","north");
    }
}
