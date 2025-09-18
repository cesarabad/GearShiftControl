#pragma once

#include <wiringPi.h>
#include <thread>
#include <atomic>
#include <unistd.h>
#include "../../Services/Data/ConcurrentData.h"

class ClutchHallSensor {
private:
    int gpioPin_;
    std::atomic<bool> active_;
    std::thread sensorThread_;

    // Constructor privado
    ClutchHallSensor(int pin)
        : gpioPin_(pin), active_(false) {
    }

    // Loop interno del hilo
    void sensorLoop() {
        while (true) {
            if (active_.load()) {
                int state = digitalRead(gpioPin_);
                bool pressed = (state == HIGH);

                // Actualizamos ConcurrentData
                Services::Data::ConcurrentData::get_instance().set_clutch_pressed(pressed);
            }
            usleep(100000); // 100 ms
        }
    }

public:
    // Singleton
    static ClutchHallSensor& getInstance(int pin = 0) {
        static ClutchHallSensor instance(pin);
        return instance;
    }

    // Prohibimos copias
    ClutchHallSensor(const ClutchHallSensor&) = delete;
    ClutchHallSensor& operator=(const ClutchHallSensor&) = delete;

    void start() {
        wiringPiSetup();
        pinMode(gpioPin_, INPUT);
        if (!sensorThread_.joinable()) {
            sensorThread_ = std::thread(&ClutchHallSensor::sensorLoop, this);
        }
        active_.store(true);
    }

    void setActive(bool value) {
        active_.store(value);
    }

    bool isActive() const {
        return active_.load();
    }

    void stop() {
        active_.store(false);
        if (sensorThread_.joinable())
            sensorThread_.join();
    }

    ~ClutchHallSensor() {
        stop();
    }
};
