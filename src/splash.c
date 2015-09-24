#include <pebble.h>
#include "splash.h"



Window *splash_window;
TextLayer *text_layer;
static GBitmap *icon_poo;
BitmapLayer *bitmap_layer;

void splash_cb_timeout(void) {
  //indow_stack_pop(true);
  window_stack_remove(splash_window, true);
  
}


void splash_handle_init(void) {
  splash_window = window_create();
  
  GRect gr= GRect(0, 0, 168, 70);
  GRect win = GRect(0,0,144,168);
  
  grect_align(&gr, &win, GAlignCenter, false);
  window_set_background_color(splash_window, GColorOrange);
  //text_layer = text_layer_create(GRect(0, 10, 144, 168));
  text_layer = text_layer_create(gr);
  text_layer_set_text_alignment(text_layer,  GTextAlignmentCenter);
  text_layer_set_background_color(text_layer,GColorClear);
  text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
  text_layer_set_text(text_layer, "Psi\nSpacer");
  
  GRect poo=GRect(0,0,28,28);
  grect_align(&poo, &win, GAlignBottom, false);
  icon_poo = gbitmap_create_with_resource(RESOURCE_ID_ICON_POO3);
  bitmap_layer = bitmap_layer_create(poo);
  bitmap_layer_set_bitmap(bitmap_layer, icon_poo);
  
  
  
  app_timer_register(3000, (AppTimerCallback)splash_cb_timeout, NULL);

  layer_add_child(window_get_root_layer(splash_window), text_layer_get_layer(text_layer));
  layer_add_child(window_get_root_layer(splash_window), bitmap_layer_get_layer(bitmap_layer));
  //window_stack_push(my_window, true);
}



void splash_handle_deinit(void) {
  text_layer_destroy(text_layer);
  window_destroy(splash_window);
}
