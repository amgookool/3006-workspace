#include "main.h"

int test0 = 420;

int test1[] = {0,10,20,30,40,50,60,70,80,90,100};

typedef struct UWI_STUDENT
{
    int uwi_id;
    char first_name[6];
    char last_name[7];
    char* language;
} xStudent;

xStudent xParam = {816008385,"Adrian","Gookool","Python and C/C++"};

static const char *degree = "Electrical and Computer Engineering"; 

void app_main()
{
    vTaskSuspendAll(); //suspends the task scheduler

    // Initializing a task handler for creating and deleting a task
    TaskHandle_t myTaskHandle = NULL;

    //  Creating a Task
    // xTaskCreate(c-function, task-name, stack-depth, function-parameters, priority-level, task-handler)
    // Function-Parameters must be of type: void*
    
    // Tasks with no input parameters
    xTaskCreate(chipDataTask,"Print-Chip-Info-Task", 1024, NULL, 10, NULL);
    
    xTaskCreate(myTask, "No-Param-Task", 1024, NULL, 9, & myTaskHandle);
    
    // Getting the priority of a Task
        //  Use a task handler in the uxTaskPriorityGet function which returns a UBaseType_t type priority integer
    UBaseType_t task_priority = uxTaskPriorityGet(myTaskHandle);
    printf("My task priority is %d\n",task_priority);

    // Setting the priority of a Task
    vTaskPrioritySet(myTaskHandle,3);

    //Check if priority was changed.   
    UBaseType_t task_priority = uxTaskPriorityGet(myTaskHandle);
    printf("My task priority is %d\n",task_priority);
    
    // Suspending a Task
    // vTaskSuspend();
    

    // Task with an integer input parameter
    xTaskCreate(int_paramTask,"ipTask",1024,(void*)test0,8,NULL);

    // Task with an integer array input parameter
    xTaskCreate(array_paramTask,"array-paramTask",1024,(void*)test1,7,NULL);

    // Task with an struct input parameter
    xTaskCreate(struct_paramTask,"StructParam-Task",1024,(void*) &xParam,6,NULL);

    // Task with an string input parameter
    xTaskCreate(string_paramTask,"StrParam-Task", 1024, (void*)degree,5,NULL);

    // Delaying for 20 seconds 
    vTaskDelay(TWENTY_SECONDS/portTICK_PERIOD_MS);

    // Deleting a Task using task Handler
    if (myTaskHandle != NULL)
        vTaskDelete(myTaskHandle);
    
    xTaskResumeAll(); // resume the task scheduler


}

void chipDataTask(void *pvParam){

    esp_chip_info_t chip_data; //initializing typedef for ESP8266 chip information 
    esp_chip_info(& chip_data); // using function to get and store chip data into typedef struct chip_data

    printf("The Model Number of the MCU: %s\n",chip_data.model);
    printf("The number of CPU cores: %d\n",chip_data.cores);
    printf("Revision Number:%d\n",chip_data.revision);

    vTaskDelete(NULL); // Delete Task Once Finished Executing
}


void myTask(void *pvParam){
    while(1){
        printf("Hello World! This is my task Function that takes no input parameters");
        vTaskDelay(FIVE_SECONDS/portTICK_PERIOD_MS); // Delay for Five Seconds
    }
}

// Creating a task with an input parameter of a integer
void int_paramTask(void *pvParam){
    int* input_int;
    input_int = (int*) pvParam;

    printf("The value passed into the function is: %d\n", *input_int);

    vTaskDelete(NULL);
}

// Creating a task with an input parameters consisting of an array
void array_paramTask(void *pvParam){
    int* arr_in;
    arr_in = (int*)pvParam;
    int arr_len = sizeof(arr_in)/sizeof(int);
    for (int i = 0 ; i < arr_len; i++){
        printf("Value at index %d : ",i);
        printf("%d\n",*(arr_in + i));
    }
    vTaskDelete(NULL);
}

// Creating a task with an input parameter of a struct
void struct_paramTask(void *pvParam){
    xStudent* student_param;
    student_param = (xStudent*) pvParam;

    printf("Student ID: %d\n",student_param->uwi_id);
    print("Student Name: %s ",student_param->first_name);
    printf("%s\n",student_param->last_name);
    printf("Programming Languages: %s\n",student_param->language);

    vTaskDelete(NULL);
}

// Creating a task with an input parameter of a string
void string_paramTask(void *pvParam){
    char* degree;
    degree = (char*) pvParam; 
    printf("Degree: %s\n",degree);
    vTaskDelete(NULL);
}
