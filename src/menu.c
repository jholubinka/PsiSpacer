#include <pebble.h>
#include "menu.h"
#include "confirm.h"
#include "dog.h"

Window *menu_window;
TextLayer *text_layer;

uint8_t test_counter=1;
uint8_t elements[10] ={ 10,11,12,13,14,15,16,17,18,19};

static uint16_t menu_cb_get_num_rows (struct MenuLayer *menu_layer, uint16_t section_index, void *callback_context) {
  return getDogCount();
}

static void menu_cb_draw_row (GContext *ctx, const Layer *cell_layer, MenuIndex *cell_index, void *callback_context) {
  //snprintf(foo,10,"%d",elements[cell_index->row]);
  menu_cell_basic_draw(ctx, cell_layer, getDogName(cell_index->row), getDogState(cell_index->row), NULL);
}

static void menu_cb_select_click (struct MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context) {
  //elements[cell_index->row]+=10;
  updateDogState(cell_index->row);
  layer_mark_dirty(menu_layer_get_layer(menu_layer));
}

static void menu_cb_select_long_click (struct MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context) {
  //elements[cell_index->row]+=10;
  resetDogStates();
  layer_mark_dirty(menu_layer_get_layer(menu_layer));
}


void menu_handle_init(void) {
  menu_window = window_create();

  text_layer = text_layer_create(GRect(0, 0, 144, 20));
  text_layer_set_text(text_layer, "PSI SPACER");
  
  
  MenuLayer* menu_layer = menu_layer_create(GRect(0,0,144,168));
  menu_layer_set_callbacks(menu_layer, NULL, (MenuLayerCallbacks) {
    .get_num_rows=menu_cb_get_num_rows,
    .draw_row=menu_cb_draw_row,
    .select_click=menu_cb_select_click,
    .select_long_click=menu_cb_select_long_click
  });

  menu_layer_set_normal_colors(menu_layer, GColorBlack, GColorWhite);
  menu_layer_set_highlight_colors(menu_layer, GColorYellow, GColorBlack);
  
  menu_layer_set_click_config_onto_window(menu_layer, menu_window);
  force_back_button(menu_window, menu_layer);
  layer_add_child(window_get_root_layer(menu_window), menu_layer_get_layer(menu_layer));
  
  
  //window_stack_push(my_window, true);
}



void menu_handle_deinit(void) {
  text_layer_destroy(text_layer);
  window_destroy(menu_window);
}



/* based on https://gist.github.com/sarfata/10574031 */

void back_button_handler(ClickRecognizerRef recognizer, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "back clicked");
  window_stack_push(confirm_window, true);
}

// We need to save a reference to the ClickConfigProvider originally set by the menu layer
ClickConfigProvider previous_ccp;

// This is the new ClickConfigProvider we will set, it just calls the old one and then subscribe
// for back button events.
void new_ccp(void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "calling the new ccp");
  previous_ccp(context);
  window_single_click_subscribe(BUTTON_ID_BACK, back_button_handler);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "done in the new ccp");
}

// Call this from your init function to do the hack
void force_back_button(Window *window, MenuLayer *menu_layer) {
  previous_ccp = window_get_click_config_provider(window);
  window_set_click_config_provider_with_context(window, new_ccp, menu_layer);
}