#include <pebble.h>
#include "window_activity.h"
#include "window_compass.h"

void compass_callback(CompassHeadingData heading) {
  if (heading.compass_status != CompassStatusDataInvalid) {
    update_compass(TRIGANGLE_TO_DEG(TRIG_MAX_ANGLE - heading.true_heading));
  } else {
    // Heading not available yet - Show calibration UI to user.
    update_compass(666);
  }
}
  
static void init(void) {
  //compass_service_subscribe(compass_callback);
  //show_window_compass();
  show_window_activity();
}

static void deinit(void) {
  compass_service_unsubscribe();
  //hide_window_compass();
  hide_window_activity();
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}