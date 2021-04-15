#include "utils.h"

char * timestampToText(int epoch, char *buff){
  struct tm *ts;
  time_t time;
  //char buff[256];
  time = epoch;
  ts = localtime(&time);
  strftime(buff, 256, "%a %b %d %H:%M:%S %Y", ts);
  return buff;
}
