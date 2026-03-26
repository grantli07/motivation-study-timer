# Motivation Study Timer 🍅

A Pomodoro-based study timer built on an Arduino Uno with a 16x2 LCD display. Features auto and custom timer modes, motivational messages, rest periods, and session tracking.

---

## Hardware Required

| Component | Quantity |
|-----------|----------|
| Arduino Uno | 1 |
| 16x2 LCD Display | 1 |
| Buzzer | 1 |
| Push Buttons | 3 |
| Jumper Wires | 26 |
| Breadboard | 1 |
| Potentiometer | 1 |

---

## Wiring

| Component | Pin |
|-----------|-----|
| LCD RS | 12 |
| LCD EN | 11 |
| LCD D4 | 5 |
| LCD D5 | 4 |
| LCD D6 | 3 |
| LCD D7 | 2 |
| Buzzer | 10 |
| Select Button | 7 |
| Left Button | 8 |
| Right Button | 9 |

---

## Features

- **Auto Mode** — runs a single 25 minute Pomodoro cycle followed by a 5 minute rest
- **Custom Mode** — choose from 1 to 5 hour sessions made up of multiple Pomodoro cycles
- **Motivational Messages** — rotating messages on the LCD heading during focus time
- **Rest Periods** — automatic rest timer after each focus cycle
- **Session Tracking** — checkpoint screen after each cycle showing total cycles completed and total time studied
- **Summary Screen** — final summary when ending a session

---

## How to Use

1. Power on — a welcome screen plays a startup melody
2. Use the **left/right buttons** to navigate menu options
3. Use the **select button** to confirm a selection
4. Choose **AUTO** for a single Pomodoro cycle or **CUSTOM** to select a multi-hour session
5. After each cycle a checkpoint screen shows your progress
6. Select **YES** on the continue screen to keep going or **NO** to end and view your summary

---

## Dependencies

- [LiquidCrystal](https://www.arduino.cc/reference/en/libraries/liquidcrystal/) — built into the Arduino IDE and PlatformIO

---

## Built With

- [PlatformIO](https://platformio.org/)
- Arduino Uno
