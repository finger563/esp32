#include "SerialTask.hpp"
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define MS_TO_TICKS( xTimeInMs ) (uint32_t)( ( ( TickType_t ) xTimeInMs * configTICK_RATE_HZ ) / ( TickType_t ) 1000 )

namespace SerialTask {

  // User definitions for the task
  bool changeState = false;

  // Everything below here is not exported by the header

  static const char *TAG = "uart_events";

  #define EX_UART_NUM UART_NUM_0

  #define BUF_SIZE (1024)
  static QueueHandle_t uart0_queue;

  uint8_t data[BUF_SIZE];

  static void uart_event_task(void *pvParameters)
  {
    uart_event_t event;
    size_t buffered_size;
    uint8_t* dtmp = (uint8_t*) malloc(BUF_SIZE);
    for(;;) {
      //Waiting for UART event.
      if(xQueueReceive(uart0_queue, (void * )&event, (portTickType)portMAX_DELAY)) {
        ESP_LOGI(TAG, "uart[%d] event:", EX_UART_NUM);
        switch(event.type) {
            //Event of UART receving data
            /*We'd better handler data event fast, there would be much more data events than
                  other types of events. If we take too much time on data event, the queue might
                  be full.
                  in this example, we don't process data in event, but read data outside.*/
          case UART_DATA:
            uart_get_buffered_data_len(EX_UART_NUM, &buffered_size);
            ESP_LOGI(TAG, "data, len: %d; buffered len: %d", event.size, buffered_size);
            break;
            //Event of HW FIFO overflow detected
          case UART_FIFO_OVF:
            ESP_LOGI(TAG, "hw fifo overflow\n");
            //If fifo overflow happened, you should consider adding flow control for your application.
            //We can read data out out the buffer, or directly flush the rx buffer.
            uart_flush(EX_UART_NUM);
            break;
            //Event of UART ring buffer full
          case UART_BUFFER_FULL:
            ESP_LOGI(TAG, "ring buffer full\n");
            //If buffer full happened, you should consider encreasing your buffer size
            //We can read data out out the buffer, or directly flush the rx buffer.
            uart_flush(EX_UART_NUM);
            break;
            //Event of UART RX break detected
          case UART_BREAK:
            ESP_LOGI(TAG, "uart rx break\n");
            break;
            //Event of UART parity check error
          case UART_PARITY_ERR:
            ESP_LOGI(TAG, "uart parity error\n");
            break;
            //Event of UART frame error
          case UART_FRAME_ERR:
            ESP_LOGI(TAG, "uart frame error\n");
            break;
            //UART_PATTERN_DET
          case UART_PATTERN_DET:
            ESP_LOGI(TAG, "uart pattern detected\n");
            changeState = true;
            InputOutputTask::changeState = true;
            DisplayTask::changeState = true;
            break;
            //Others
          default:
            ESP_LOGI(TAG, "uart event type: %d\n", event.type);
            break;
        }
      }
    }
    free(dtmp);
    dtmp = NULL;
    vTaskDelete(NULL);
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
    uart_config_t uart_config = {
      .baud_rate = 115200,
      .data_bits = UART_DATA_8_BITS,
      .parity = UART_PARITY_DISABLE,
      .stop_bits = UART_STOP_BITS_1,
      .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
      .rx_flow_ctrl_thresh = 122,
    };
    //Set UART parameters
    uart_param_config(EX_UART_NUM, &uart_config);
    //Set UART log level
    esp_log_level_set(TAG, ESP_LOG_INFO);
    //Install UART driver, and get the queue.
    uart_driver_install(EX_UART_NUM, BUF_SIZE * 2, BUF_SIZE * 2, 10, &uart0_queue, 0);

    //Set UART pins (using UART0 default pins ie no changes.)
    uart_set_pin(EX_UART_NUM, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    //Set uart pattern detect function.
    uart_enable_pattern_det_intr(EX_UART_NUM, '+', 3, 10000, 10, 10);
    //Create a task to handler UART event from ISR
    xTaskCreate(uart_event_task, "uart_event_task", 2048, NULL, 12, NULL);
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
      int len = uart_read_bytes(EX_UART_NUM, data, BUF_SIZE, 100 / portTICK_RATE_MS);
      if(len > 0) {
        ESP_LOGI(TAG, "uart read : %d", len);
        //uart_write_bytes(EX_UART_NUM, (const char*)data, len);
      }
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

      int len = uart_read_bytes(EX_UART_NUM, data, BUF_SIZE, 100 / portTICK_RATE_MS);
      if(len > 0) {
        ESP_LOGI(TAG, "uart read : %d", len);
        uart_write_bytes(EX_UART_NUM, (const char*)data, len);
      }
    }
  }

  void state_State_1_setState( void ) {
    stateLevel_0 = state_State_1;
  }

  void state_State_1_transition( void ) {
    if (__change_state__)
      return;
    else if ( changeState ) {
      __change_state__ = true;
      // run the current state's finalization function
      state_State_1_finalization();
      // set the current state to the state we are transitioning to
      state_State_2_State_setState();
      // start state timer (@ next states period)
      __state_delay__ = 500;
      // execute the transition function
      printf("SerialTask :: transition function!\n");
      changeState = false;

    }
  }

  void state_State_1_finalization( void ) {

  }

 
};
