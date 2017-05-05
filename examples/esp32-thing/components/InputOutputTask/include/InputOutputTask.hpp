#ifndef __InputOutputTask__INCLUDE_GUARD
#define __InputOutputTask__INCLUDE_GUARD

#include <cstdint>

// Task Includes
#include "driver/gpio.h" // needed for button and LED

// Generated state functions and members for the task
namespace InputOutputTask {

  // Task Forward Declarations
  extern gpio_num_t ledPin;
  extern bool       ledOn;
  extern gpio_num_t buttonPin;
  extern bool       buttonPressed;

  // Generated task function
  void  taskFunction ( void *pvParameter );

  // Generated state functions
  void  state_State_2_execute      ( void );
  void  state_State_2_setState     ( void );
  void  state_State_2_transition   ( void );
  void  state_State_2_finalization ( void );
  void  state_State_2_State_execute      ( void );
  void  state_State_2_State_setState     ( void );
  void  state_State_2_State_transition   ( void );
  void  state_State_2_State_finalization ( void );
  void  state_State_1_execute      ( void );
  void  state_State_1_setState     ( void );
  void  state_State_1_transition   ( void );
  void  state_State_1_finalization ( void );

};

#endif // __InputOutputTask__INCLUDE_GUARD
