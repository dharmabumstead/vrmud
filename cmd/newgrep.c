inherit "/std/move";
/* grepper by Lleldorin - 16/04/92 */
/* please retain these comments */

// Ported to MudOS by Gudu 12/06/93

// Slider added 'more' support 2/14/96

#define QL this_player()->query_level()
 
#define SIZE 100
int matched, moreflag;
string *output;
 
main( str) {

    string exp,file, morearg;
    string path,dummy;
    string *files;
    int i;

	output=allocate(0);
 
    if ((!str) || ((sscanf(str,"%s %s %s",exp,file,morearg)!=3) &&
	    (sscanf(str,"%s %s", exp,file)!=2))) {
	notify_fail("Usage: grep <string expression> <file> [-m(ore)]\n");
        return 0;
    }

	if ((morearg == "-m") || (morearg == "-M"))
		moreflag = 1;
	else
		moreflag = 0;
    
    file = "/"+resolve_path( this_player()->query_current_path(), file);

    if (sscanf(file,"%s*%s",path,dummy)>=1) {
        files=get_dir(file);
        if (!files) {
            write("No such file(s).\n");
            return 1;
        }
        for (i=0;i<sizeof(files);i++) {
	    if( files[i] == "." || files[i] == "..")
		continue;
            grep_it(path+files[i],exp);
        }
        return 1;
    }
    grep_it(file,exp);

    seteuid( getuid());
    return 1;
}
 
grep_it(string file,string exp) {

    int current_line;
    string lines;
 
    current_line=0;
    matched=0;
    while((lines=read_file(file,current_line,SIZE))!=0) {
        grep_string(lines,exp,file);
        current_line+=SIZE;
    }
    if (current_line==0)	
        write("File(s) not found.\n");
	else
		if(moreflag == 1)
			more(implode(output, ""));

    return 1;
}
 
grep_string(string lines,string exp, string file) {
string *lines_array;
string *matched_arr;
int i, z;
 
    lines_array=explode(lines,"\n");

    matched_arr=regexp(lines_array,exp);

	z = 0;
    
	if (!matched_arr)
        return;

	if(moreflag == 0) {
    	for (i=0;i<sizeof(matched_arr);i++)
        	printf("%s:%s\n", file, matched_arr[i]);
	} else {
    	for (i=0;i<sizeof(matched_arr);i++) {
		   output += ({sprintf("%s:%s\n", file, matched_arr[i])});
		}
	}

    matched+=sizeof(matched_arr);
	return(1);
}
 
