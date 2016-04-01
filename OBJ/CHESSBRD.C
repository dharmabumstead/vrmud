/***************************************************************************
 * NAME:
 *    chessbrd.c
 * DESCRIPTION:
 *    Slider's Chess Object
 * VERSION:
 *    0.8
 * ENVIRONMENT:
 *    Virtual Realities - LPMud 3.1.2-DR
 * UPDATE HISTORY
 *   05/08/93  Slider  Initial version
 *   09/12/93  Slider  Board display; moves; takeback
 *   09/14/93  Slider  Changed 'new' to 'reset board'
 *   11/07/93  Slider  Added piece addition/removal to board
 ***************************************************************************/
#define LOG_NAME "slider.chess"
#include "/players/slider/include/slider.h"
inherit "std/move";
 
string *board;
string separator;
string short_desc;
string long_desc;
int y1, x1, y2, x2;
string oldpiece;
 
create() {
   int counter;
   board = allocate(8);
 
   for(counter=0;counter<8;counter++)
      board[counter] = allocate(8);
 
   separator = "  +---+---+---+---+---+---+---+---+";
   reset_board();
   set_short("A chess board");
   set_long("Slider's Chess Board.  Type 'help chess' for instructions.\n");
}
 
id(str)
{
   return((str=="board")||(str=="chessboard")||(str=="chess"));
}
 
short()
{
   return short_desc;
}
 
long()
{
   write(long_desc);
}
 
get() { return 0; }
 
drop() { return 0; }
 
init() {
   /* Add our commands */
   add_action("help_board", "help");
   add_action("new_game", "reset");
   add_action("show_board", "show");
   add_action("move_piece", "chess");
   add_action("resign_game", "resign");
   add_action("take_back", "back");
   add_action("add_piece", "add");
   add_action("remove_piece", "remove");
}
 
new_game(str)
{
   if(id(str)) {
     write("You reset the chess board.\n");
     say(capitalize(this_player()->query_real_name()) + " resets the board.\n");
     reset_board();
     show_board();
     return(1);
   }
   return(0);
}
 
help_board(str)
{
   if(id(str))
   {
      write(
"This is Slider's Chess Board, version 0.8.  Here's how it works:\n"+
"    White pieces are capital letters.  Black pieces are lowercase.\n"+
"    To move, type 'chess y1 x1 y2 x2'  (y is vertical, x is horizontal)\n"+
"       where y1 is a number from 0 to 7 for the y axis of the piece,\n"+
"       x1 is a number from 0 to 7 for the x axis of the piece to move,\n"+
"       and y2 and x2 are the y and x positions of the destination square.\n"+
"       NO COMMAS or anything! Here's an example: chess 6 0 4 0\n"+
"    To display the board, type 'show board' or 'show chess'\n"+
"    To take back the last move, type 'back'\n"+
"    To start a new game, type 'reset board' or 'reset chess'\n"+
"    To add/change a piece, type 'add y1 x1 piece'\n"+
"    To remove a piece, type 'remove y1 x1'\n"+
"    You can refer to the chessboard as 'chess', 'board', or 'chessboard'\n"+
"This is a preliminary version!  It doesn't yet check for legal moves, so\n"+
"play it with someone you can trust in the meantime!  Have fun!  And please\n"+
"send suggestions to me!\n");
   }
   return(1);
}
 
remove_piece(str)
{
        string piece;
 
   sscanf(str, "%d %d", y1, x1);
 
   if((y1<0)||(x1<0)) {
      write("That's not a valid position!\n");
      return(1);
   }
 
   board[y1][x1] = " ";
 
   say(capitalize(this_player()->query_real_name()) +
      " removes piece from "+y1+","+x1+"\n");
 
   write("You remove a piece from " +y1+","+x1+"\n");
 
   show_board();
   return(1);
}
 
add_piece(str)
{
        string piece;
 
   sscanf(str, "%d %d %s", y1, x1, piece);
 
   if((y1<0)||(x1<0)) {
      write("That's not a valid position!\n");
      return(1);
   }
 
   board[y1][x1] = piece;
 
   say(capitalize(this_player()->query_real_name()) +
      " adds " + piece+ " to the chess board at "+y1+","+x1+"\n");
 
   write("You add: "+piece+" at " +y1+","+x1+"\n");
 
   show_board();
   return(1);
}
 
show_board() {
   int x,y;
 
   say(capitalize(this_player()->query_real_name()) +
      " ponders the chess board.\n");
 
   write(" ");
   for(x=0;x<8;x++)
      write("   " + x);
   write("\n");
 
   for(y=0;y<8;y++) {
      write(separator + "\n");
      write(y);
      for(x=0;x<8;x++) {
         write(" | " + board[y][x]);
      }
      write(" | " + y + "\n");
   }
   write(separator + "\n ");
   for(x=0;x<8;x++)
      write("   " + x);
   write("\n");
   return(1);
}
 
move_piece(str)
{
   sscanf(str, "%d %d %d %d", y1, x1, y2, x2);
 
   if((y1<0)||(y2<0)||(x1<0)||(x2<0)) {
      write("That's not a valid move!\n");
      return(1);
   }
 
   if((y1>7)||(y2>7)||(x1>7)||(x2>7)) {
      write("That's not a valid move!\n");
      return(1);
   }
 
   if(board[y1][x1] == " ") {
      write("There's no piece there to move!\n");
      return(1);
   }
 
   oldpiece = board[y2][x2];
   board[y2][x2] = board[y1][x1];
   board[y1][x1] = " ";
 
   say(capitalize(this_player()->query_real_name()) +
      " makes a move on the chess board: "+y1+","+x1+" to "+y2+","+x2);
 
   write("You move: "+y1+","+x1+" to "+y2+","+x2);
 
   if(oldpiece != " ") {
      say(" ("+board[y2][x2] + "x"+oldpiece+")\n");
      write(" ("+board[y2][x2] + "x"+oldpiece+")\n");
   } else {
      say("\n");
      write("\n");
   }
 
   show_board();
   return(1);
}
 
take_back()
{
   say(capitalize(this_player()->query_real_name()) +
      " takes back the last move on the chess board.\n");
   board[y1][x1] = board[y2][x2];
   board[y2][x2] = oldpiece;
   show_board();
   return(1);
}
 
reset_board() {
   int t, x, y;
 
 
   board[0][0] = "r";
   board[0][1] = "n";
   board[0][2] = "b";
   board[0][3] = "q";
   board[0][4] = "k";
   board[0][5] = "b";
   board[0][6] = "n";
   board[0][7] = "r";
 
   for(t=0;t<8;t++)
      board[1][t] = "p";
 
   board[7][0] = "R";
   board[7][1] = "N";
   board[7][2] = "B";
   board[7][3] = "Q";
   board[7][4] = "K";
   board[7][5] = "B";
   board[7][6] = "N";
   board[7][7] = "R";
 
   for(t=0;t<8;t++)
      board[6][t] = "P";
 
   for(y=2;y<6;y++) {
      for(x=0;x<8;x++)
         board[y][x] = " ";
   }
   return(1);
}
 
set_short(str) {
   short_desc = str;
}
 
set_long(str) {
   long_desc = str;
}
