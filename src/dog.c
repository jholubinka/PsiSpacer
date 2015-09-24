#include <pebble.h>
#include "dog.h"

char* dogs[DOG_COUNT];
char* states[STATE_COUNT];

uint8_t currentState[DOG_COUNT];

char* getDogName(uint8_t dog_idx) {
  return dogs[dog_idx];
}

uint8_t getDogCount() {
  return DOG_COUNT;
}

char* getDogState(uint8_t dog_idx) {
  return states[currentState[dog_idx]];
}
uint8_t getDogStateRaw(uint8_t dog_idx) {
  return currentState[dog_idx];
}


void updateDogState(uint8_t dog_idx) {
  uint8_t newState = currentState[dog_idx];
  if (++newState >= STATE_COUNT) newState=0;
  currentState[dog_idx] = newState;
}

void resetDogStates() {
  uint8_t i;
  for(i=0; i<DOG_COUNT; i++) currentState[i]=0;
}


void loadDogNames() {
  dogs[0]="Desti";
  dogs[1]="Eksi";
  dogs[2]="Falka";
  
  currentState[0]=0;
  currentState[1]=0;
  currentState[2]=0;
  
  
  
  states[0]="Nic";
  states[1]="Sikała";
  states[2]="Robiła";
  states[3]="Komplet";
}

