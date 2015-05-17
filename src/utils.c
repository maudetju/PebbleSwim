#include <pebble.h>
#include "utils.h"

// Format uptime to 00:00:00
void format_uptime(char **format, int hours, int minutes, int seconds) {
  strcpy(*format,  "");
  
  if (hours < 10) {
    strcat(*format, "0%d:");
  } else {
    strcat(*format, "%d:");
  }
  if (minutes < 10) {
    strcat(*format, "0%d:");
  } else {
    strcat(*format, "%d:");
  }
  if (seconds < 10) {
    strcat(*format, "0%d");
  } else {
    strcat(*format, "%d");
  }
}

// Show float NOT TESTED
void ftoa(char* str, double val, int precision) {
  //  start with positive/negative
  if (val < 0) {
    *(str++) = '-';
    val = -val;
  }
  //  integer value
  snprintf(str, 12, "%d", (int) val);
  str += strlen(str);
  val -= (int) val;
  //  decimals
  if ((precision > 0) && (val >= .00001)) {
    //  add period
    *(str++) = '.';
    //  loop through precision
    for (int i = 0;  i < precision;  i++)
      if (val > 0) {
        val *= 10;
        *(str++) = '0' + (int) (val + ((i == precision - 1) ? .5 : 0));
        val -= (int) val;
      } else
        break;
  }
  //  terminate
  *str = '\0';
}