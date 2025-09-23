#pragma once  
#include "../../../Core/Model/Configuration/SecurityConfiguration.h"  
#include "../JsonMapper.h"  
#include <nlohmann/json.hpp>  

namespace Services::Mapping {  
class SecurityMapper : public JsonMapper<Core::Model::Configuration::SecurityConfiguration> {  
public:  
	~SecurityMapper() override = default;  

	Core::Model::Configuration::SecurityConfiguration deserialize(const std::string& json) const override;  
};  
}