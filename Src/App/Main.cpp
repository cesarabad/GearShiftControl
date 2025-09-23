#include <iostream>
#include <string>

#include "../Services/Mapping/GearProperties/GearPropertiesMapper.h"
#include "../Infrastructure/Configuration/Json/JsonReader.h"
#include "../Services/Data/ConcurrentData.h"
#include "../Infrastructure/Device/DeviceManager.h"
#include "../Infrastructure/Listenner/Keyboard/KeyboardListener.h"
#include "../Infrastructure/Sensor/ClutchHallSensor.h"
#include "../Services/Mapping/Security/SecurityMapper.h"

int main() {
    using namespace Services::Data;
    using namespace Services::Mapping;
    using namespace Infrastructure::Configuration;
    using namespace Services::Device;

    try {

        JsonReader jsonReader("./Res/GearProperties.json");
        std::string jsonContent = jsonReader.read();

        GearPropertiesMapper gearPropertiesMapper;
        auto gearMap = gearPropertiesMapper.deserialize(jsonContent);

        auto& data = ConcurrentData::get_instance();
        data.set_gear_map(gearMap);

        SecurityMapper securityMapper;
        jsonReader.set_path("./Res/Security.json");
		jsonContent = jsonReader.read();
        data.get_configuration().Security = securityMapper.deserialize(jsonContent);

		jsonReader.set_path("./Res/Devices.json");
		jsonContent = jsonReader.read();

        auto& deviceManager = Infrastructure::Device::DeviceManager::get_instance(jsonContent);

        deviceManager.get_keyboard().set_active(true);
        deviceManager.get_gearbox_shifter().set_active(true);

        auto& clutchSensor = Infrastructure::Sensor::ClutchHallSensor::getInstance(0);
        clutchSensor.start();

        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}
