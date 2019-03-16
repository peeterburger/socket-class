#include <stdio.h>
#include <time.h>

time_t t;
struct tm *p;
char formated_date[100];

void log_status(const char *prefix, const char *msg)
{
  t = time(NULL);
  p = localtime(&t);
  strftime(formated_date, 100, "%H:%M:%S", p);
  printf("[STATUS@%s][%s]\t->\t%s\n", formated_date, prefix, msg);
}