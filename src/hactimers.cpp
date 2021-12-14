/**
 *
 * @file hactimers.cpp
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

/* #region SELF_HEADER */
#include "hactimers.h"
/* #endregion */

/* #region CLASS_DEFINITION */
/**
     * Library Constructor.           
     */
HACTimers::HACTimers() {}
/**
     * Library Destructor.           
     */
HACTimers::~HACTimers() {}

/**
     * Timer setup.           
     * @param duration Timer duration in milliseconds
     * @param timerModes Timer modes defined by enum TimerModes
     * @param countMax Max count for Up and down counter
     */
void HACTimers::setup(
    bool timeDelayTrigger,
    unsigned long duration,
    TimerModes timerModes
    )
{
    this->_timeDelayTrigger = timeDelayTrigger;
    this->_duration = duration;
    this->_timerModes = timerModes;
    this->_timer = millis();
}

/**
     * Timer setup.           
     * @param duration Timer duration in milliseconds
     * @param timerModes Timer modes defined by enum TimerModes
     * @param countMax Max count for Up and down counter
     */
void HACTimers::setup(
    unsigned long duration,
    TimerModes timerModes,
    uint16 countMax)
{
    this->_duration = duration;
    this->_timerModes = timerModes;
    this->_countMax = countMax;
    this->_timer = millis();

    DEBUG_CALLBACK_HAC_TIMERS("Timer setup done.");
}

/**
     * Loop handle function
     */

void HACTimers::handle()
{
    if (this->_cancelFlag)
        return;

    switch (this->_timerModes)
    {
    case TICK_TAC:
        this->_processTicTac();
        break;
    case TICK_TOGGLES:
        this->_processTicTacToggle();
        break;
    case UP_COUNTER:
        this->_processCounter(true);
        break;
    case DOWN_COUNTER:
        this->_processCounter(false);
        break;
    case TIME_ON_DELAY:
        this->_processTonDelay();
        break;
    case TIME_OFF_DELAY:
        this->_processTofDelay();
        break;
    default:
        break;
    }

    if (this->_onElapseFn)
        this->_onElapseFn((millis() - this->_timer));
}

/**
     * Begin the timer
     */

void HACTimers::begin()
{
    this->_cancelFlag = false;

    if (this->_timerModes == UP_COUNTER)
        this->_count = 0;
    if (this->_timerModes == DOWN_COUNTER)
        this->_count = this->_countMax;
}

/**
     * Debug Callback function.           
     * @param fn Standard non return function with a const * char parameter.
     */
void HACTimers::onDebug(t_funcHacTimer01 fn)
{
    this->_onDebugFn = fn;
}

/**
     * TicTac Callback function.           
     * @param fn Standard non return function with a const * char parameter.
     */
void HACTimers::onTickTack(t_funcHacTimer00 fn)
{
    this->_onTickTackFn = fn;
}

/**
     * Timer counting.           
     * @param fn Standard non return function with a const * char parameter.
     */
void HACTimers::onCounting(t_funcHacTimer03 fn)
{
    this->_onCountingFn = fn;
}

/**
     * Timer counting done.           
     * @param fn Standard non return function with a const * char parameter.
     */
void HACTimers::onCountingDone(t_funcHacTimer00 fn)
{
    this->_onCountingDoneFn = fn;
}

/**
     * Timer ON or OFF delay done.           
     * @param fn Standard non return function with a const * char parameter.
     */
void HACTimers::onTimerDone(t_funcHacTimer02 fn)
{
    this->_onTimerDoneFn = fn;
}

/**
     * On elapse.           
     * @param fn Standard non return function with a const * char parameter.
     */
void HACTimers::onElapse(t_funcHacTimer04 fn)
{
    this->_onElapseFn = fn;
}

/**
     * TicTac Toggle Callback function.           
     * @param fn Standard non return function with a const * char parameter.
     */
void HACTimers::onTickToggle(t_funcHacTimer02 fn)
{
    this->_onTickToggleFn = fn;
}

/**
     * Debug function.     
     * @param data const char .
     */

void HACTimers::_debug(const char *data)
{
    if (this->_onDebugFn)
        this->_onDebugFn(String(String(HAC_TIMER_DEBUG_PREFIX) + " " + String(data)).c_str());
}

/**
     * Process Tic Tac type timer.     
     */

void HACTimers::_processTicTac()
{

    if ((millis() - this->_timer) >= this->_duration)
    {
        this->_timer = millis();
        if (this->_onTickTackFn)
            this->_onTickTackFn();
    }
}
/**
     * Process Tic Tac toggle type timer.     
     */

void HACTimers::_processTicTacToggle()
{
    if ((millis() - this->_timer) >= this->_duration)
    {
        this->_timer = millis();
        this->_out = !this->_out;
        if (this->_onTickToggleFn)
            this->_onTickToggleFn(this->_out);
    }

}

/**
     * Process Tic Tac toggle type timer.  
     * @param isUpCounter True if is Up Counter, false for Down Counter
     */

void HACTimers::_processCounter(bool isUpCounter)
{
    if ((millis() - this->_timer) >= this->_duration)
    {
        this->_timer = millis();

        if (this->_count == 0 &&
            this->_timerModes == DOWN_COUNTER)
        {
            this->_count = this->_countMax;
            this->_cancelFlag = true;

            if (this->_onCountingDoneFn)
                this->_onCountingDoneFn();

            return;
        }

        if (this->_count == this->_countMax &&
            this->_timerModes == UP_COUNTER)
        {
            this->_count = 0;
            this->_cancelFlag = true;

            if (this->_onCountingDoneFn)
                this->_onCountingDoneFn();

            return;
        }

        if (this->_onCountingFn)
            this->_onCountingFn(this->_count);

        if (isUpCounter)
            this->_count++;
        else
            this->_count--;
    }
}

/**
     * Process time ON delay.     
     */
void HACTimers::_processTonDelay()
{
    if(!this->_timeDelayTrigger) this->_timer = millis();

    if ((millis() - this->_timer) >= this->_duration && this->_timeDelayTrigger)
    {
        if (this->_onTimerDoneFn)
            this->_onTimerDoneFn(this->_timeDelayTrigger);
        this->_cancelFlag = true;
    }
}

/**
     * Process time OFF delay.     
     */
void HACTimers::_processTofDelay()
{
    if(this->_timeDelayTrigger) this->_timer = millis();
    
    if ((millis() - this->_timer) >= this->_duration && !this->_timeDelayTrigger)
    {
        if (this->_onTimerDoneFn)
            this->_onTimerDoneFn(this->_timeDelayTrigger);
        this->_cancelFlag = true;
    }
}

/* #endregion */