# Clock and time referance module

## Features

### Sources

Clock has 3 sources that it switches automatically. Two of those sources are external driven by external oscillators with frequency of 32.768kHz.

### Alarms

Clock module also consists of two programmable alarms that, have independent outputs. Each alarm can be programmed to trigger on a specific date and time or can operate cyclicly.

### Seven segment display

Module is equipped with a 4 digit seven segment module to display date and time

### Buttons

There are two buttons to allow user to select what he wants to see on the display. **SHIFT** button alows user to "shift" between date and time mode. The **ALT** button allows to either display seconds (if in time mode) or year (if in date mode).

### Serial interface

#### Info

 - Available over USB
 - Baudrate is 115200

#### Commands

*Note: all command return "OK" on success*

 - get_time_date -> returns time & date in YYYY:MM:DD:HH:MM:SS format
 - set_time HH MM SS
 - set_date YYYY MM DD
 - set_alarm [alarm number] YYYY MM DD HH MM SS (note: -1 means this argument doesn't matter)
 - get_alarm [alarm number] -> return alarm settings
 - en_alarm [alarm number] S (S is 0(disabled) or 1(enabled))

## Goals
 - [x] Use clock source of 32.768kHz
 - [x] Display time on a 4 digit 7 segment display
 - [x] Add alarms
 - [x] Add serial interface
 - [x] Add leap year support
 - [x] Add buttons to enable selecting what to display on screen

## Connections to Raspberry PI Pico

| GPIO | Function |
|------|----------|
| GP2 | Source A |
| GP3 | Source B |
| GP4 | Alarm 0 |
| GP5 | Alarm 1 |
| GP6 | DP segment |
| GP7 | G segment |
| GP8 | F segmant |
| GP9 | E segment |
| GP10 | Digit 4 |
| GP11 | Digit 3 |
| GP12 | Digit 2 |
| GP13 | Digit 1 |
| GP16 | SHIFT |
| GP17 | ALT |
| GP18 | A segment |
| GP19 | B segment |
| GP20 | C segment |
| GP21 | D segment |

## Photos

![time](photos/prototype/IMG_20220126_235642.jpg)
![seconds](photos/prototype/IMG_20220126_235653.jpg)
![date](photos/prototype/IMG_20220126_235651.jpg)
![year](photos/prototype/IMG_20220126_235658.jpg)