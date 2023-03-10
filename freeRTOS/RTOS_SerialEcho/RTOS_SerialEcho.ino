/*
This is a simple sketch, in which there are 2 Tasks: 

SerialSubscriber: 
- Listens to the input from the Serial Monitor
- On a newline character it stores all chars up to this 
  point in the heap memory.
- Notifies SerialPublisher of the new message

SerialPublisher:
- Waits for the notification of the SerialSubscriber
- Print the message found in the heap memory to the 
  Serial output
- Frees the Heap Memory
*/

#if CONFIG_FREERTOS_UNICORE
static const BaseType_t appCpu = 0;
#else
static const BaseType_t appCpu = 1;
#endif
static const int ledPin = LED_BUILTIN;

/* 
Generic Settings for the Message aCharBuffer 
This allows for max 255 chars
*/
static const uint8_t u8BufferLength = 255;

/*
These are the globals which are to be used
to pass data around between the two threads
*/
static char* pMessagePointer = NULL;
static volatile uint8_t bMessageInputFlag = 0;

/**
 * Simple delay function.
 */
void wait_ms(int ms) {
  vTaskDelay(ms / portTICK_PERIOD_MS);
}

void startBlinkyLed(void* parameters) {
  while (1) {
    digitalWrite(ledPin, HIGH);
    wait_ms(100);
    digitalWrite(ledPin, LOW);
    wait_ms(100);
  }
}

void startSerialSubscriber(void* parameters) {
  char c;
  char aCharBuffer[u8BufferLength];
  uint8_t u8CharacterIndex = 0;

  // Clear whole aCharBuffer
  memset(aCharBuffer, 0, u8BufferLength);

  Serial.println("-----------------------------------------");
  Serial.println("Please enter new String :)");

  // Loop forever
  while (1) {

    /* Read from the serial console */
    if (Serial.available() > 0) {
      c = Serial.read();

      /* Store received character to aCharBuffer if not over aCharBuffer limit */
      if (u8CharacterIndex < u8BufferLength - 1) {
        aCharBuffer[u8CharacterIndex] = c;
        u8CharacterIndex++;
      }

      // Create a message aCharBuffer for print task
      if (c == '\n') {

        // The last character in the string is '\n', so we need to replace
        // it with '\0' to make it null-terminated
        aCharBuffer[u8CharacterIndex - 1] = '\0';

        // Try to allocate memory and copy over message. If message aCharBuffer is
        // still in use, ignore the entire message.
        if (bMessageInputFlag == 0) {
          Serial.print("Number of characters entered: ");
          Serial.println(u8CharacterIndex);
          pMessagePointer = (char*)pvPortMalloc(u8CharacterIndex * sizeof(char));
          /* Check whether the returned value is NULL -> No space available */
          configASSERT(pMessagePointer);

          /* Copy the collected message from static memory (stack) to the heap */
          memcpy(pMessagePointer, aCharBuffer, u8CharacterIndex);

          /* Notify the other thread, that the message is ready to be processed */
          bMessageInputFlag = 1;
        }

        /* Reset all entries of the aCharBuffer to 0 */
        memset(aCharBuffer, 0, u8BufferLength);
        u8CharacterIndex = 0;
      }
    }
  }
}

void startSerialPublisher(void* parameters) {
  while (1) {
    // Wait for flag to be set and print message
    if (bMessageInputFlag == 1) {
      Serial.println(pMessagePointer);

      //Give amount of free heap memory (uncomment if you'd like to see it)
      Serial.print("Free heap (bytes): ");
      Serial.println(xPortGetFreeHeapSize());

      // Free aCharBuffer, set pointer to null, and clear flag
      vPortFree(pMessagePointer);
      pMessagePointer = NULL;
      bMessageInputFlag = 0;

      Serial.println("-----------------------------------------");
      Serial.println("Please enter new String :)");
    }
  }
}


void setup() {
  /* Configure the LED as an output Pin */
  pinMode(ledPin, OUTPUT);

  /* Set up the serial connection */
  Serial.begin(115200);

  wait_ms(1000);
  Serial.println();
  Serial.println("--- FreeRTOS Serial Echo ---");

  /*
  Task Creation
  */
  xTaskCreatePinnedToCore(
    startBlinkyLed,  // task function pointer
    "Toggle Led",    // Name of the task
    1024,            // Stack Size 1kB (in 8bit for ESP32, 16bit for regular RTOS)
    NULL,            // Parameters to pass to the task function
    1,               // Task priority
    NULL,            // Task handle
    appCpu);         // Run the task in only one core.

  xTaskCreatePinnedToCore(
    startSerialSubscriber,
    "Subscribe to Serial Console",
    1024,
    NULL,
    1,
    NULL,
    appCpu);

  xTaskCreatePinnedToCore(
    startSerialPublisher,
    "Publish to Serial Console",
    1024,
    NULL,
    1,
    NULL,
    appCpu);

  /* 
  Delete the setup and the loop task 
  */
  vTaskDelete(NULL);
}

void loop() {
  /* This is never reached */
  Serial.println("I must not be called");
}
