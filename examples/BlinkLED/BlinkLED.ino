/*
 * Blink example with 2 seconds interval
 * https://github.com/SyntaxHarvy/HACTimers
 */

#include <HACTimers.h>

HACTimers gHACTimers;

//Callback functions
void onDebugCB(const char *msg);
void onTickToggleCB(bool out);
void onElapseCB(unsigned long elapseTime);

void setup() {
  Serial.begin(115200);

  //If debug of the library verbose is enabled via DEBUG_ESP_PORT definition
  gHACTimers.onDebug(onDebugCB);

  //Set GPIO4 as an OUTPUT
  pinMode(16, OUTPUT);
  //Turn OFF GPIO16
  digitalWrite(16, LOW);

  gHACTimers.onTickToggle(onTickToggleCB);
  gHACTimers.onElapse(onElapseCB);
  gHACTimers.setup(2000, TICK_TOGGLES);    
  gHACTimers.begin();
  
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
  //Set GPIO16 to out value
  digitalWrite(16, out);
}
void onElapseCB(unsigned long elapseTime)
{
  Serial.println("Elsapse time =>" + String(elapseTime));
}
