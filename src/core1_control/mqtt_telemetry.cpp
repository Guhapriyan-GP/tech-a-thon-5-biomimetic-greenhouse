#include <stdint.h>

// Pragma pack ensures no padding bytes are wasted over the network
#pragma pack(push, 1)
typedef struct {
    uint32_t ts;                   // Unix epoch, 4 Bytes
    int16_t  temp_c_x100;          // e.g. 2731 = 27.31C, 2 Bytes
    uint16_t co2_ppm;              // 2 Bytes
    int16_t  vent_angle_x10;       // e.g. 450 = 45.0deg, 2 Bytes
    uint8_t  status;               // Bit-packed status flags, 1 Byte
    uint16_t grid_power_avoided_w; // Instantaneous watts saved, 2 Bytes
    uint16_t cumulative_wh_saved;  // Rolling counter (resets daily), 2 Bytes
} TelemetryPacket;
#pragma pack(pop)

// Function to construct the payload before MQTT publish
TelemetryPacket build_payload(uint32_t timestamp, float temp_c, uint16_t co2, float angle, uint16_t power_saved) {
    TelemetryPacket packet;
    
    packet.ts = timestamp;
    packet.temp_c_x100 = (int16_t)(temp_c * 100);
    packet.co2_ppm = co2;
    packet.vent_angle_x10 = (int16_t)(angle * 10);
    packet.status = 0x01; 
    packet.grid_power_avoided_w = power_saved;
    packet.cumulative_wh_saved = 0; // Updated dynamically in main loop
    
    return packet;
}