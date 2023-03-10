/**
 * FreeRTOS Task Demo
 * 
 * Toggles an LED and print 'Hello World'
 * This example shows the effects of one task interrupting
 * the other task.
 * 
 * Basically the ESP32 Default task (as it is already in place
 * with the setup and the loop function) controls the other 2
 * tasks.
 */

#if CONFIG_FREERTOS_UNICORE
static const BaseType_t appCpu = 0;
#else
static const BaseType_t appCpu = 1;
#endif

/* Some random string that can be interrupted ;) */
const char msg[] = "Boaty McBoatFace is really the best name you can pick for a submarine robot - don't you think???";

static const int ledPin = LED_BUILTIN;

/**
 * Task handles, so that these tasks can be controlled
 * by a third task.
 */
static TaskHandle_t taskPrintInidividualChars;
static TaskHandle_t taskPrintStars;

/**
 * Helperfunction - waiting
 */

/**
 * Simple delay function.
 */
void wait_ms(int ms) {
  vTaskDelay(ms / portTICK_PERIOD_MS);
}

/**
 * Tasks
 */

void startTaskPrintIndividualChars(void* parameters) {
  int msgLength = strlen(msg);
  /**
    * Print the individual chars to the terminal
    * Since the baudrate of the communication is set to 
    * such a low speed this operation will be intercepted
    * by the other tasks. Furthermore this task has the 
    * lowest prio. Therefore it can be interrupted by 
    * everything else.
    */
  while (1) {
    Serial.println();
    for (int i = 0; i < msgLength; i++) {
      Serial.print(msg[i]);
    }
    Serial.println();
    wait_ms(1000);
  }
}

void startTaskPrintStars(void* parameters) {
  /**
   * This task just prints random stars.
   * Since it has a higher prio then the 
   * printIndividualChars task, it will 
   * introduce asterics in the output string, 
   * when this one is printed.
   */
  while (1) {
    Serial.print("*");
    wait_ms(100);
  }
}

void startBlinkyLed(void* parameters) {
  while (1) {
    digitalWrite(ledPin, HIGH);
    wait_ms(100);
    digitalWrite(ledPin, LOW);
    wait_ms(100);
  }
}

void setup() {
  /* Configure the LED as an output Pin */
  pinMode(ledPin, OUTPUT);

  /* Set a really low baud rate - otherwise it is not observable */
  Serial.begin(300);

  /* Wait until the connection is established */
  wait_ms(1000);
  Serial.println();
  Serial.println("--- FreeRTOS Task Demo ---");

  /* Print the own tasks priority */
  Serial.print("Setup and loop task on core: ");
  Serial.print(xPortGetCoreID());
  Serial.print(" with priority ");
  Serial.println(uxTaskPriorityGet(NULL));

  /**
   * Setup the new tasks
   */
  xTaskCreatePinnedToCore(
    startTaskPrintIndividualChars,
    "Print individual characters",
    1024,
    NULL,
    1,
    &taskPrintInidividualChars,  // Adding the task handle makes it possible to control the task from outside
    appCpu);

  xTaskCreatePinnedToCore(
    startTaskPrintStars,
    "Print stars!! :)",
    1024,
    NULL,
    5,  // This task gets a higher prio, so that it is able to intercept the printIndividualChars Task
    &taskPrintStars,
    appCpu);


  xTaskCreatePinnedToCore(
    startBlinkyLed,  // task function pointer
    "Toggle Led",    // Name of the task
    1024,            // Stack Size 1kB (in 8bit for ESP32, 16bit for regular RTOS)
    NULL,            // Parameters to pass to the task function
    1,               // Task priority
    NULL,            // Task handle
    appCpu);         // Run the task in only one core.
}
void loop() {
  /**
   * Wait for 4 seconds to have the stars
   * writing into the stream
   */
  wait_ms(4000);

  /**
   * Suspend the printStars task
   */
  for (int i = 0; i < 3; i++) {
    vTaskSuspend(taskPrintStars);
    wait_ms(2000);
    vTaskResume(taskPrintStars);
    wait_ms(2000);
  }


  /**
   * Suspend the print Stars task for 3 seconds
   */
  vTaskSuspend(taskPrintStars);
  wait_ms(4000);
  vTaskResume(taskPrintStars);

  /**
   * Delete the PrintIndividualChars task
   * It is important that this is not done
   * repeatedly - Trouble incoming otherwisek
   */
  if (taskPrintInidividualChars != NULL) {
    Serial.println("Task deleted");
    vTaskDelete(taskPrintInidividualChars);
    taskPrintInidividualChars = NULL;
  }
}
