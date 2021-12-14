#include <Arduino.h>
#include "hactimers.h"

HACTimers gHACTimers;

//Callback functions
void onDebugCB(const char *msg);
void onTicTacCB();
void onTickToggleCB(bool out);
void onCountingCB(uint16 count);
void onCountingDone();
void onTimerDoneCB(bool out);
void onElapseCB(unsigned long elapseTime);

void setup() {
  Serial.begin(115200);

  //If debug of the library verbose is enabled via DEBUG_ESP_PORT definition
  gHACTimers.onDebug(onDebugCB);
  
  
  //Case 1: Tic Tac Timer
  //gHACTimers.onTickTack(onTicTacCB);
  //Setup default mode is Tic Tc
  //gHACTimers.setup(2000);
  

  //Case 2: Tic Tac Toggle Timer
  //gHACTimers.onTickToggle(onTickToggleCB);
  //gHACTimers.setup(2000, TICK_TOGGLES);
  
  //Case 3: Up Counter
  //gHACTimers.onCounting(onCountingCB);
  //gHACTimers.onCountingDone(onCountingDone);
  //gHACTimers.setup(2000, UP_COUNTER, 10);

  //Case 4: Time On Delay
  bool onTrigger = true;       //Time on delay start when the trigger goes on
  gHACTimers.onTimerDone(onTimerDoneCB);
  gHACTimers.onElapse(onElapseCB);
  gHACTimers.setup(5000, TIME_ON_DELAY, onTrigger);

  //Case 5: Time Off Delay
  //bool offTrigger = false;       //Time Off delay start when the trigger goes off
  //gHACTimers.onTimerDone(onTimerDoneCB);
  //gHACTimers.setup(5000, TIME_OFF_DELAY, offTrigger);
  
  //Case 6: Time Off delay
  
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

void onTickToggleCB(bool out)
{
  Serial.println("Out =>" + String(out));
}

void onCountingCB(uint16 count)
{
  Serial.println("Count =>" + String(count));
}
void onCountingDone()
{
  Serial.println("Counting is done!");
}

void onTimerDoneCB(bool out)
{
  Serial.println("Time delay done, Out =>" + String(out));
}

void onElapseCB(unsigned long elapseTime)
{
  Serial.println("Elapse in milliseconds =>" + String(elapseTime));
}