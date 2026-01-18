#pragma once
#include "../../../../../DeviceDomain/include/Device/Output/OutputDevice.h"
#include "../../../Core/Model/Gear.h"
#include "../../../Services/Data/ConcurrentData.h"
#include <memory>
#include <string>
#include <stdexcept>
#include <unistd.h>

namespace Infrastructure::Device {

    class GearBoxControlDevice : public ::Device::OutputDevice<Core::Model::GearModel::Gear>, public ::Device::InputDevice<std::string> {
    public:
        explicit GearBoxControlDevice(int device_serial_fd)
            : ::Device::Device(device_serial_fd), ::Device::OutputDevice<Core::Model::GearModel::Gear>(device_serial_fd),
			::Device::InputDevice<std::string>(device_serial_fd, NULL)
        {}

        GearBoxControlDevice(const GearBoxControlDevice&) = delete;
        GearBoxControlDevice& operator=(const GearBoxControlDevice&) = delete;
        GearBoxControlDevice(GearBoxControlDevice&&) = delete;
        GearBoxControlDevice& operator=(GearBoxControlDevice&&) = delete;

        ~GearBoxControlDevice() override = default;

        void write(const Core::Model::GearModel::Gear& gear) const override {
			::Data::ConcurrentData::get_instance().get_shift_mutex().lock();
            std::string message = "X" + std::to_string(gear.rotation.x) +
                ",Y" + std::to_string(gear.rotation.y) + "\n";

            ::write(device_serial_fd_, message.c_str(), message.size());
        }

		std::string read() const override {
			char buffer[256];
			ssize_t n = ::read(device_serial_fd_, buffer, sizeof(buffer) - 1);
			if (n < 0) {
				throw std::runtime_error("Error reading from GearBoxControlDevice");
			}
			buffer[n] = '\0'; // Null-terminate the string
			return std::string(buffer);
		}
    };

}
