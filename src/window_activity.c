#include "window_activity.h"
#include <pebble.h>
#include "utils.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GBitmap *s_res_resource_id_image_setup;
static GBitmap *s_res_resource_id_image_swim;
static GBitmap *s_res_resource_id_image_menu_line;
static GFont s_res_gothic_24_bold;
static GFont s_res_gothic_28_bold;
static GFont s_res_gothic_18_bold;
static ActionBarLayer *s_actionbarlayer;
static BitmapLayer *s_bitmaplayer_menu;
static TextLayer *s_textlayer_lap_text;
static TextLayer *s_textlayer_lap;
static TextLayer *s_textlayer_time_text;
static TextLayer *s_textlayer_dist_text;
static TextLayer *s_textlayer_time;
static TextLayer *s_textlayer_1;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, false);
  
  s_res_resource_id_image_setup = gbitmap_create_with_resource(RESOURCE_ID_RESOURCE_ID_IMAGE_SETUP);
  s_res_resource_id_image_swim = gbitmap_create_with_resource(RESOURCE_ID_RESOURCE_ID_IMAGE_SWIM);
  s_res_resource_id_image_menu_line = gbitmap_create_with_resource(RESOURCE_ID_RESOURCE_ID_IMAGE_MENU_LINE);
  s_res_gothic_24_bold = fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD);
  s_res_gothic_28_bold = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
  s_res_gothic_18_bold = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
  // s_actionbarlayer
  s_actionbarlayer = action_bar_layer_create();
  action_bar_layer_add_to_window(s_actionbarlayer, s_window);
  action_bar_layer_set_background_color(s_actionbarlayer, GColorBlack);
  action_bar_layer_set_icon(s_actionbarlayer, BUTTON_ID_UP, s_res_resource_id_image_setup);
  action_bar_layer_set_icon(s_actionbarlayer, BUTTON_ID_SELECT, s_res_resource_id_image_swim);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_actionbarlayer);
  
  // s_bitmaplayer_menu
  s_bitmaplayer_menu = bitmap_layer_create(GRect(0, 100, 124, 52));
  bitmap_layer_set_bitmap(s_bitmaplayer_menu, s_res_resource_id_image_menu_line);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_menu);
  
  // s_textlayer_lap_text
  s_textlayer_lap_text = text_layer_create(GRect(0, 20, 124, 24));
  text_layer_set_text(s_textlayer_lap_text, "LAP");
  text_layer_set_text_alignment(s_textlayer_lap_text, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_lap_text, s_res_gothic_24_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_lap_text);
  
  // s_textlayer_lap
  s_textlayer_lap = text_layer_create(GRect(0, 45, 124, 30));
  text_layer_set_text(s_textlayer_lap, "0");
  text_layer_set_text_alignment(s_textlayer_lap, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_lap, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_lap);
  
  // s_textlayer_time_text
  s_textlayer_time_text = text_layer_create(GRect(0, 101, 62, 20));
  text_layer_set_text(s_textlayer_time_text, "Time");
  text_layer_set_text_alignment(s_textlayer_time_text, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_time_text, s_res_gothic_18_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_time_text);
  
  // s_textlayer_dist_text
  s_textlayer_dist_text = text_layer_create(GRect(63, 101, 61, 20));
  text_layer_set_text(s_textlayer_dist_text, "Distance");
  text_layer_set_text_alignment(s_textlayer_dist_text, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_dist_text, s_res_gothic_18_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_dist_text);
  
  // s_textlayer_time
  s_textlayer_time = text_layer_create(GRect(0, 122, 62, 20));
  text_layer_set_text(s_textlayer_time, "00:00:00");
  text_layer_set_text_alignment(s_textlayer_time, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_time, s_res_gothic_18_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_time);
  
  // s_textlayer_1
  s_textlayer_1 = text_layer_create(GRect(63, 122, 61, 20));
  text_layer_set_text(s_textlayer_1, "0");
  text_layer_set_text_alignment(s_textlayer_1, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_1, s_res_gothic_18_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_1);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  action_bar_layer_destroy(s_actionbarlayer);
  bitmap_layer_destroy(s_bitmaplayer_menu);
  text_layer_destroy(s_textlayer_lap_text);
  text_layer_destroy(s_textlayer_lap);
  text_layer_destroy(s_textlayer_time_text);
  text_layer_destroy(s_textlayer_dist_text);
  text_layer_destroy(s_textlayer_time);
  text_layer_destroy(s_textlayer_1);
  gbitmap_destroy(s_res_resource_id_image_setup);
  gbitmap_destroy(s_res_resource_id_image_swim);
  gbitmap_destroy(s_res_resource_id_image_menu_line);
}
// END AUTO-GENERATED UI CODE

#define BUFFER_SIZE 32
  
static void start_activity(void);
static void pause_activity(void);
static void stop_activity(void);
static void access_settings(void);
static void reset_timer(void);
static void tick_handler(struct tm *tick_time, TimeUnits units_changed);
static void reset_timer(void);
static void reset_lap(void);

enum ActivityStatus {Started, Paused, Stopped};

static GBitmap *s_res_resource_id_image_pause;
static GBitmap *s_res_resource_id_image_stop;
static enum ActivityStatus activity_state = Stopped;
static int s_timer = 0;
static char s_timer_buffer[BUFFER_SIZE];

static void initialise_data(void) {
  s_res_resource_id_image_pause = gbitmap_create_with_resource(RESOURCE_ID_RESOURCE_ID_IMAGE_PAUSE);
  s_res_resource_id_image_stop = gbitmap_create_with_resource(RESOURCE_ID_RESOURCE_ID_IMAGE_STOP);
}

static void start_activity(void) {
  // Update activity state
  activity_state = Started;
  
  // Update icons in the actionBar
  action_bar_layer_set_icon(s_actionbarlayer, BUTTON_ID_SELECT, s_res_resource_id_image_pause);
  action_bar_layer_set_icon(s_actionbarlayer, BUTTON_ID_DOWN, s_res_resource_id_image_stop);
  
  // Register with TickTimerService
  tick_timer_service_subscribe(SECOND_UNIT, tick_handler);
}

static void pause_activity(void) {
  // Update activity state
  activity_state = Paused;
  
  // Update icons in the actionBar
  action_bar_layer_set_icon(s_actionbarlayer, BUTTON_ID_SELECT, s_res_resource_id_image_swim);
  action_bar_layer_set_icon(s_actionbarlayer, BUTTON_ID_DOWN, s_res_resource_id_image_stop);
  
  // Unregister with TickTimerService
  tick_timer_service_unsubscribe();
}

static void stop_activity(void) {
  // Update activity state
  activity_state = Stopped;
  
  // Update icons in the actionBar
  action_bar_layer_set_icon(s_actionbarlayer, BUTTON_ID_SELECT, s_res_resource_id_image_swim);
  action_bar_layer_clear_icon(s_actionbarlayer, BUTTON_ID_DOWN);
  
  // Reset lap, timer and distance
}

static void access_settings(void) {
  
}

static void reset_timer(void) {
  s_timer = 0;
  text_layer_set_text(s_textlayer_time, "00:00:00");
}

static void reset_lap(void) {
  s_lap = 0;
  text_layer_set_text(s_textlayer_lap, "0");
}

static void reset_distance(void) {
  s_distance = 0;
  text_layer_set_text(s_textlayer_lap, "0");
}

/******************************** Manage clicks *********************************/
static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (activity_state == Started) {
    pause_activity();
  }
  access_settings();
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (activity_state == Stopped || activity_state == Paused) {
    start_activity();
  } else if (activity_state == Started) {
    pause_activity();
  }
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (activity_state == Paused) {
    stop_activity();
  }
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}
/********************************************************************************/

/******************************** Manage timer **********************************/
static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  // Increment s_uptime
  s_timer++;
  
  // Get time since launch
  int seconds = s_timer % 60;
  int minutes = (s_timer % 3600) / 60;
  int hours = s_timer / 3600;
  
  // Format uptime to 00:00:00
  char *format = malloc(BUFFER_SIZE);
  format_uptime(&format, hours, minutes, seconds);
  
  // Update the TextLayer
  snprintf(s_timer_buffer, sizeof(s_timer_buffer), format, hours, minutes, seconds);
  text_layer_set_text(s_textlayer_time, s_timer_buffer);
  
  free(format);
}
/********************************************************************************/


static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_window_activity(void) {
  initialise_ui();
  initialise_data();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_set_click_config_provider(s_window, click_config_provider);
  window_stack_push(s_window, true);
}

void hide_window_activity(void) {
  window_stack_remove(s_window, true);
}
