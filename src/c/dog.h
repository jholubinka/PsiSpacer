#pragma once
#include <pebble.h>
  
#define DOG_COUNT 3
#define STATE_COUNT 4
  
  
char* getDogName(uint8_t dog_idx);
char* getDogState(uint8_t dog_idx);
void updateDogState(uint8_t dog_idx);
void resetDogStates();
uint8_t getDogCount() ;
uint8_t getDogStateRaw(uint8_t dog_idx);
void loadDogNames();