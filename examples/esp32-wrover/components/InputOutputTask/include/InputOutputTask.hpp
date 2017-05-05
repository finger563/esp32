#ifndef __InputOutputTask__INCLUDE_GUARD
#define __InputOutputTask__INCLUDE_GUARD

#include <cstdint>

// Task Includes
#include "driver/gpio.h" // needed for button and LED
#include "SerialTask.hpp" // needed for SerialTask::changeState

// Generated state functions and members for the task
namespace InputOutputTask {

  // Task Forward Declarations
  extern gpio_num_t rPin;
  extern gpio_num_t gPin;
  extern gpio_num_t bPin;
  extern bool       ledOn;

  extern bool       changeState;

  // Generated task function
  void  taskFunction ( void *pvParameter );

  // Generated state functions
  void  state_Cycle_RGB_execute      ( void );
  void  state_Cycle_RGB_setState     ( void );
  void  state_Cycle_RGB_transition   ( void );
  void  state_Cycle_RGB_finalization ( void );
  void  state_Cycle_RGB_Flash_Green_execute      ( void );
  void  state_Cycle_RGB_Flash_Green_setState     ( void );
  void  state_Cycle_RGB_Flash_Green_transition   ( void );
  void  state_Cycle_RGB_Flash_Green_finalization ( void );
  void  state_Cycle_RGB_Flash_Blue_execute      ( void );
  void  state_Cycle_RGB_Flash_Blue_setState     ( void );
  void  state_Cycle_RGB_Flash_Blue_transition   ( void );
  void  state_Cycle_RGB_Flash_Blue_finalization ( void );
  void  state_Cycle_RGB_Flash_Red_execute      ( void );
  void  state_Cycle_RGB_Flash_Red_setState     ( void );
  void  state_Cycle_RGB_Flash_Red_transition   ( void );
  void  state_Cycle_RGB_Flash_Red_finalization ( void );
  void  state_Flash_All_RGB_execute      ( void );
  void  state_Flash_All_RGB_setState     ( void );
  void  state_Flash_All_RGB_transition   ( void );
  void  state_Flash_All_RGB_finalization ( void );

};

#endif // __InputOutputTask__INCLUDE_GUARD
