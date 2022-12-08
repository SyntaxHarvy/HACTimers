#include "myTrafficLight.h"

/**
     * Constructor.
     * @param tPeriods Traffic light time interval On
     */
myTrafficLight::myTrafficLight(std::vector<t_trafficTimePeriod> tPeriods)
{
    this->_tPeriods = tPeriods;

}

/**
     * Destructor.
     */
myTrafficLight::~myTrafficLight(){}


/**
     * Handle traffic lights.
     * @param t time in seconds
     * @return True if the Time is on the time periods defined
     
     */
bool myTrafficLight::handle(uint16_t t)
{
  
    for(auto p : this->_tPeriods)
    {
        if(t >= p.start && t <= p.end)
            return true;
    }

    return false;

}
