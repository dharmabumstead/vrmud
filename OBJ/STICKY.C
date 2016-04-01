inherit "/std/move";
/**************************************************************************
 * NAME:
 *    sticky.c
 * DESCRIPTION:
 *    Slider's Magic Sticky Note
 * VERSION:
 *    1.0
 * ENVIRONMENT:
 *    End Of The Line - LPMud 3.1.2-DR
 * UPDATE HISTORY
 *    01/19/93  Slider  Initial version
 *    03/30/93  Slider  Changed 'write' to 'note' and added erase feature
 *    04/04/93  Slider  Changed 'note' back to 'write' to avoid conflict
 *                      with bulletin board objects
 *    11/07/93  Slider  Minor update
 ***************************************************************************/
 
id(str) { return ((str== "note") || (str=="sticky note")); }
 
static string note_text; /* Note contents */
string short_desc;
 
short() { return short_desc; }
 
long() {
  write(
"This is Slider's Magic Sticky note.  Use 'write <text>' to write on it.\n");
  return 1;
}
 
create()  {
   note_text = "This note intentionally left blank!";
   set_short("a sticky note that says '" + note_text + "'");
}
 
get() { return 1; }
 
drop() { return 0; }
 
init() {
   /* Add our commands */
   add_action("write_note", "write");
}
 
 
write_note(string text) {
   /* Make sure we set the text only on the note we're holding
    * in case there are multiple notes in the room.         */
   if (environment(this_object()) == this_player())
   {
 
      if(!text) {
        note_text = "This note intentionally left blank!";
        set_short("a sticky note that says '" + note_text + "'");
        /* Write player's message */
        write("You erase the sticky note.\n");
 
        /* Write player's environment message */
        say(this_player()->query_name()+" erases a sticky note.\n");
        return 1;
      }
 
      note_text = text;
 
      set_short("a sticky note that says '" + note_text + "'");
 
      /* Write player's message */
      write("You scribble on the note.  It now reads:\n"+
            "'" + note_text + "'\n");
 
      /* Write player's environment message */
      say(this_player()->query_name()+" scribbles something on a sticky"+
          " note.\n");
 
      return(1);
   } else {
      return(0);
   }
}
 
set_short(str) {
  short_desc=str;
}
 
query_value()
{
   return(5);
}
 
