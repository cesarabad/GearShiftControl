#pragma once
#include "../../../../../DeviceDomain/include/Device/Output/OutputDevice.h"
#include "../../../../../DeviceDomain/include/Device/Input/InputDevice.h"
#include "../../../Services/Data/ConcurrentData.h"
#include <memory>
#include <string>
#include <stdexcept>
#include <unistd.h>
#include "../../../Core/Model/Servo.h"

namespace Infrastructure::Device {

class ServoMotorDevice 
    : public ::Device::OutputDevice<Core::Servo::ServoRequest, Core::Servo::ServoResponse>,
      public ::Device::InputDevice<Core::Servo::ServoResponse>
{
public:
    explicit ServoMotorDevice(int device_serial_fd)
        : ::Device::Device(device_serial_fd), 
          ::Device::OutputDevice<Core::Servo::ServoRequest, Core::Servo::ServoResponse>(device_serial_fd),
          ::Device::InputDevice<Core::Servo::ServoResponse>(device_serial_fd, nullptr),
          device_serial_fd_(device_serial_fd)
    {
    }

    ServoMotorDevice(const ServoMotorDevice&) = delete;
    ServoMotorDevice& operator=(const ServoMotorDevice&) = delete;
    ServoMotorDevice(ServoMotorDevice&&) = delete;
    ServoMotorDevice& operator=(ServoMotorDevice&&) = delete;

    ~ServoMotorDevice() override = default;

    // Escribir un comando a un servo específico
    Core::Servo::ServoResponse write(const Core::Servo::ServoRequest& request, uint8_t id) const {
        auto& mutex = Services::Data::ConcurrentData::get_instance().get_shift_mutex();
        std::lock_guard lock(mutex);

        // Creamos una copia del request y asignamos el ID
        Core::Servo::ServoRequest req = request;
        req.id = id;

        ssize_t written = ::write(device_serial_fd_, reinterpret_cast<const char*>(&req), sizeof(req));
        if (written != sizeof(req)) {
            throw std::runtime_error("Failed to write full ServoRequest to device");
        }

        // Leer respuesta si el servo responde al comando
        return read(id);
    }

    // Leer respuesta de un servo específico
    Core::Servo::ServoResponse read(uint8_t id) const {
        auto& mutex = Services::Data::ConcurrentData::get_instance().get_shift_mutex();
        std::lock_guard lock(mutex);

        Core::Servo::ServoResponse response{};
        ssize_t n = ::read(device_serial_fd_, reinterpret_cast<char*>(&response), sizeof(response));
        if (n < 0) {
            throw std::runtime_error("Error reading from ServoMotorDevice");
        }
        if (static_cast<size_t>(n) != sizeof(response)) {
            throw std::runtime_error("Incomplete ServoResponse read from device");
        }

        // Validar que la respuesta corresponda al ID solicitado
        if (response.id != id) {
            throw std::runtime_error("Response ID does not match requested servo ID");
        }

        // Validar header y checksum
        if (response.header1 != 0xFF || response.header2 != 0xFF) {
            throw std::runtime_error("Invalid header in ServoResponse");
        }
        uint8_t calcChecksum = calculateChecksum(response);
        if (calcChecksum != response.checksum) {
            throw std::runtime_error("Checksum mismatch in ServoResponse");
        }

        return response;
    }

private:
    int device_serial_fd_;

    // Calcula checksum según protocolo SCServo
    uint8_t calculateChecksum(const Core::Servo::ServoResponse& resp) const {
        uint16_t sum = resp.id + resp.length + resp.error
                     + resp.data.position + (resp.data.position >> 8)
                     + resp.data.speed + (resp.data.speed >> 8)
                     + resp.data.load + (resp.data.load >> 8)
                     + resp.data.voltage + resp.data.temperature;
        return static_cast<uint8_t>(~sum & 0xFF);
    }
};

} // namespace Infrastructure::Device