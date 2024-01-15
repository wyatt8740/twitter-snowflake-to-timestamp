#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "arg_parsing.h"
#include "tweet_timestamp_common.h"

long long int timecalc(long long int tid);

/* only for "snowflake" tweet ID's */
extern int use_unix_time;

int main(int argc, char **argv) {
  int arg_scan_cursor=1;
  while(arg_scan_cursor > -1) {
    arg_scan_cursor=scan_for_dash_flag(argc, argv, arg_scan_cursor);
    if( arg_scan_cursor > -1  && strlen(argv[arg_scan_cursor]) >= 1)
        switch(argv[arg_scan_cursor][1]) {
        case 'u':
          /* print unix time in seconds */
          use_unix_time=1;
          break;
        case 's':
          /* print a formatted string for time */
          use_unix_time=0;
          break;
        default:
          fprintf(stderr, "Warning: unknown argument `%s' passed\n",argv[arg_scan_cursor]);
          break;
        }
    arg_scan_cursor++;
  }
  
  int i=1;
  if(argc > 1) {
    /* if -u is first argument, output unix timestamps instead of formatted */
    long long int timestamp;
    time_t seconds;
    struct tm epoch_time;
    /* I think 80 chars is long enough for most any timestamp in this format */
    char buf[80];
    while(i < argc) {
      timestamp=parse_arg(argv[i]);
      if(timestamp > -1) {
        /* possible truncation here!! - converting long long int to time_t */
        seconds=(int)timecalc(timestamp);

        if( use_unix_time ) {
          printf("%lld\n",(long long int)seconds);
        }
        else {
          memcpy(&epoch_time, gmtime(&seconds), sizeof(struct tm));
          /* strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", &epoch_time);*/
          strftime(buf, sizeof(buf), "%Y%m%d_%H%M%S", &epoch_time);

          /* printf("%s (%d)\n",buf, timecalc(timestamp));*/
          printf("%s\n",buf);
        }
      }
        i++;
    }
  }
}

long long int div_round_closest(const long long int n, const long long int d)
{
  return ((n < 0ll) == (d < 0ll)) ? ((n + d/2ll)/d) : ((n - d/2ll)/d);
}

/* convert snowflake ID to Unix timestamp */
long long int timecalc(long long int tid) {
  /* note that we lose granularity (and precision) here, because unix
     timestamps are only accurate to the second (but snowflakes
     are accurate to the millisecond). That's what the '/1000' is doing. */
  /* return div_round_closest((tid >> 22ll),1000ll) + 1288834974ll; */
  return (tid >> 22ll)/1000ll + 1288834974ll;
}

