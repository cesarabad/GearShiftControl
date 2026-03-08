#include "SecurityMapper.h"

namespace Services::Mapping {
	Core::Model::Configuration::SecurityConfiguration
		SecurityMapper::deserialize(const std::string& jsonStr) const {
		Core::Model::Configuration::SecurityConfiguration config;
		try {
			auto json = nlohmann::json::parse(jsonStr);
			config.CheckClutchPressed = json.at("CheckClutchPressed").get<bool>();
			config.CheckSpeedRange = json.at("CheckSpeedRange").get<bool>();
		}
		catch (const std::exception& e) {
			throw std::runtime_error(std::string("Failed to deserialize Security JSON: ") + e.what());
		}
		return config;
	}
}