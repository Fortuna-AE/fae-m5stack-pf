/* General */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/* for M5Stack system */
#include "esp_system.h"
#include "esp_log.h"
#include "M5GFX.h"

/* M5GFX instance for M5Stack Basic */
M5GFX display;

// Perform an action every 1000 ticks.
void display_task(void *pvParameters)
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = pdMS_TO_TICKS(1000);

    int count;
    count = 0;

    M5GFX *lcd = static_cast<M5GFX *>(pvParameters);
    lcd->setTextColor(TFT_WHITE, TFT_BLACK);
    lcd->setTextDatum(MC_DATUM);
    lcd->setFont(&fonts::Font2);
    lcd->drawString("Hello World!",
                    lcd->width() / 2,
                    lcd->height() / 2);

    xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        /* Wait for the next cycle. */
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
        count++;

        /* Perform action here. */
        ESP_LOGI("DISPLAY", "Hello World! %d", count);
    }
}

extern "C" void app_main(void)
{
    /* Initialize M5GFX */
    display.begin();
    if (!display.begin())
    {
        ESP_LOGE("DISPLAY", "Display init failed");
        return;
    }

    /* Initialize LCD */
    display.setRotation(1);
    display.fillScreen(TFT_BLACK);

    /* Generate FreeRTOS task */
    BaseType_t xReturned;

    xReturned = xTaskCreate(
        display_task,  // Pointer to the task entry function
        "DisplayTask", // A descriptive name for the task
        4096,          // The number of words (not bytes!) to allocate for use as the task's stack
        &display,      // A value that is passed as the paramater
        1,             // Task priority
        nullptr        // Task handller
    );

    if (xReturned != pdPASS)
    {
        ESP_LOGE("RTOS", "Failed to create DisplayTask");
    }
}
