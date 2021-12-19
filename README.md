# HACTimers

An event driven Timer for arduino which can be used as:
- **Tic Tac** , the timer will periodically repeat the task at each given duration
- **Tic Tac Toggles** , the timer will periodically repeat the task at each given duration and toggle the output from False to True and vice versa.
- **Up Counter**, the timer will count from 0 to a given max value on a define duration interval for each count.
- **Down Counter**, the timer will count from given max value to 0 on a define duration interval for each count.
- **Time On Delay**, the timer will delay the ON of the output at a given duration.
- **Time Off Delay**, the timer will delay the OFF of the output at a given duration.

The **HACTimers** has a define callbacks for various timer events:
- **onDebug**, 
    If **DEBUG_ESP_PORT** is define then this event will return all the debug define within the library. This will be usefull when troubleshooting and debugging.
- **onTickTack**, 
    This event will be raised when the timer elapse time expired. When the timer elapsed time expired, it will reset the timer. Making it to periodically raised the events at every given duration in milliseconds.
- **onTickToggle**, 
    This event will be raised when the timer elapse time expired and toggle the output from its previous state. When the timer elapsed time expired, it will reset the timer. Making it to periodically raised the events at every given duration in milliseconds.
- **onCounting**, 
    This event will be raised when the timer is counting either up and down.
- **onCountingDone**, 
    This event will be raised when the timer counting is done for both Up and Down Counter mode.
- **onTimerDone**, 
    This event will be raised when the timer for On or Off delay expires.
- **onElapse**, 
    This event will be raised all the time and give the total elapse time since the timer started.


Libary setup function:


```cpp
void setup(
    unsigned long duration = DEFAULT_DURATION_MS,
    TimerModes timerModes = TICK_TAC,
    uint16 countMax = DEFAULT_COUNTER_MAX
    );
```


## Installation
- **Download**: https://github.com/SyntaxHarvy/HACTimers/archive/refs/heads/main.zip
- Arduino Ide:
1. Go to Sketch >> Include Library >> Add .zip library
2. Select the downloaded zip file.
- Others:
1. Unzip and modify the folder name to **HACTimers**
2. Move the modified folder on the designated library of the IDE you are using.

## How to use

- Include the **HACTimers** library to your project(Refer to library example).

```cpp
#include <hactimers.h>
```

- Instantiate:

```cpp
HACTimers gHACTimers;
```

### Different Options of Setting-up.

#### **Option 1** : Tic Tac Timer

- Define the callback functions prototype:

```cpp             
void onTicTacCB();                              

void onTicTacCB(){
  Serial.println("On Tic Tac..");
}

```


- Initialization of the events
```cpp
gHACTimers.onTickTack(onTicTacCB);
```

- Calling the timer default setup (Note: Default timer mode is TICK_TAC).

```cpp
gHACTimers.setup(2000);
```

- Begin the timer.

```cpp
 gHACTimers.begin();
```

#### **Option 2** : Tic Tac Toggle Timer

- Define the callback functions prototype:

```cpp             
void onTickToggleCB(bool out);                          

void onTickToggleCB(bool out)
{
  Serial.println("Out =>" + String(out));
}
```

- Initialization of the events
```cpp
gHACTimers.onTickToggle(onTickToggleCB);
```

- Calling the timer default setup (Note: Default timer mode is TICK_TAC).

```cpp
gHACTimers.setup(2000, TICK_TOGGLES);
```

- Begin the timer.

```cpp
 gHACTimers.begin();
```

#### **Option 3** : Up Counter

- Define the callback functions prototype:

```cpp             
void onCountingCB(uint16 count);
void onCountingDone();

void onCountingCB(uint16 count)
{
  Serial.println("Count =>" + String(count));
}
void onCountingDone()
{
  Serial.println("Counting is done!");
}
```

- Initialization of the events
```cpp
gHACTimers.onCounting(onCountingCB);
gHACTimers.onCountingDone(onCountingDone);  
```

- Calling the timer default setup (Note: Default timer mode is TICK_TAC).

```cpp
gHACTimers.setup(2000, UP_COUNTER, 10);
```

- Begin the timer.

```cpp
 gHACTimers.begin();
```

#### **Option 4** : Down Counter

- Define the callback functions prototype:

```cpp             
void onCountingCB(uint16 count);
void onCountingDone();

void onCountingCB(uint16 count)
{
  Serial.println("Count =>" + String(count));
}
void onCountingDone()
{
  Serial.println("Counting is done!");
}
```

- Initialization of the events
```cpp
gHACTimers.onCounting(onCountingCB);
gHACTimers.onCountingDone(onCountingDone);  
```

- Calling the timer default setup (Note: Default timer mode is TICK_TAC).

```cpp
gHACTimers.setup(2000, DOWN_COUNTER, 10);
```

- Begin the timer.

```cpp
 gHACTimers.begin();
```

#### **Option 5** : Time ON Delay

- Define the callback functions prototype:

```cpp             
void onTimerDoneCB(bool out);
void onElapseCB(unsigned long elapseTime);

void onTimerDoneCB(bool out)
{
  Serial.println("Time delay done, Out =>" + String(out));
}

void onElapseCB(unsigned long elapseTime)
{
  Serial.println("Elapse in milliseconds =>" + String(elapseTime));
}
```

- Initialization of the events
```cpp
gHACTimers.onTimerDone(onTimerDoneCB);
gHACTimers.onElapse(onElapseCB);
```

- Calling the timer default setup (Note: Default timer mode is TICK_TAC).

```cpp
bool onTrigger = true;       //Time on delay start when the trigger goes on
gHACTimers.setup(5000, TIME_ON_DELAY);
gHACTimers.timeDelayTrigger = onTrigger;
```

- Begin the timer.

```cpp
 gHACTimers.begin();
```

#### **Option 6** : Time OFF Delay

- Define the callback functions prototype:

```cpp             
void onTimerDoneCB(bool out);
void onElapseCB(unsigned long elapseTime);

void onTimerDoneCB(bool out)
{
  Serial.println("Time delay done, Out =>" + String(out));
}

void onElapseCB(unsigned long elapseTime)
{
  Serial.println("Elapse in milliseconds =>" + String(elapseTime));
}
```

- Initialization of the events
```cpp
gHACTimers.onTimerDone(onTimerDoneCB);
gHACTimers.onElapse(onElapseCB);
```

- Calling the timer default setup (Note: Default timer mode is TICK_TAC).

```cpp
bool offTrigger = false;       //Time Off delay start when the trigger goes off
gHACTimers.setup(5000, TIME_OFF_DELAY);
gHACTimers.timeDelayTrigger = offTrigger;
```

- Begin the timer.

```cpp
 gHACTimers.begin();
```


### Loop Handling

- Calling the library loop function at the arduino loop routine

```cpp
gHACTimers.handle();
```
## Public Variables

- **timeDelayTrigger**

```cpp
bool timeDelayTrigger;
```

- **timerIndex**

```cpp
uint8_t timerIndex;
```

## Public Function Definitions

- **setup**

```cpp
void setup(
    unsigned long duration = DEFAULT_DURATION_MS,
    TimerModes timerModes = TICK_TAC,
    uint16 countMax = DEFAULT_COUNTER_MAX
    );
```

- **begin**

```cpp
void begin();
```

- **stop**

```cpp
void stop();
```

- **resume**

```cpp
void resume();
```

- **handle**

```cpp
//Loop handle function
void handle(); 
```

- **Events**

```cpp
void onDebug(t_funcHacTimer01 fn);
void onTickTack(t_funcHacTimer00 fn);
void onTickTack(t_funcHacTimer03 fn);
void onTickToggle(t_funcHacTimer02 fn);
void onCounting(t_funcHacTimer03 fn);
void onCountingDone(t_funcHacTimer00 fn);
void onTimerDone(t_funcHacTimer02 fn);
void onElapse(t_funcHacTimer04 fn);
```
