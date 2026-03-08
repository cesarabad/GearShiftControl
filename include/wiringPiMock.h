// wiringPiMock.h
#pragma once

// Simulación de las constantes de WiringPi
constexpr int INPUT  = 0;
constexpr int OUTPUT = 1;
constexpr int HIGH   = 1;
constexpr int LOW    = 0;
constexpr int PWM_OUTPUT = 2;

inline void pinMode(int, int) {}
inline void digitalWrite(int, int) {}
inline int digitalRead(int) { return 0; }
inline void delay(int) {}
inline void wiringPiSetup() {}