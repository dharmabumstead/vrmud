main(arg) {
 object foo;
  if(!(foo=find_player(arg))) notify_fail("They aren't on right now.\n");
  foo->frog_curse(1);
  write(capitalize(foo->query_real_name())+" frogged.\n");
  return 1;
}
