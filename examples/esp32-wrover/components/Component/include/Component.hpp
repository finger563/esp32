#ifndef COMPONENT_INCLUDE_GUARD_
#define COMPONENT_INCLUDE_GUARD_
#include <cstdint>

uint32_t testFunc(void *pvParameters);

class myClass {
  public:
  myClass() { test = 0; }
  ~myClass() {}

  uint32_t getIntFromPtr(void *ptr);
  
  private:
  int test;
};
#endif //COMPONENT_INCLUDE_GUARD_