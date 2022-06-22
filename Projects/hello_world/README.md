# FreeRTOS Code Demonstration

## FreeRTOS Kernel Information and Programming Caveats

### Data Types

FreeRTOS has a ```portmacro.h``` header file that contains definitions for two port specific data types which are:

- ``` TickType_t ```
- ``` BaseType_t ```

#### TickType_t Data Type

- FreeRTOS configures a periodic interrupt called the tick interrupt.
- The number of tick interrupts that have occurred since the FreeRTOS application started is called the tick count. The tick count is used as a measure of time.
- TickType_t is the data type used to hold the tick count value, and to specify times.
- TickType_t can be:
  - unsigned 16-bit : configUSE_16_BIT_TICKS is set to 1
  - unsigned 32-bit : configUSE_16_BIT_TICKS is set to 0

#### BaseType_t Data Type

- This is always defined as the most efficient data type for the architecture.
Typically, this is a 32-bit type on a 32-bit architecture, a 16-bit type on a 16-bit architecture, and an 8-bit type on an 8-bit architecture.
- BaseType_t is generally used for return types that can take only a very limited range of values, and for pdTRUE/pdFALSE type Booleans.

### Variable Names

- Variables are prefixed with their type.
  - ``` c ``` for char
  - ``` s ``` for int16_t (short)
  - ``` l ``` for int32_t (long)
  - ``` x ``` for BaseType_t and any non-standard types (structs, task handles, queue handles, etc)
- Variables are also prefixed based on wether they are unsigned or pointer
  - ``` u ``` for unsigned
  - ``` p ``` for pointer
  - ``` v ``` for void

Example: a pointer to char : ```pc```
Example: an unsigned int16_t : ```us```

### Function Names

- Functions are prefixed with both the type they return and the file they are defined within.

**Example:**

- **vTask**PrioritySet() returns a void and is defined within task.c
- **xQueue**Receive() returns a variable of type BaseType_t and is defined within queue.c
- **pvTimer**GetTimerID() returns a pointer to void and is defined within timers.c

### Macro Names

Most macros are written in upper case, and prefixed with lower case letters that indicate where the macro is defined. Macro Prefixes are:

- port (e.g. portMAX_DELAY) -> portable.h or portmacro.h
- task (e.g. portENTER_CRITICAL()) -> task.h
- pd (e.g. pdTRUE) -> projdefs.h
- config (e.g. configUSE_PREEMPTION) -> FreeRTOSConfig.h
- err (e.g. errQUEUE_FULL) -> projdefs.h

These macros are used throughout source code:

- pdTRUE : 1
- pdFALSE : 0
- pdPASS : 1
- pdFAIL : 0

## Creating and Deleting a Task

- Tasks are implemented as C functions.
- Tasks must **return** ```void``` type
- Tasks **input parameters**  are ``` void pointers ```
- Each  task is a small program that has an entry point and runs forever within an infinite loop and will not exit.
- If a task is no longer required is should be explicitly deleted (vTaskDelete()).
Example Code Snippet of this declaration:

```c
void TaskFunction ( void *Params);
```

### Creating a Task

The ``` xTaskCreate() ``` and the ``` xTaskCreateStatic() ``` functions are used to create tasks in FreeRTOS.

- xTaskCreateStatic function allocates memory required to create the task statically at compile time.

The input parameters of these functions are:

- pvTaskCode :  c-function code (infinite loop code)
- pcName : The Name of the Task (string)
- usStackDepth : Each task has its own unique stack that is allocated by the kernel to the task when the task is created. The usStackDepth value tells the kernel how large to make the stack.
  - Input Integer X 4 bytes
- pvParameters : The input parameters of the pvTaskCode function
  - Must be of type pointer to void (typecasting) -> ``` (void*) ```
- uxPriority : Defines the priority at which the task will execute.
  - 0 -> Lowest Priority
  - configMAX_PRIORITIES is a user defined constant that sets that Highest Priority Number
- pxCreateTask : Task Handler. This handle can then be used to reference the task in API calls that, for example, change the task priority or delete the task.
  - If your application has no use for the task handle, then pxCreatedTask can be set to NULL.

Return Values are:

- pdPASS : indicates that the task has been created successfully.
- pdFAIL :  indicates that the task has not been created because there is insufficient heap memory available for FreeRTOS to allocate enough RAM to hold the task data structures and stack

### Deleting a Task
