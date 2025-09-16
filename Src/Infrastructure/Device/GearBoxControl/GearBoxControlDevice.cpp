#include "GearBoxControlDevice.h"
#include <stdexcept>

std::unique_ptr<GearBoxControlDevice> GearBoxControlDevice::instance_ = nullptr;

GearBoxControlDevice::GearBoxControlDevice(int device_serial_fd, const std::string& device_function)
    : Device(device_serial_fd, device_function), OutputDevice() {
    if (device_function == "GearBoxControl") {
        device_function_ = device_function;
    }
    else {
        throw std::invalid_argument("Invalid device function for GearBoxControlDevice");
    }
}

GearBoxControlDevice::~GearBoxControlDevice() = default;

void GearBoxControlDevice::write(Core::Model::GearModel::Gear& gear) const {

    std::string message = "X" + std::to_string(gear.rotation.x) +
        ",Y" + std::to_string(gear.rotation.y) + "\n";

    ::write(device_serial_fd_, message.c_str(), message.size());
}
