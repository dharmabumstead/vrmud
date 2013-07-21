/* Slider's Castle - the very definition of 'simple' *grin* */
/* glommed from Gudu and modified 4/2/93 */
/* update 12/10/93 */
 
#define ENTRY "/room/newroom/main10"
#define ENTRY_LONG "A winding path leads south through the trees...\n"
 
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
       ENTRY->add_exit("/players/slider/rooms/path1", "south");
    }
}
