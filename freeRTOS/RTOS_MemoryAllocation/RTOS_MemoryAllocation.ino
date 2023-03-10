/*
This is a demo program, which shows the effects of memory allocation
All the action is taking place in the taskAllocateMemory() function.
In its current form memory is allocated in a safe form, yet if you comment
out the right portions of the code, flash the code and observe the outputs 
on the serial terminal, you can see how the Microcontroller goes seriously
into the weeds.
*/

#if CONFIG_FREERTOS_UNICORE
static const BaseType_t appCpu = 0;
#else
static const BaseType_t appCpu = 1;
#endif
static const int ledPin = LED_BUILTIN;
static TaskHandle_t tAllocateMemory;

/**
 * Simple delay function.
 */
void wait_ms(int ms) {
  vTaskDelay(ms / portTICK_PERIOD_MS);
}

void taskAllocateMemory(void* parameter) {
  while (1) {
    volatile int fillInValue = 8;

    /*
    Creates an Array on the stack of the Thread
    This stack is within the microcontroller's heap
    memory.
    However each task/thread is initialized with a certain
    amount of heap memory. 
    This array contains: 100 * 4 Bytes.
    The minimum heap space that is required for an ESP32 thread is 768 Bytes
    The initial setting for the allocated space is 1024 bytes. Therefore the 
    available space is to small. The Processor will crash once it exceeds its
    limit - which happens
    */
    volatile int array[100];

    for (int i = 0; i < 100; i++) {
      array[i] = i;
    }
    Serial.println("Beep - successful run");

    /*
    You can also get the high watermark (words = 4 bytes)
    of available memory in the currents' tasks allocated
    stack Memory
    */
    Serial.print("High water mark (words): ");
    Serial.println(uxTaskGetStackHighWaterMark(tAllocateMemory));

    /*
    Get the total amount of available Heap size
    */
    Serial.print("Heap Size before malloc (bytes): ");
    Serial.println(xPortGetFreeHeapSize());

    /*
    Allocate a big chunk of memory on the heap
    This memory is allocated external from the allocated
    stack memory. It is allcated directly on the heap.

    In order to malloc memory in a thread safe way, freeRTOS provides
    the pvPortMalloc function.

    If this memory is not free'd then the increasing heap will
    crash into the stack eventually. The printing functionality
    which is added below is there to make the growth of the 
    heap visible.
    */
    int* pPointerToMemory = (int*)pvPortMalloc(1024 * sizeof(int));

    if (NULL == pPointerToMemory) {
      /* pvPortMalloc returns NULL when there is no Heap Memory left over */
      Serial.println("####### No heap memory space left ######### ");
    } else {
      /* Do something with the memory so that the compiler does not optimize it out */
      for (int i = 0; i < 1024; i++) {
        pPointerToMemory[i] = i;
      }
    }
    /*
    Recheck the memory
    */
    Serial.print("Heap Size after malloc (bytes): ");
    Serial.println(xPortGetFreeHeapSize());

    /*
    Free the Memory after usage. Again 
    RTOS provides a thread safe function for the memory
    deallocation (free)

    Comment out the following free vPortFree() functions
    to see the Microcontroller going into the weeds of
    allocating memory which is not free - there is another
    safety net though. The memory is only allocated, when there
    is heap memory available. You also need to comment out the section above
    where it is checked against the NULL Return value.
    */
    vPortFree(pPointerToMemory);

    wait_ms(200);
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
  /* Set up the serial connection */
  Serial.begin(115200);

  wait_ms(1000);

  Serial.println();
  Serial.println("--- FreeRTOS Memory Demo ---");

  xTaskCreatePinnedToCore(
    taskAllocateMemory,
    "Memory Allocation Task",
    //1024,  // Initial Value is too small for the array that is created withing the stack of the thread
    1500,  // Update this value - 768 bytes + 400 bytes + extra margin = 1500
    NULL,
    1,
    &tAllocateMemory,
    appCpu);

  /* Configure the LED as an output Pin */
  pinMode(ledPin, OUTPUT);

  xTaskCreatePinnedToCore(
    startBlinkyLed,  // task function pointer
    "Toggle Led",    // Name of the task
    1024,            // Stack Size 1kB (in 8bit for ESP32, 16bit for regular RTOS)
    NULL,            // Parameters to pass to the task function
    1,               // Task priority
    NULL,            // Task handle
    appCpu);         // Run the task in only one core.

  /* Delets the setup and the loop task */
  vTaskDelete(NULL);
}

void loop() {
  /* This is never reached */
  Serial.println("I must not be called");
}
