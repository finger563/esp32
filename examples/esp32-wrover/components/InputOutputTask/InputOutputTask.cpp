#include "InputOutputTask.hpp"
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define MS_TO_TICKS( xTimeInMs ) (uint32_t)( ( ( TickType_t ) xTimeInMs * configTICK_RATE_HZ ) / ( TickType_t ) 1000 )

namespace InputOutputTask {

  // User definitions for the task
  gpio_num_t rPin          = GPIO_NUM_0;
  gpio_num_t gPin          = GPIO_NUM_2;
  gpio_num_t bPin          = GPIO_NUM_4;
  bool       ledOn         = false;

  bool       changeState   = false;

  // Everything below here is not exported (not in the declarations)

  void configureRGBPin( gpio_num_t pinNum ) {
    gpio_config_t io_conf;
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    //bit mask of the pins that you want to set
    io_conf.pin_bit_mask = (1<<pinNum);
    //disable pull-down mode
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    //disable pull-up mode
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    //configure GPIO with the given settings
    gpio_config(&io_conf);
  }


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
    state_Flash_All_RGB_setState();
    // execute the init transition for the initial state and task
    configureRGBPin(rPin);
    configureRGBPin(gPin);
    configureRGBPin(bPin);

    printf("Configured GPIO\n");

    // now loop running the state code
    while (true) {
      // reset __change_state__ to false
      __change_state__ = false;
      // run the proper state function
      state_Cycle_RGB_execute();
      state_Flash_All_RGB_execute();
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
  const uint8_t state_Cycle_RGB = 0;

  void state_Cycle_RGB_execute( void ) {
    if (__change_state__ || stateLevel_0 != state_Cycle_RGB)
      return;

    state_Cycle_RGB_transition();

    // execute all substates
    state_Cycle_RGB_Flash_Green_execute();
    state_Cycle_RGB_Flash_Blue_execute();
    state_Cycle_RGB_Flash_Red_execute();

    if (!__change_state__) {

    }
  }

  void state_Cycle_RGB_setState( void ) {
    stateLevel_0 = state_Cycle_RGB;
  }

  void state_Cycle_RGB_transition( void ) {
    if (__change_state__)
      return;
  }

  void state_Cycle_RGB_finalization( void ) {

  }

  const uint8_t state_Cycle_RGB_Flash_Green = 0;

  void state_Cycle_RGB_Flash_Green_execute( void ) {
    if (__change_state__ || stateLevel_1 != state_Cycle_RGB_Flash_Green)
      return;

    state_Cycle_RGB_Flash_Green_transition();

    // execute all substates

    if (!__change_state__) {
      gpio_set_level( gPin, ledOn );
      ledOn = !ledOn;
    }
  }

  void state_Cycle_RGB_Flash_Green_setState( void ) {
    stateLevel_1 = state_Cycle_RGB_Flash_Green;
    state_Cycle_RGB_setState();
  }

  void state_Cycle_RGB_Flash_Green_transition( void ) {
    if (__change_state__)
      return;
    else if ( changeState ) {
      __change_state__ = true;
      // run the current state's finalization function
      state_Cycle_RGB_Flash_Green_finalization();
      // set the current state to the state we are transitioning to
      state_Cycle_RGB_Flash_Blue_setState();
      // start state timer (@ next states period)
      __state_delay__ = 500;
      // execute the transition function
      changeState = false;
          printf("flashing blue\n");

    }
  }

  void state_Cycle_RGB_Flash_Green_finalization( void ) {
    gpio_set_level( rPin, false );
    gpio_set_level( gPin, false );
    gpio_set_level( bPin, false );
    ledOn = false;
    // Finalize parent state
    state_Cycle_RGB_finalization();
  }

  const uint8_t state_Cycle_RGB_Flash_Blue = 1;

  void state_Cycle_RGB_Flash_Blue_execute( void ) {
    if (__change_state__ || stateLevel_1 != state_Cycle_RGB_Flash_Blue)
      return;

    state_Cycle_RGB_Flash_Blue_transition();

    // execute all substates

    if (!__change_state__) {
      gpio_set_level( bPin, ledOn );
      ledOn = !ledOn;
    }
  }

  void state_Cycle_RGB_Flash_Blue_setState( void ) {
    stateLevel_1 = state_Cycle_RGB_Flash_Blue;
    state_Cycle_RGB_setState();
  }

  void state_Cycle_RGB_Flash_Blue_transition( void ) {
    if (__change_state__)
      return;
    else if ( changeState ) {
      __change_state__ = true;
      // run the current state's finalization function
      state_Cycle_RGB_Flash_Blue_finalization();
      // set the current state to the state we are transitioning to
      state_Cycle_RGB_Flash_Red_setState();
      // start state timer (@ next states period)
      __state_delay__ = 500;
      // execute the transition function
      changeState = false;
          printf("flashing red\n");

    }
  }

  void state_Cycle_RGB_Flash_Blue_finalization( void ) {
    gpio_set_level( rPin, false );
    gpio_set_level( gPin, false );
    gpio_set_level( bPin, false );
    ledOn = false;
    // Finalize parent state
    state_Cycle_RGB_finalization();
  }

  const uint8_t state_Cycle_RGB_Flash_Red = 2;

  void state_Cycle_RGB_Flash_Red_execute( void ) {
    if (__change_state__ || stateLevel_1 != state_Cycle_RGB_Flash_Red)
      return;

    state_Cycle_RGB_Flash_Red_transition();

    // execute all substates

    if (!__change_state__) {
      gpio_set_level( rPin, ledOn );
      ledOn = !ledOn;
    }
  }

  void state_Cycle_RGB_Flash_Red_setState( void ) {
    stateLevel_1 = state_Cycle_RGB_Flash_Red;
    state_Cycle_RGB_setState();
  }

  void state_Cycle_RGB_Flash_Red_transition( void ) {
    if (__change_state__)
      return;
    else if ( changeState ) {
      __change_state__ = true;
      // run the current state's finalization function
      state_Cycle_RGB_Flash_Red_finalization();
      // set the current state to the state we are transitioning to
      state_Cycle_RGB_Flash_Green_setState();
      // start state timer (@ next states period)
      __state_delay__ = 500;
      // execute the transition function
      changeState = false;
          printf("flashing green\n");

    }
  }

  void state_Cycle_RGB_Flash_Red_finalization( void ) {
    gpio_set_level( rPin, false );
    gpio_set_level( gPin, false );
    gpio_set_level( bPin, false );
    ledOn = false;
    // Finalize parent state
    state_Cycle_RGB_finalization();
  }

  const uint8_t state_Flash_All_RGB = 1;

  void state_Flash_All_RGB_execute( void ) {
    if (__change_state__ || stateLevel_0 != state_Flash_All_RGB)
      return;

    state_Flash_All_RGB_transition();

    // execute all substates

    if (!__change_state__) {
      gpio_set_level( rPin, ledOn );
      gpio_set_level( gPin, ledOn );
      gpio_set_level( bPin, ledOn );
      ledOn = !ledOn;
    }
  }

  void state_Flash_All_RGB_setState( void ) {
    stateLevel_0 = state_Flash_All_RGB;
  }

  void state_Flash_All_RGB_transition( void ) {
    if (__change_state__)
      return;
    else if ( changeState ) {
      __change_state__ = true;
      // run the current state's finalization function
      state_Flash_All_RGB_finalization();
      // set the current state to the state we are transitioning to
      state_Cycle_RGB_Flash_Red_setState();
      // start state timer (@ next states period)
      __state_delay__ = 500;
      // execute the transition function
      changeState = false;
          printf("flashing red\n");

    }
  }

  void state_Flash_All_RGB_finalization( void ) {
    gpio_set_level( rPin, false );
    gpio_set_level( gPin, false );
    gpio_set_level( bPin, false );
    ledOn = false;
  }

 
};
