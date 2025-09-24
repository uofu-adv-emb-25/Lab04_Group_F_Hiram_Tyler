#include "signaling.h"

// worker task
void signal_handle_calculation(SemaphoreHandle_t request, SemaphoreHandle_t response, struct signal_data *data)
{
    
    printf("Waiting for the request from supervisor task\n");
    xSemaphoreTake(request, portMAX_DELAY);

    printf("Updating data output\n");
    data->output = data->input + 5;

    vTaskDelay(10);

    printf("Signal Supervisor that calculation is done\n");
    xSemaphoreGive(response);

    printf("Exit calculation routine\n");

}    

// "Supervisor" task
BaseType_t signal_request_calculate(SemaphoreHandle_t request, SemaphoreHandle_t response, struct signal_data *data)
{
    printf("Signaling worker tasks\n");
    xSemaphoreGive(request);
    
    printf("Waiting for worker task to complete work\n");
    BaseType_t result = xSemaphoreTake(response, 100);

    printf("Recieved signal that worker task has completed\n");

    return result;

}