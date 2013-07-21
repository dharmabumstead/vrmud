// ed by Gudu 4/2/93
// slight modifications - Artagel 11-11-93
   
int main( string file) {
   
   object user;
   string err;
   int test;
   
   user = this_player();
   
   if( !wizardp( user))
      return 0;
   
   seteuid( getuid( previous_object()));
   file = resolv_path( user->query_current_path(), file);
   
#ifdef MUDOS
   test = (int)master()->valid_write(file, user, "ed");
   write("Editing: " + file);
   if(test)
      write("\n");
   else
      write(" [read only]\n");
#endif

   ed( file);
   
   user->set_last_file(file);
   return 1;
}

