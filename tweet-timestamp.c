#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
long long int timecalc(long long int tid);

/* only for "snowflake" tweet ID's */

int main(int argc, char **argv) {
  if(argc > 1) {
    int i=1;
    long long int timestamp;
    time_t seconds;
    struct tm epoch_time;
    char buf[80];
    while(i < argc) {
      timestamp=atoll(argv[i]);
      seconds=(int)timecalc(timestamp);
      memcpy(&epoch_time, gmtime(&seconds), sizeof(struct tm));
      /* strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", &epoch_time);*/
      strftime(buf, sizeof(buf), "%Y%m%d_%H%M%S", &epoch_time);
      
      /* printf("%s (%d)\n",buf, timecalc(timestamp));*/
      printf("%s\n",buf);
      i++;
    }
  }
}

/* convert snowflake ID to Unix timestamp */
long long int timecalc(long long int tid) {
  return (tid >> 22ll)/1000ll + 1288834974ll;
}

