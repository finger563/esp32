#include "SerialTask.hpp"
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define MS_TO_TICKS( xTimeInMs ) (uint32_t)( ( ( TickType_t ) xTimeInMs * configTICK_RATE_HZ ) / ( TickType_t ) 1000 )

namespace SerialTask {

  // User definitions for the task


  // Generated state variables
  bool     __change_state__ = false;
  uint32_t __state_delay__ = 0;
  uint8_t  stateLevel_0;
  uint8_t  stateLevel_1;

  // Generated task function
  void taskFunction ( void *pvParameter ) {
    // initialize here
    __change_state__ = false;
    __state_delay__ = 1000;
    state_State_1_setState();
    // execute the init transition for the initial state and task
    printf("SerialTask :: initializing State 1\n");

    // now loop running the state code
    while (true) {
      // reset __change_state__ to false
      __change_state__ = false;
      // run the proper state function
      state_State_2_execute();
      state_State_1_execute();
      // now wait if we haven't changed state
      if (!__change_state__) {
        vTaskDelay( MS_TO_TICKS(__state_delay__) );
      }
      else {
        vTaskDelay( MS_TO_TICKS(1) );
      }
    }
  }

  // Generated state functions
  const uint8_t state_State_2 = 0;

  void state_State_2_execute( void ) {
    if (__change_state__ || stateLevel_0 != state_State_2)
      return;

    state_State_2_transition();

    // execute all substates
    state_State_2_State_execute();

    if (!__change_state__) {

    }
  }

  void state_State_2_setState( void ) {
    stateLevel_0 = state_State_2;
  }

  void state_State_2_transition( void ) {
    if (__change_state__)
      return;
  }

  void state_State_2_finalization( void ) {

  }

  const uint8_t state_State_2_State = 0;

  void state_State_2_State_execute( void ) {
    if (__change_state__ || stateLevel_1 != state_State_2_State)
      return;

    state_State_2_State_transition();

    // execute all substates

    if (!__change_state__) {
      printf("SerialTask :: State 2 :: State :: periodic Function\n");
    }
  }

  void state_State_2_State_setState( void ) {
    stateLevel_1 = state_State_2_State;
    state_State_2_setState();
  }

  void state_State_2_State_transition( void ) {
    if (__change_state__)
      return;
  }

  void state_State_2_State_finalization( void ) {

    // Finalize parent state
    state_State_2_finalization();
  }

  const uint8_t state_State_1 = 1;

  void state_State_1_execute( void ) {
    if (__change_state__ || stateLevel_0 != state_State_1)
      return;

    state_State_1_transition();

    // execute all substates

    if (!__change_state__) {
      printf("SerialTask :: State 1 :: periodic Function\n");
    }
  }

  void state_State_1_setState( void ) {
    stateLevel_0 = state_State_1;
  }

  void state_State_1_transition( void ) {
    if (__change_state__)
      return;
    else if ( InputOutputTask::buttonPressed ) {
      __change_state__ = true;
      // run the current state's finalization function
      state_State_1_finalization();
      // set the current state to the state we are transitioning to
      state_State_2_State_setState();
      // start state timer (@ next states period)
      __state_delay__ = 500;
      // execute the transition function
      printf("SerialTask :: transition function!\n");

    }
  }

  void state_State_1_finalization( void ) {

  }

 
};
