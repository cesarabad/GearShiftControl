#pragma once
#include <string>
#include <memory>
#include <stdexcept>
#include <fcntl.h>
#include <unistd.h>
#include <nlohmann/json.hpp>

#include "./Keyboard/KeyboardDevice.h"
#include "./GearBoxControl/GearBoxControlDevice.h"
#include "./GearBoxShifter/GearBoxShifterDevice.h"
#include "./DeviceConstants.h"

namespace Infrastructure::Device {

    namespace DeviceConst {
        namespace Type {
            inline const std::string Input = "Input";
            inline const std::string Output = "Output";
        }
    }

    class DeviceManager {
    public:
        static DeviceManager& get_instance(const std::string& jsonContent) {
            static DeviceManager instance(jsonContent);
            return instance;
        }

        KeyboardDevice& get_keyboard() {
            if (!keyboard_) throw std::runtime_error("KeyboardDevice not initialized");
            return *keyboard_;
        }

        GearBoxControlDevice& get_gearbox() {
            if (!gearbox_) throw std::runtime_error("GearBoxControlDevice not initialized");
            return *gearbox_;
        }

        GearBoxShifterDevice& get_gearbox_shifter() {
			if (!gearbox_shifter_) throw std::runtime_error("GearBoxShifterDevice not initialized");
			return *gearbox_shifter_;
        }

    private:
        explicit DeviceManager(const std::string& jsonContent) {
            nlohmann::json j = nlohmann::json::parse(jsonContent);
            initialize_devices(j);
        }

        void initialize_devices(const nlohmann::json& j) {

			using namespace Device::DeviceConst::Type;

            for (auto& dev : j) {
                std::string symlink = dev["Symlink"];
                std::string function = dev["Function"];
                std::string type = dev["Type"];

                switch (type) {
                    case INPUT:
                        initialize_input_device(function, symlink);
                        break;

					case OUTPUT:
                        initialize_output_device(function, symlink);
                        break;

					default:
						throw std::invalid_argument("Unknown device type: " + type);
                }
            }
        }

        void initialize_input_device(const std::string& function, const std::string& symlink) {
            
            using namespace Device::DeviceConst::Function;

            switch (function) {
                case READ_KEYBOARD:
                    initialize_keyboard(symlink);
					break;

				case READ_GEARBOX_SHIFTER:
					initialize_gearbox_shifter(symlink);
                    break;

				default:
					throw std::invalid_argument("Unknown input device function: " + function);
            }
        }



        void initialize_output_device(const std::string& function, const std::string& symlink) {

			using namespace Device::DeviceConst::Function;

			switch (function) {
			    case GEARBOX_CONTROL:
				    initialize_gearbox_control(function, symlink);
				    break;

			    default:
				    throw std::invalid_argument("Unknown output device function: " + function);
			}
        }

        std::unique_ptr<KeyboardDevice> keyboard_;
        std::unique_ptr<GearBoxControlDevice> gearbox_;
		std::unique_ptr<GearBoxShifterDevice> gearbox_shifter_;

        void initialize_keyboard(const std::string& symlink) {
            int fd = open(symlink.c_str(), O_RDONLY | O_NONBLOCK);
            if (fd < 0) throw std::runtime_error("Cannot open keyboard device");
            keyboard_ = std::make_unique<KeyboardDevice>(fd);
        }

		void initialize_gearbox_shifter(const std::string& symlink) {
            int fd = open(symlink.c_str(), O_RDONLY | O_NONBLOCK);
            if (fd < 0) throw std::runtime_error("Cannot open gearbox shifter device");
            gearbox_shifter_ = std::make_unique<GearBoxShifterDevice>(fd);
		}

        void initialize_gearbox_control(const std::string& function, const std::string& symlink) {
            int fd = open(symlink.c_str(), O_WRONLY);
            if (fd < 0) throw std::runtime_error("Cannot open gearbox device");
            gearbox_ = std::make_unique<GearBoxControlDevice>(fd, function);
		}
    };

}
