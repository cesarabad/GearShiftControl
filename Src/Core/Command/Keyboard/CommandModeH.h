#pragma once
#include "../Command.h"
#include "../../../Core/Model/Configuration/ShiftMode.h"
#include "../../../Services/Data/ConcurrentData.h"
#include <iostream>
#include <memory>

namespace Core::Commands::Keyboard {

    class CommandModeH : public Command {
    public:
        static CommandModeH& get_instance() {
            static CommandModeH instance;
            return instance;
        }

        void execute() override {
            std::cout << "Usando cambio en H\n";
			Services::Data::ConcurrentData::get_instance().get_configuration().ShiftMode_.store(Core::Model::Configuration::ShiftMode::Manual);
        }

    private:
        CommandModeH() = default;
    };

}
