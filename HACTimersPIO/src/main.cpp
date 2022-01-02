/*
 * https://github.com/SyntaxHarvy/HACTimers
 */

#include <HaCTimers.h>

HACTimers gHACTimers;

//Callback functions
void onDebugCB(const char *msg);
void onTickToggleCB(bool out);

void setup() {
  Serial.begin(115200);

  //If debug of the library verbose is enabled via DEBUG_ESP_PORT definition
  gHACTimers.onDebug(onDebugCB);
    
  gHACTimers.onTickToggle(onTickToggleCB);
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
}
