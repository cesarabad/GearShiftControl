#pragma once
#include "../Command.h"
#include "../../../Services/Data/ConcurrentData.h"
#include "../../../Core/Model/Configuration/ShiftMode.h"
#include <iostream>
#include <memory>

namespace Core::Commands::Keyboard {

    class CommandSimulatedSpeed : public Command {
    public:
        static CommandSimulatedSpeed& get_instance(float simulatedSpeed) {
            static CommandSimulatedSpeed instance;
			instance.simulatedSpeed_ = simulatedSpeed;
            return instance;
        }

        void execute() override {
            Services::Data::ConcurrentData::get_instance().set_current_speed(simulatedSpeed_);
        }

    private:
        CommandSimulatedSpeed() = default;
		float simulatedSpeed_{ 0.0f };
    };

}
