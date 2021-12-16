#include <hactimers.h>

HACTimers gHACTimers;

//Callback functions
void onDebugCB(const char *msg);
void onTimerDoneCB(bool out);
void onElapseCB(unsigned long elapseTime);

void setup() {
  Serial.begin(115200);

  //If debug of the library verbose is enabled via DEBUG_ESP_PORT definition
  gHACTimers.onDebug(onDebugCB);
    
  gHACTimers.onTimerDone(onTimerDoneCB);
  gHACTimers.onElapse(onElapseCB);
  gHACTimers.setup(10000, TIME_ON_DELAY);  
  gHACTimers.timeDelayTrigger = true;             //Once trigger is true then time on delay will start counting
  gHACTimers.begin();
  
}

void loop() {
  gHACTimers.handle();
}

void onDebugCB(const char *msg){
  Serial.println(msg);
}
void onTimerDoneCB(bool out)
{
  Serial.println("Out =>" + String(out));
}
void onElapseCB(unsigned long elapseTime)
{
  Serial.println("Elsapse time =>" + String(elapseTime));
}