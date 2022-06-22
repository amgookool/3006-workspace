#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#define FIVE_SECONDS 5000
#define TWENTY_SECONDS 20000 

// Task Function Prototypes
// Creating a task that has no input parameters
void myTask(void *pvParam);
void chipDataTask(void *pvParam);

// Creating a task with an input parameter of int/float
void int_paramTask(void *pvParam);

// Creating a task with an input parameters consisting of an array
void array_paramTask(void *pvParam);

// Creating a task with an input parameter of a struct
void struct_paramTask(void *pvParam);

// Creating a task with an input parameter of a string
void string_paramTask(void *pvParam);
