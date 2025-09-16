#include "GearBoxControlDevice.h"
#include <stdexcept>
#include <unistd.h> // ::write

GearBoxControlDevice::GearBoxControlDevice(int device_serial_fd, const std::string& device_function)
    : Device(device_serial_fd, device_function)
{
    if (device_function != "GearBoxControl") {
        throw std::invalid_argument("Invalid device function for GearBoxControlDevice");
    }
}

GearBoxControlDevice::~GearBoxControlDevice() = default;

void GearBoxControlDevice::write(const Core::Model::GearModel::Gear& gear) const {
    std::string message = "X" + std::to_string(gear.rotation.x) +
        ",Y" + std::to_string(gear.rotation.y) + "\n";

    ::write(device_serial_fd_, message.c_str(), message.size());
}
