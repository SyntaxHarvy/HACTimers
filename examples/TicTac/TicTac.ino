/*
 * https://github.com/SyntaxHarvy/HACTimers
 */

#include <HaCTimers.h>
HACTimers gHACTimers;

//Callback functions
void onDebugCB(const char *msg);
void onTicTacCB();

void setup() {
  Serial.begin(115200);

  //If debug of the library verbose is enabled via DEBUG_ESP_PORT definition
  gHACTimers.onDebug(onDebugCB);
    
  gHACTimers.onTickTack(onTicTacCB);
  //Setup default mode is Tic Tc
  gHACTimers.setup(2000);
  
  gHACTimers.begin();
  
}

void loop() {
  gHACTimers.handle();
}

void onDebugCB(const char *msg){
  Serial.println(msg);
}

void onTicTacCB(){
  Serial.println("On Tic Tac..");
}
