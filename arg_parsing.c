#include <stdlib.h>

long long int parse_arg(char *arg){
  if(arg[0]=='-'){
    /* don't convert to a date (skip) */
    return -1;
  }
  return atoll(arg);
}

int scan_for_dash_flag(int argc, char **argv, int i){
  /* returns next argument containing a '-', or negative number if reached end of argument
     list.
     'i' is the index to start our search from.
  */
  
  int found_index=-2;
  while( (found_index < 0) && (i < argc) ) {
    if(argv[i][0] == '-') {
      found_index=i;
    }
    i++;
  }
  /* note: to resume search with another call, be sure i is incremented by one
     from found_index. */
  return found_index;
}
