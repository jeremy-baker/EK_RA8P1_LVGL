#include "touch_thread.h"
#include "port/lv_port_indev.h"

/* Touch Thread entry function */
/* pvParameters contains TaskHandle_t */
void touch_thread_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED (pvParameters);

    /* TODO: add your own code here */
    while (1)
    {
#if (1 == INDEV_EVENT_DRIVEN)
        BaseType_t status;

        status = xSemaphoreTake( g_irq_binary_semaphore, portMAX_DELAY);
        if(pdTRUE == status)
        {
            lv_indev_t * indev_touchpad = NULL;
            indev_touchpad = lv_indev_get_next(NULL);
            if(NULL == indev_touchpad)
            {
                LV_ASSERT(0);
            }
            /* Call this anywhere you want to read the input device */
            lv_indev_read(indev_touchpad);
        }
#else
        vTaskDelay(portMAX_DELAY);
#endif

    }
}
