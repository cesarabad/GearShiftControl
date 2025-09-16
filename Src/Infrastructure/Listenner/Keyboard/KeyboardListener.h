#pragma once
#include "../../../Services/Listener/DeviceListener.h"
#include "../../../Infrastructure/Device/DeviceManager.h"
#include "../../../Core/Command/Keyboard/CommandA.h"
#include "../../../Core/Command/Keyboard/CommandB.h"

#include <thread>
#include <iostream>

namespace Services::Listener {

    class KeyboardListener : public DeviceListener {
    public:
        void listen(const std::string& event = "") const override {
            if (listening_) return;
            stopFlag_.store(false);
            listening_ = true;

            listenerThread_ = std::thread([this]() {
                auto& device = Infrastructure::Device::DeviceManager::get_instance().get_keyboard();
                while (!stopFlag_.load()) {
                    std::string input = device.read();
                    if (input.empty()) break; // EOF o error

                    if (input == "a") {
                        std::thread([]() {
                            Core::Commands::CommandA::get_instance().execute();
                            }).detach();
                    }
                    else if (input == "b") {
                        std::thread([]() {
                            Core::Commands::CommandB::get_instance().execute();
                            }).detach();
                    }
                }
                });
        }
    };

}
