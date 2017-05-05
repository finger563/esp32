#include "Component.hpp"
uint32_t testFunc(void *pvParameters) {
  myClass mc;
  return mc.getIntFromPtr(pvParameters);
}

uint32_t myClass::getIntFromPtr( void *ptr ) {
  test++;
  return (uint32_t)ptr;
}