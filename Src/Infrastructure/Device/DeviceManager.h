#pragma once
#include <string>
#include <memory>
#include <stdexcept>
#include <fcntl.h>
#include <unistd.h>
#include <nlohmann/json.hpp>
#include "SCServo.h"


#include "./Keyboard/KeyboardDevice.h"
#include "./GearBoxShifter/GearBoxShifterDevice.h"
#include "./DeviceConstants.h"
#include "./ServoMotor/ServoMotorDevice.h"

namespace Infrastructure::Device {

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

        GearBoxShifterDevice& get_gearbox_shifter() {
			if (!gearbox_shifter_) throw std::runtime_error("GearBoxShifterDevice not initialized");
			return *gearbox_shifter_;
        }
        ServoMotorDevice& get_servo_motor_x() {
            if (!servo_motor_x_) throw std::runtime_error("ServoMotorDevice X not initialized");
            return *servo_motor_x_;
        }
        ServoMotorDevice& get_servo_motor_y() {
            if (!servo_motor_y_) throw std::runtime_error("ServoMotorDevice Y not initialized");
            return *servo_motor_y_;
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

                if (symlink != "" && function != "") {
                    initialize_device(function, symlink);
				}
				else {
					throw std::invalid_argument("Unknown device with symlink: " + symlink);
				}
            }
        }

        void initialize_device(const std::string& function, const std::string& symlink) {
            
            using namespace Device::DeviceConst::Function;

            if (function == READ_KEYBOARD) {
                initialize_keyboard(symlink);
            }
			else if (function == READ_GEARBOX_SHIFTER) {
				initialize_gearbox_shifter(symlink);
			}
            else if (function == CONTROL_SERVO_MOTORS) {
                initialize_servo_motors(symlink);
            }

			else {
				throw std::invalid_argument("Unknown input device function: " + function);
			}
        }


        std::unique_ptr<KeyboardDevice> keyboard_;
		std::unique_ptr<GearBoxShifterDevice> gearbox_shifter_;
        std::unique_ptr<ServoMotorDevice> servo_motor_x_;
        std::unique_ptr<ServoMotorDevice> servo_motor_y_;

        void initialize_keyboard(const std::string& symlink) {
            int fd = open(symlink.c_str(), O_RDONLY);
            if (fd < 0) throw std::runtime_error("Cannot open keyboard device");
            keyboard_ = std::make_unique<KeyboardDevice>(fd);
        }

		void initialize_gearbox_shifter(const std::string& symlink) {
            int fd = open(symlink.c_str(), O_RDONLY);
            if (fd < 0) throw std::runtime_error("Cannot open gearbox shifter device");
            gearbox_shifter_ = std::make_unique<GearBoxShifterDevice>(fd);
		}

        void initialize_servo_motors(const std::string& symlink) {
            int fd = open(symlink.c_str(), O_WRONLY);
            if (fd < 0) throw std::runtime_error("Cannot open servo motors device");
            servo_motor_x_ = std::make_unique<ServoMotorDevice>(fd, 1);
            servo_motor_y_ = std::make_unique<ServoMotorDevice>(fd, 2);
        }
    };

}
