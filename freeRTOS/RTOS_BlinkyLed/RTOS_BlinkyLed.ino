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
static const int blinkRateA = 30;
static const int blinkRateB = 55;

/**
 * Threads / Tasks
 */

/**
 * Toggle the Led
 */
void taskToggleLed_A(void * parameter) {
  while (1) {
    digitalWrite(ledPin, HIGH);
    /**
     * Use the non blocking delay from RTOS
     * RTOS will run other tasks in the mean
     * time until the wait time is up.
     */
    vTaskDelay(blinkRateA / portTICK_PERIOD_MS);
    digitalWrite(ledPin, LOW);
    vTaskDelay(blinkRateA / portTICK_PERIOD_MS);
  }
}

void taskToggleLed_B(void * parameter) {
  while (1) {
    digitalWrite(ledPin, HIGH);
    vTaskDelay(blinkRateB / portTICK_PERIOD_MS);
    digitalWrite(ledPin, LOW);
    vTaskDelay(blinkRateB / portTICK_PERIOD_MS);
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
    taskToggleLed_A,        // task function pointer
    "Toggle Led Rate A",    // Name of the task
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

 xTaskCreatePinnedToCore(
    taskToggleLed_B,        // task function pointer
    "Toggle Led Rate B",    // Name of the task
    1024,                   // Stack Size 1kB (in 8bit for ESP32, 16bit for regular RTOS)
    NULL,                   // Parameters to pass to the task function
    1,                      // Task priority
    NULL,                   // Task handle
    appCpu);                // Run the task in only one core.

}

void loop() {
  // put your main code here, to run repeatedly:

}
