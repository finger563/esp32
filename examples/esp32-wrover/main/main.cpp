#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"

// include the task components
#include "InputOutputTask.hpp"
#include "SerialTask.hpp"
#include "DisplayTask.hpp"

// now start the tasks that have been defined
extern "C" void app_main(void)
{
  xTaskCreate(&InputOutputTask::taskFunction, // function the task runs
	      "taskFunction_0", // name of the task (should be short)
	      2048, // stack size for the task
	      NULL, // parameters to task
	      1, // priority of the task (higher -> higher priority)
	      NULL // returned task object (don't care about storing it)
	      );
  xTaskCreate(&SerialTask::taskFunction, // function the task runs
	      "taskFunction_1", // name of the task (should be short)
	      2048, // stack size for the task
	      NULL, // parameters to task
	      0, // priority of the task (higher -> higher priority)
	      NULL // returned task object (don't care about storing it)
	      );
  xTaskCreate(&DisplayTask::taskFunction, // function the task runs
	      "taskFunction_2", // name of the task (should be short)
	      2048, // stack size for the task
	      NULL, // parameters to task
	      0, // priority of the task (higher -> higher priority)
	      NULL // returned task object (don't care about storing it)
	      );
}

