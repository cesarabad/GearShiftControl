#pragma once
#include "../Command.h"
#include <iostream>
#include <memory>

namespace Core::Commands {

    class CommandA : public Command {
    public:
        static CommandA& get_instance() {
            static CommandA instance;
            return instance;
        }

        void execute() override {
            std::cout << "CommandA ejecutado (tecla 'a')\n";
        }

    private:
        CommandA() = default;
    };

}
