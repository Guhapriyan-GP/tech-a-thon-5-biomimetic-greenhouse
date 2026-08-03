#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Task Handles
TaskHandle_t TaskDSP;
TaskHandle_t TaskControl;

// Core 0: DSP and Predictive Modeling
void dsp_task(void *pvParameters) {
    for (;;) {
        // Goertzel sampling and ELM inference pipeline
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// Core 1: Actuation, Hardware Gating, and Telemetry
void control_task(void *pvParameters) {
    for (;;) {
        // MPU6050 reading, hardware AND-gate checks, and MQTT payload
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void setup() {
    // Assign DSP task to Core 0
    xTaskCreatePinnedToCore(
        dsp_task,
        "DSP_Task",
        4096,
        NULL,
        1,
        &TaskDSP,
        0
    );

    // Assign Control task to Core 1
    xTaskCreatePinnedToCore(
        control_task,
        "Control_Task",
        4096,
        NULL,
        1,
        &TaskControl,
        1
    );
}

void loop() {
    // Main loop remains empty; FreeRTOS handles execution
    vTaskDelete(NULL);
}