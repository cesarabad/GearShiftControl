#pragma once
#include <unordered_map>
#include <string>
#include "../JsonMapper.h"
#include "../../../Core/Model/Gear.h"
#include <nlohmann/json.hpp>

namespace Services::Mapping {

	using namespace Core::Model::GearModel;

    class GearPropertiesMapper
        : public JsonMapper<std::unordered_map<int, Gear>> {

    public:
        ~GearPropertiesMapper() override = default;

        std::unordered_map<int, Gear>
            deserialize(const std::string& json) const override;
    };

}
