#include "fifo.h"

void fifo_worker_handler(QueueHandle_t requests, QueueHandle_t results, int id)
{
    // Instantiate a buffer for request message data
    struct request_msg *data;
    
    // Pull off the most recent task from the requests fifo
    BaseType_t res = xQueueReceive(requests, &data, 1000);
    
    // do the worker routine (data += 5)
    data->output = data->input + 5;
    data->handled_by = id;

    // return the result by adding it to the results fifo
    xQueueSendToBack(results, &data, portMAX_DELAY);

}