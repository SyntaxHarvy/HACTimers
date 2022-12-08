#ifndef __MYTRAFFICLIGHT_H_
#define __MYTRAFFICLIGHT_H_

#include <Arduino.h>

typedef struct trafficTimePeriod
{
    uint8_t start;
    uint8_t end;
} t_trafficTimePeriod;

class myTrafficLight
{
public:
    myTrafficLight(std::vector<t_trafficTimePeriod> tPeriods); // Constructor
    ~myTrafficLight();   

    bool handle(uint16_t t); 
    
private:       
    std::vector<t_trafficTimePeriod> _tPeriods;    

};

#include "myTraficLight-impl.h"

#endif