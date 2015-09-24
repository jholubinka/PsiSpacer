#include <pebble.h>
#include "confirm.h"
#include "dog.h"

#define TIMEOUT 2500
  
Window *confirm_window;
TextLayer *text_layer;
ActionBarLayer *ab_layer;

static GBitmap *icon_check;
static GBitmap *icon_cross;

static void confirm_cb_timeout(void) {
  window_stack_pop_all(true);
}

static void confirm_cb_timeout2(void) {
  window_stack_pop(true);
}


static void confirm_up_handler(ClickRecognizerRef recognizer, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG,"Nacisnales up, trzeba cos tu zrobic z tym!");
 
  DictionaryIterator *iterator;
  app_message_outbox_begin(&iterator);
  uint8_t i;
  for(i=0; i<DOG_COUNT; i++) {
      dict_write_uint8(iterator, i, getDogStateRaw(i));
  }
  

  dict_write_end(iterator); 
  app_message_outbox_send();
  
}
static void confirm_down_handler(ClickRecognizerRef recognizer, void *context) {
  window_stack_pop_all(true);
}

static void click_config_provider(void *context) {
  // Register the ClickHandlers
  window_single_click_subscribe(BUTTON_ID_UP, confirm_up_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, confirm_down_handler);
}


static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Message received!");
  // Get the first pair
  Tuple *t = dict_read_first(iterator);

  // Process all pairs present
  while(t != NULL) {
    // Process this pair's key
    switch (t->key) {
      case 99:
        APP_LOG(APP_LOG_LEVEL_INFO, "KEY_DATA received with value %s", (char*)t->value->cstring);
        text_layer_set_text(text_layer, (char*)t->value->cstring);
        app_timer_register(TIMEOUT, (AppTimerCallback)confirm_cb_timeout, NULL);
        break;
    }

    // Get next pair, if any
    t = dict_read_next(iterator);
  }
}

static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
  text_layer_set_text(text_layer, "Błąd zapisu\n1");
  vibes_long_pulse();
  app_timer_register(TIMEOUT, (AppTimerCallback)confirm_cb_timeout2, NULL);
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
  text_layer_set_text(text_layer, "Błąd zapisu\n2");
  vibes_long_pulse();
  app_timer_register(TIMEOUT, (AppTimerCallback)confirm_cb_timeout2, NULL);
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
  text_layer_set_text(text_layer, "...");
}





void confirm_handle_init(void) {
  confirm_window = window_create();
  
  GRect gr= GRect(0, 0, 114, 60);
  GRect win = GRect(0,0,114,168);
  
  grect_align(&gr, &win, GAlignCenter, false);
  window_set_background_color(confirm_window, GColorBrightGreen);
  //text_layer = text_layer_create(GRect(0, 10, 144, 168));
  text_layer = text_layer_create(gr);
  text_layer_set_text_alignment(text_layer,  GTextAlignmentCenter);
  text_layer_set_background_color(text_layer,GColorClear);
  text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_text(text_layer, "Czy zapisać zmiany?");
  
  
  icon_check = gbitmap_create_with_resource(RESOURCE_ID_ICON_CHECK);
  icon_cross = gbitmap_create_with_resource(RESOURCE_ID_ICON_CROSS);
  
  
  ab_layer = action_bar_layer_create();
  action_bar_layer_set_icon(ab_layer, BUTTON_ID_UP, icon_check);
  action_bar_layer_set_icon(ab_layer, BUTTON_ID_DOWN, icon_cross);
  
  action_bar_layer_add_to_window(ab_layer, confirm_window);

  layer_add_child(window_get_root_layer(confirm_window), text_layer_get_layer(text_layer));
  //window_set_click_config_provider(confirm_window, click_config_provider);
  action_bar_layer_set_click_config_provider(ab_layer, click_config_provider);
  
  
  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);
  
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
  
}



void confirm_handle_deinit(void) {
  text_layer_destroy(text_layer);
  action_bar_layer_destroy(ab_layer);
  window_destroy(confirm_window);
  gbitmap_destroy(icon_check);
  gbitmap_destroy(icon_cross);
}
