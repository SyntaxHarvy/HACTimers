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
  bool offTrigger = false;       //Time Off delay start when the trigger goes off
  gHACTimers.setup(5000, TIME_OFF_DELAY, offTrigger);
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
  Serial.println("Time delay done, Out =>" + String(out));
}

void onElapseCB(unsigned long elapseTime)
{
  Serial.println("Elapse in milliseconds =>" + String(elapseTime));
}
