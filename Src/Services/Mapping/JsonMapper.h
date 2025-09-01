#pragma once
#include <string>

namespace Services::Mapping {

    template <typename T>
    class JsonMapper {
    public:
        virtual ~JsonMapper() = default;

        virtual T map(const std::string& json) const = 0;
    };

}
