#pragma once
#include <cstdint>

namespace Core::Servo {

#pragma pack(push,1)

// Estructura usada por la respuesta
struct ServoStatus
{
    uint16_t position;     // posición actual (0–4095)
    uint16_t speed;        // velocidad actual
    uint16_t load;         // carga / torque aplicado
    uint8_t  voltage;      // voltaje (valor * 0.1V normalmente)
    uint8_t  temperature;  // temperatura en °C
};

// Paquete completo que recibes del servo
struct ServoResponse
{
    uint8_t header1;
    uint8_t header2;
    uint8_t id;
    uint8_t length;
    uint8_t error;
    ServoStatus data;
    uint8_t checksum;
};

// Paquete que envías al servo
struct ServoRequest
{
    uint8_t header1 = 0xFF;   // siempre 0xFF
    uint8_t header2 = 0xFF;   // siempre 0xFF
    uint8_t id;               // ID del servo
    uint8_t length;           // bytes después de length (instruction + params + checksum)
    uint8_t instruction;      // 0x02=READ, 0x03=WRITE, 0x04=WRITE_EX, etc.
    uint8_t param[10];        // parámetros (posición, velocidad, aceleración...)
    uint8_t checksum;         // checksum calculado
};

#pragma pack(pop) // restaura alineación

} // namespace Core::Servo