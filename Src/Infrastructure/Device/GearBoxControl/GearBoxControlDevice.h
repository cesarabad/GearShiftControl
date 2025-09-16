#pragma once
#include "../../../Services/Device/Output/OutputDevice.h"
#include "../../../Core/Model/Gear.h"
#include <memory>
#include <string>

class GearBoxControlDevice : public Services::Device::OutputDevice<Core::Model::GearModel::Gear> {
private:
    static std::unique_ptr<GearBoxControlDevice> instance_;
    std::string device_function_;


public:
    GearBoxControlDevice(const GearBoxControlDevice&) = delete;
    GearBoxControlDevice& operator=(const GearBoxControlDevice&) = delete;
    GearBoxControlDevice(GearBoxControlDevice&&) = delete;
    GearBoxControlDevice& operator=(GearBoxControlDevice&&) = delete;

    ~GearBoxControlDevice() override;

    explicit GearBoxControlDevice(int device_serial_fd, const std::string& device_function);

    void write(const Core::Model::GearModel::Gear& gear) const override;
};
