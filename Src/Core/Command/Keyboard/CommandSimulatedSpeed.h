#pragma once
#include "../Command.h"
#include "../../../Services/Data/ConcurrentData.h"
#include <iostream>

namespace Core::Commands::Keyboard {

    class CommandSimulatedSpeed : public Command {
    public:
        // Cada llamada crea un objeto independiente
        static CommandSimulatedSpeed get_instance(float simulatedSpeed) {
            CommandSimulatedSpeed instance;
            instance.simulatedSpeed_ = simulatedSpeed;
            return instance;
        }

        void execute() override {
            // Asigna la velocidad simulada al ConcurrentData
            Services::Data::ConcurrentData::get_instance().set_current_speed(simulatedSpeed_);
        }

    private:
        CommandSimulatedSpeed() = default;
        float simulatedSpeed_{ 0.0f };
    };

}
