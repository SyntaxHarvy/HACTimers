#include <Arduino.h>
#include "myTrafficLight.h"
#include "HaCTimers.h"


std::vector<t_trafficTimePeriod> green1TPeriods =
{
    {//Time Period range1
        0,  //Start on seconds
        10 //End on seconds
    },
    {
        26,  //Start on seconds
        40 //End on seconds
    }//Time Period range2  

};
myTrafficLight green1(green1TPeriods);

std::vector<t_trafficTimePeriod> orange1TPeriods =
{
    {//Time Period range1
        11,  //Start on seconds
        15 //End on seconds
    },
    {
        41,  //Start on seconds
        45 //End on seconds
    }//Time Period range2  

};
myTrafficLight orange1(orange1TPeriods);

std::vector<t_trafficTimePeriod> red1TPeriods =
{
    {//Time Period range1
        16,  //Start on seconds
        25 //End on seconds
    },
    {
        46,  //Start on seconds
        60 //End on seconds
    }//Time Period range2  

};
myTrafficLight red1(red1TPeriods);

#define GREEN_PIN1  2
#define ORANGE_PIN1  3
#define RED_PIN1  4

#define PIN_SIZE 3

uint8_t outputPins[PIN_SIZE] = {GREEN_PIN1, ORANGE_PIN1, RED_PIN1};

HACTimers gHACTimers;

//Timers Callback functions
void onCountingCB(uint16 count);

void setup() {
    Serial.begin(115200);
    
    //Define GPIO PIN for traffic light 1
    for(uint8_t i=0;i<(uint8_t)PIN_SIZE; i++)
        pinMode(outputPins[i], OUTPUT);

    //Setup Timer
    gHACTimers.onCounting(onCountingCB);
    gHACTimers.onCountingDone([&]{
        gHACTimers.reset(); //Reset the timer when it is done
    });
    gHACTimers.setup(1000, UP_COUNTER, 60); //Count up every second up to 60, define the end of the counter according to the traffic light maximum period requirement
    gHACTimers.begin();    
    
  
}

void loop() {
    gHACTimers.handle();
}


void onCountingCB(uint16 count)
{
    Serial.println(count);

    bool gr, og, rd;

    gr = green1.handle(count);
    og = orange1.handle(count);
    rd = red1.handle(count);
    digitalWrite(GREEN_PIN1, gr);
    digitalWrite(ORANGE_PIN1, og);
    digitalWrite(RED_PIN1, rd);

    if((gr + og + rd) > 1 || (gr + og + rd) == 0)
    {
        Serial.println("ERROR INVALID STATE!");  
        return;
    }

    if(gr)
    {
        Serial.println("GO!");
    }
    else if(og)
    {
        Serial.println("PREPARE FOR STOP..");
    }
    else if(rd)
    {
        Serial.println("STOP!");
    }    

}
