#include <pebble.h>
#include <stdio.h>

  #include "menu.h"
  #include "splash.h"
  #include "confirm.h"
  #include "dog.h"
  
  /*
  Window *my_window;
TextLayer *text_layer;

uint8_t test_counter=1;
uint8_t elements[10] ={ 10,11,12,13,14,15,16,17,18,19};

static uint16_t menu_cb_get_num_rows (struct MenuLayer *menu_layer, uint16_t section_index, void *callback_context) {
  return 10;
}

static void menu_cb_draw_row (GContext *ctx, const Layer *cell_layer, MenuIndex *cell_index, void *callback_context) {
  char foo[10];
  snprintf(foo,10,"%d",elements[cell_index->row]);
  menu_cell_basic_draw(ctx, cell_layer, "FOo", foo, NULL);
}

static void menu_cb_select_click (struct MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context) {
  elements[cell_index->row]+=10;
  layer_mark_dirty(menu_layer_get_layer(menu_layer));
}



void handle_init(void) {
  my_window = window_create();

  text_layer = text_layer_create(GRect(0, 0, 144, 20));
  text_layer_set_text(text_layer, "PSI SPACER");
  
  
  MenuLayer* menu_layer = menu_layer_create(GRect(0,0,144,168));
  menu_layer_set_callbacks(menu_layer, NULL, (MenuLayerCallbacks) {
    .get_num_rows=menu_cb_get_num_rows,
    .draw_row=menu_cb_draw_row,
    .select_click=menu_cb_select_click
  });

  menu_layer_set_click_config_onto_window(menu_layer, my_window);
  layer_add_child(window_get_root_layer(my_window), menu_layer_get_layer(menu_layer));
  window_stack_push(my_window, true);
}
*/
  
  void handle_init(void) {
  
  menu_handle_init();
  splash_handle_init();
  confirm_handle_init();

  window_stack_push(menu_window,true);
  //window_stack_push(confirm_window,true);
  window_stack_push(splash_window,true);
  
}
  
void handle_deinit(void) {
  //text_layer_destroy(text_layer);
  //window_destroy(my_window);
    menu_handle_deinit();
    splash_handle_deinit();
    confirm_handle_deinit();
}

int main(void) {
  loadDogNames();
  handle_init();
  app_event_loop();
  handle_deinit();
}
