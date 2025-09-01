#pragma once

namespace Core::Commands {

    class Command {
    public:
        virtual ~Command() = default;

        virtual void execute() = 0;
    };

}