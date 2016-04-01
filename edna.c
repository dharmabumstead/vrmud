// ed by Gudu 4/2/93
// slight modifications - Artagel 11-11-93
// Llel 10/96 - fixed for "ed here"
#define LOG_NAME "ZZ_EDIT"
   
int main( string file) {
   
   object user;
    object env;
   string err;
   int test;
   
   user = this_player();
   
   if( !wizardp( user))
      return 0;
   
   seteuid( getuid( previous_object()));
    if (file=="here") {
	env=environment(user);
	if (!env)
		return 0;
	file=file_name(env)+".c";
    }
    else
   file = resolv_path( user->query_current_path(), file);
   
#ifdef MUDOS
   test = (int)master()->valid_write(file, user, "ed");
   write("Editing: " + file);
   if(test)
      write("\n");
   else
      write(" [read only]\n");
#endif

// large files are crashing the mud, thus this fix
   if(file_size(file)>1000000) {
	write("File size too large.\n");
	return 1;
   }

   ed( file);
   
   user->set_last_file(file);
   log_file(LOG_NAME,ctime()+" "+capitalize(this_player()->query_real_name())+
     " edited file " + file + "\n");
   return 1;
}

