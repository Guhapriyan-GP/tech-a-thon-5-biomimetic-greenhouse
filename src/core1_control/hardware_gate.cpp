#include <stdint.h>

// GPIO Pin definitions for the hardware interlock
const int GPIO_SW_REQUEST = 14;
const int GPIO_WATCHDOG_ALIVE = 15;
const int GPIO_GRID_PRESENT = 16;
const int GPIO_RELAY_ENABLE = 17; // Drives the N-channel MOSFET

// Evaluates the status of the physical 74LS08 AND gate
bool check_hardware_gate(bool software_request, bool watchdog_alive, bool grid_present) {
    
    // The exhaust fan can physically only trigger if ALL conditions are met
    bool relay_enabled = software_request && watchdog_alive && grid_present;
    
    if(relay_enabled) {
        // Assert GPIO HIGH to drive MOSFET -> Optocoupler -> Relay
        return true;
    } else {
        // Drop GPIO LOW to cut power completely
        return false;
    }
}