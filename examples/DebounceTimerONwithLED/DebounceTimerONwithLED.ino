/*
 * This example will turn on the GPIO16 after GPIO2 held to ground for 10secs
 * https://github.com/SyntaxHarvy/HACTimers
 */

#include <HACTimers.h>

HACTimers gHACTimers;

//Callback functions
void onDebugCB(const char *msg);
void onTimerDoneCB(bool out);
void onElapseCB(unsigned long elapseTime);

void setup() {
  Serial.begin(115200);

  //If debug of the library verbose is enabled via DEBUG_ESP_PORT definition
  gHACTimers.onDebug(onDebugCB);

  //GPIO2 as an INPUT_PULLUP
  pinMode(2, INPUT_PULLUP);
  //Set GPIO4 as an OUTPUT
  pinMode(16, OUTPUT);
  //Turn OFF GPIO16
  digitalWrite(16, LOW);

  gHACTimers.onTimerDone(onTimerDoneCB);
  gHACTimers.onElapse(onElapseCB);
  gHACTimers.setup(10000, TIME_ON_DELAY);    
  gHACTimers.begin();
  
}

void loop() {
  gHACTimers.handle();

  //When the input GPIO2 held for 10secs then it will activate the output GPIO16
  gHACTimers.timeDelayTrigger = !digitalRead(2);  

}

void onDebugCB(const char *msg){
  Serial.println(msg);
}
void onTimerDoneCB(bool out)
{
  Serial.println("Out =>" + String(out));

  //Set GPIO16 to out value
  digitalWrite(16, out);
}
void onElapseCB(unsigned long elapseTime)
{
  Serial.println("Elsapse time =>" + String(elapseTime));
}
