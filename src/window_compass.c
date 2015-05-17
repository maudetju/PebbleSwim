#include "window_compass.h"
#include <pebble.h>
  
#define BUFFER_SIZE 32  

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_28_bold;
static TextLayer *s_textlayer_1;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, false);
  
  s_res_gothic_28_bold = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
  // s_textlayer_1
  s_textlayer_1 = text_layer_create(GRect(20, 58, 100, 28));
  text_layer_set_text(s_textlayer_1, "0");
  text_layer_set_text_alignment(s_textlayer_1, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_1, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_1);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_textlayer_1);
}
// END AUTO-GENERATED UI CODE

static char s_compass_buffer[BUFFER_SIZE];

void update_compass(long heading){
  snprintf(s_compass_buffer, sizeof(s_compass_buffer), "%ld", heading);
  text_layer_set_text(s_textlayer_1, s_compass_buffer);
}

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_window_compass(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_window_compass(void) {
  window_stack_remove(s_window, true);
}
