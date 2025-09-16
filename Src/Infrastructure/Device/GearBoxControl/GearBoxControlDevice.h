#pragma once
#include "../../../Services/Device/Output/OutputDevice.h"
#include "../../../Core/Model/Gear.h"
#include <memory>
#include <string>
#include <stdexcept>
#include <unistd.h>

namespace Infrastructure::Device {

    class GearBoxControlDevice : public Services::Device::OutputDevice<Core::Model::GearModel::Gear> {
    public:
        explicit GearBoxControlDevice(int device_serial_fd, const std::string& device_function)
            : Services::Device::OutputDevice<Core::Model::GearModel::Gear>(device_serial_fd, device_function)
        {
            if (device_function != "GearBoxControl") {
                throw std::invalid_argument("Invalid device function for GearBoxControlDevice");
            }
        }

        GearBoxControlDevice(const GearBoxControlDevice&) = delete;
        GearBoxControlDevice& operator=(const GearBoxControlDevice&) = delete;
        GearBoxControlDevice(GearBoxControlDevice&&) = delete;
        GearBoxControlDevice& operator=(GearBoxControlDevice&&) = delete;

        ~GearBoxControlDevice() override = default;

        void write(const Core::Model::GearModel::Gear& gear) const override {
            std::string message = "X" + std::to_string(gear.rotation.x) +
                ",Y" + std::to_string(gear.rotation.y) + "\n";

            ::write(device_serial_fd_, message.c_str(), message.size());
        }
    };

}
