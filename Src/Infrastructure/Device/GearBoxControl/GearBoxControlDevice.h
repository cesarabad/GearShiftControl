#pragma once
#include "../../../Services/Device/Output/OutputDevice.h"
#include "../../../Core/Model/Gear.h"
#include <memory>
#include <string>

class GearBoxControlDevice : public virtual Services::Device::OutputDevice {
private:
    static std::unique_ptr<GearBoxControlDevice> instance_;

    std::string device_function_;

    explicit GearBoxControlDevice(int device_serial_fd, const std::string& device_function);

public:
    GearBoxControlDevice(const GearBoxControlDevice&) = delete;
    GearBoxControlDevice& operator=(const GearBoxControlDevice&) = delete;
    GearBoxControlDevice(GearBoxControlDevice&&) = delete;
    GearBoxControlDevice& operator=(GearBoxControlDevice&&) = delete;

    ~GearBoxControlDevice() override;

    void write(const char* data, size_t size, Core::Model::GearModel::Gear gear) const;
};
