#include "InputOutputTask.hpp"
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define MS_TO_TICKS( xTimeInMs ) (uint32_t)( ( ( TickType_t ) xTimeInMs * configTICK_RATE_HZ ) / ( TickType_t ) 1000 )

namespace InputOutputTask {

  // User definitions for the task
  gpio_num_t ledPin        = GPIO_NUM_5;
  bool       ledOn         = false;
  gpio_num_t buttonPin     = GPIO_NUM_0;
  bool       buttonPressed = false;

  static void IRAM_ATTR buttonISR( void *pvParameters ) {
    // goes low when button is pressed
    buttonPressed = !gpio_get_level( buttonPin );
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
    state_State_1_setState();
    // execute the init transition for the initial state and task
    gpio_config_t io_conf;
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    //bit mask of the pins that you want to set
    io_conf.pin_bit_mask = (1<<ledPin);
    //disable pull-down mode
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    //disable pull-up mode
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    //configure GPIO with the given settings
    gpio_config(&io_conf);

    //interrupt of rising edge
    io_conf.intr_type = GPIO_INTR_POSEDGE;
    //bit mask of the pins
    io_conf.pin_bit_mask = (1<<buttonPin);
    //set as input mode    
    io_conf.mode = GPIO_MODE_INPUT;
    //enable pull-up mode
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_config(&io_conf);

    //change gpio intrrupt type for one pin
    gpio_set_intr_type(buttonPin, GPIO_INTR_ANYEDGE);

    /*
    //create a queue to handle gpio event from isr
    gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));
    //start gpio task
    xTaskCreate(gpio_task_example, "gpio_task_example", 2048, NULL, 10, NULL);
    */

    //install gpio isr service
    gpio_install_isr_service(0);
    //hook isr handler for specific gpio pin
    gpio_isr_handler_add(buttonPin, InputOutputTask::buttonISR, NULL);

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
      gpio_set_level( ledPin, ledOn );
      ledOn = !ledOn;
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
      gpio_set_level( ledPin, ledOn );
      ledOn = !ledOn;
    }
  }

  void state_State_1_setState( void ) {
    stateLevel_0 = state_State_1;
  }

  void state_State_1_transition( void ) {
    if (__change_state__)
      return;
    else if ( buttonPressed ) {
      __change_state__ = true;
      // run the current state's finalization function
      state_State_1_finalization();
      // set the current state to the state we are transitioning to
      state_State_2_State_setState();
      // start state timer (@ next states period)
      __state_delay__ = 500;
      // execute the transition function

    }
  }

  void state_State_1_finalization( void ) {

  }

 
};
