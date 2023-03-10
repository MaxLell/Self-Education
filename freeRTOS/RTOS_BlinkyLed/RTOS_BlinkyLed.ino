/**
 * Only one core shall be used for these demos. 
 * This makes it easier to grasp how RTOS works
 */
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t appCpu = 0;
#else
static const BaseType_t appCpu = 1;
#endif

/**
 * Pin Definition
 */
static const int ledPin = LED_BUILTIN;

/**
 * Threads / Tasks
 */

/**
 * Toggle the Led
 */
void taskToggleLed(void * parameter) {
  while (1) {
    digitalWrite(ledPin, HIGH);
    /**
     * Use the non blocking delay from RTOS
     * RTOS will run other tasks in the mean
     * time until the wait time is up.
     */
    vTaskDelay(500 / portTICK_PERIOD_MS);
    digitalWrite(ledPin, LOW);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

/**
 * setup() and loop() exist inside of their own 
 * FreeRTOS task.
 */

void setup() {
  /* Configure the LED as an output Pin */
  pinMode(ledPin, OUTPUT);

  /**
   * Create a task, which runs forever on only one core. 
   * This function is ESP32 explicit, due to its dual core
   * nature
   */
  xTaskCreatePinnedToCore(
    taskToggleLed,          // task function pointer
    "Toggle Led",           // Name of the task
    1024,                   // Stack Size 1kB (in 8bit for ESP32, 16bit for regular RTOS)
    NULL,                   // Parameters to pass to the task function
    1,                      // Task priority
    NULL,                   // Task handle
    appCpu);                // Run the task in only one core.

    /**
     * if this is regular FreeRTOS, you need to call teh vTaskScheduler()
     * in the main after setting up the tasks. But this is already taken
     * care for you in the ESP32 FreeRTOS - prior to this Task Creation
     */

}

void loop() {
  // put your main code here, to run repeatedly:

}
