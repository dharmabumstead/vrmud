// Quick IP lookup by Slider

main (string str)
{
   string foo;
   mixed * nowtime;
 
   nowtime = localtime(time());
 
 
   sprintf(foo, "%02d/%02d/%04d %02d:%02d%02d", 
            nowtime(LT_MON), nowtime(LT_MDAY), nowtime(LT_YEAR),
            nowtime(LT_HOUR), nowtime(LT_MIN), nowtime(LT_SEC));
 
   printf("Result: %s", foo);
   int x;
   string new_hd;
    new_hd = new_hd + "(" + capitalize(this_player()->query_real_name()) +
      ", " + ctime(time()) + ")";
   printf("%s\n", new_hd);

   if(!str) {
      printf("Usage: lookup <ip address>\n");
	  return(1);
	    }

   x = resolve(str, "lookup_resolve");

}

void lookup_resolve(string address, string resolved, int key)
{
   printf("The IP address '%s' resolves to '%s'.\n", address, resolved);
}
