/*
 * https://github.com/SyntaxHarvy/HACTimers
 */

#include <HaCTimers.h>

HACTimers gHACTimers;

//Callback functions
void onDebugCB(const char *msg);
void onTickToggleCB(bool out);
bool _isBusyFlag = true;
void setup() {
  Serial.begin(115200);

  //If debug of the library verbose is enabled via DEBUG_ESP_PORT definition
  gHACTimers.timeDelayTrigger = _isBusyFlag;
  gHACTimers.onDebug(onDebugCB);
  
  gHACTimers.onTimerDone([&](bool out){
      _isBusyFlag = false;
      Serial.printf("Busy flag : %d \n", (uint8_t)_isBusyFlag);          
      gHACTimers.reset();
  });
  gHACTimers.onElapse([&](unsigned long elapse)
  {
    Serial.printf("Elapsed : %ld \n", elapse);
  });
  gHACTimers.begin();
  gHACTimers.setup(5000, TIME_ON_DELAY);
  
}

void loop() {
  gHACTimers.handle();
}

void onDebugCB(const char *msg){
  Serial.println(msg);
}
void onTickToggleCB(bool out)
{
  Serial.println("Out =>" + String(out));
}
