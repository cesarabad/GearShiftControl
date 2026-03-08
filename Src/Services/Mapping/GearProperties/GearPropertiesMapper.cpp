#include "GearPropertiesMapper.h"

namespace Services::Mapping {

    std::unordered_map<int, Core::Model::GearModel::Gear>
        GearPropertiesMapper::deserialize(const std::string& jsonStr) const {
        std::unordered_map<int, Core::Model::GearModel::Gear> gearMap;

        try {
            // Parse JSON string
            auto jsonArray = nlohmann::json::parse(jsonStr);

            for (const auto& item : jsonArray) {
                Core::Model::GearModel::Gear gear;

                // Rotation
                gear.rotation.x = item.at("RotationX").get<float>();
                gear.rotation.y = item.at("RotationY").get<float>();

                // Speed limits
                gear.speedLimit.min = item.at("MinSpeed").get<float>();
                gear.speedLimit.max = item.at("MaxSpeed").get<float>();
                gear.speedLimit.maxToReduce = item.at("MaxSpeedToReduce").get<float>();

                // Gear number
                int gearNumber = item.at("GearNumber").get<int>();
				gear.number = gearNumber;
                gearMap[gearNumber] = gear;
            }
        }
        catch (const std::exception& e) {
            throw std::runtime_error(std::string("Failed to deserialize Gear JSON: ") + e.what());
        }

        return gearMap;
    }

}
