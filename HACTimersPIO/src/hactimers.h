/**
 *
 * @file hactimers.h
 * @date 12.12.2021
 * @author Harvy Aronales Costiniano
 *
 * Copyright (c) 2021 Harvy Aronales Costiniano. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifndef __HAC_TIMERS_H_
#define __HAC_TIMERS_H_

/* #region CONSTANT_DEFINITION */
#define HAC_TIMER_DEBUG_PREFIX "[HACTIMERS]"
#define DEFAULT_DURATION_MS 2000    //Default duration in milliseconds
#define DEFAULT_COUNTER_MAX 255     //Default maximum counter

#ifdef DEBUG_ESP_PORT

#define DEBUG_HAC_TIMERS Serial // Custom serial debug
#define DEBUG_MSG_HAC_TIMERS(msg, ...)                   \
    {                                                    \
        DEBUG_HAC_TIMERS.printf(msg, ##__VA_ARGS__); \
    } // Custom serial debug for Serial.printf
#define DEBUG_MSG_HAC_TIMERS_LN(msg)     \
    {                                      \
        DEBUG_HAC_TIMERS.println(msg); \
    } // Custom serial debug for Serial.println
#define DEBUG_MSG_HAC_TIMERS_SERIAL_INIT()  \
    {                                       \
        DEBUG_HAC_TIMERS.begin(115200); \
    } // Serial initialization baud rate
#define DEBUG_CALLBACK_HAC_TIMERS(msg)         \
    {                                          \
        HACTimers::_debug(msg); \
    }

#else

#define DEBUG_MSG_HAC_TIMERS(msg, ...)
#define DEBUG_MSG_HAC_TIMERS_LN(msg)
#define DEBUG_MSG_HAC_TIMERS_SERIAL_INIT()
#define DEBUG_CALLBACK_HAC_TIMERS(msg)

#endif

/* #endregion */

/* #region EXTERNAL_DEPENDENCY */
#include <Arduino.h>
/* #endregion */

/* #region GLOBAL_DECLARATION */
typedef std::function<void()> t_funcHacTimer00;
typedef std::function<void(const char *)> t_funcHacTimer01; 
typedef std::function<void(bool)> t_funcHacTimer02;
typedef std::function<void(uint16)> t_funcHacTimer03; 
typedef std::function<void(unsigned long)> t_funcHacTimer04; 
 

enum TimerModes{
    TICK_TAC = 1,           // Timer which continously tick and tack periodically
    TICK_TOGGLES = 2,       // A tic tac timer which toggles states from on and off and vice versa
    UP_COUNTER = 3,     // A timer which count up with the given frequency
    DOWN_COUNTER = 4,   // A timer which count down with the given frequency
    TIME_OFF_DELAY = 5,     // A timer which delay the turning off of output for a given time 
    TIME_ON_DELAY = 6,      // A timer which delay the turning on of output for a given time
};


/* #endregion */

/* #region CLASS_DECLARATION */
class HACTimers{ 
    public:
        bool timeDelayTrigger;
        HACTimers();
        ~HACTimers();

        /*void setup(
            unsigned long duration,
            TimerModes timerModes           
        );*/

        void setup(
            unsigned long duration = DEFAULT_DURATION_MS,
            TimerModes timerModes = TICK_TAC,
            uint16 countMax = DEFAULT_COUNTER_MAX
            );

        void begin();
        void stop();
        void resume();

        //Loop handle function
        void handle();          
        

        // Event Function Declaration
        void onDebug(t_funcHacTimer01 fn);              // Debug related events
        void onTickTack(t_funcHacTimer00 fn);
        void onTickToggle(t_funcHacTimer02 fn);
        void onCounting(t_funcHacTimer03 fn);
        void onCountingDone(t_funcHacTimer00 fn);
        void onTimerDone(t_funcHacTimer02 fn);
        void onElapse(t_funcHacTimer04 fn);

    private:
        unsigned long _timer = millis();
        unsigned long _duration;
        uint16 _count = 0;
        uint16 _countMax = DEFAULT_COUNTER_MAX;
        TimerModes _timerModes;       
        bool _out = false;        
        bool _cancelFlag = false;

        t_funcHacTimer00 _onTickTackFn;
        t_funcHacTimer01 _onDebugFn;        
        t_funcHacTimer02 _onTickToggleFn;
        t_funcHacTimer03 _onCountingFn;
        t_funcHacTimer00 _onCountingDoneFn;
        t_funcHacTimer02 _onTimerDoneFn;
        t_funcHacTimer04 _onElapseFn;

        //tListGenCbFnHaC1BoolTimersSub _onTimerDoneFn;
        
        //tListGenCbFnHaC1ULIntTimersSub _onElapseFn;

        void _debug(const char *data); // Function prototype declaration for debug function
        void _processTicTac();
        void _processTicTacToggle();
        void _processCounter(bool isUpCounter = true);
        void _processTonDelay();
        void _processTofDelay();

};
/* #endregion */
#endif
