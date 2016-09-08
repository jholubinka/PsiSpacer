#pragma once
#include <pebble.h>
  
  void menu_handle_init(void);
  void menu_handle_deinit(void);

void force_back_button(Window *window, MenuLayer *menu_layer);

Window *menu_window;