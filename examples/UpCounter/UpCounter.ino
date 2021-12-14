#include <hactimers.h>

HACTimers gHACTimers;

//Callback functions
void onDebugCB(const char *msg);
void onCountingCB(uint16 count);
void onCountingDone();

void setup() {
  Serial.begin(115200);

  //If debug of the library verbose is enabled via DEBUG_ESP_PORT definition
  gHACTimers.onDebug(onDebugCB);
    
  gHACTimers.onCounting(onCountingCB);
  gHACTimers.onCountingDone(onCountingDone);
  gHACTimers.setup(2000, UP_COUNTER, 10);
  gHACTimers.begin();
  
}

void loop() {
  gHACTimers.handle();
}

void onDebugCB(const char *msg){
  Serial.println(msg);
}
void onCountingCB(uint16 count)
{
  Serial.println("Count =>" + String(count));
}
void onCountingDone()
{
  Serial.println("Counting is done!");
}
