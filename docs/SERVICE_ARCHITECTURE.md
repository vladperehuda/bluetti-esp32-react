# Backend Service Architecture

This document describes the clean service-based architecture for the Bluetti Dashboard backend.

## Architecture Overview

The backend is organized using a service-based architecture where each service handles a specific domain of functionality. All services inherit from the base `Service` interface.

### Base Service Interface

Located in `src/services/Service.h`, this provides a common interface for all services:

```cpp
class Service {
public:
    virtual bool begin() = 0;  // Initialize the service
    virtual void end() = 0;    // Clean up and stop the service
};
```

## APService

The Access Point service manages all WiFi AP functionality.

### Features

- **Enable/Disable AP Mode**: Control whether the AP starts on boot
- **Configure SSID**: Set the network name (1-32 characters)
- **Configure Password**: Set password (8-63 chars) or leave empty for open network
- **Query Status**: Check if AP is active, get IP address, count connected clients
- **Persistent Storage**: All settings are stored in ESP32 Preferences (non-volatile)

### Usage Example

```cpp
#include "services/APService.h"

APService apService;

void setup() {
    // Initialize the service (loads settings and auto-starts if enabled)
    apService.begin();
    
    // Configure AP settings
    apService.setSSID("MyBluetti");
    apService.setPassword("MySecurePass123");
    apService.setEnabled(true);
    
    // Manual start/stop
    apService.start();
    apService.stop();
    
    // Query status
    if (apService.isActive()) {
        Serial.println(apService.getIPAddress());
        Serial.println(apService.getClientCount());
    }
}
```

### Default Settings

- **SSID**: `Bluetti-ESP32`
- **Password**: Empty (open network)
- **Enabled**: `false`

### Preferences Storage

All settings are stored under the namespace `ap_service`:
- `ssid`: Access Point SSID
- `password`: Access Point password
- `enabled`: Whether AP should start on boot

## Future Services

Following the same pattern, you can add:
- **WiFiService**: WiFi client connection management and network scanning
- **WebService**: Web server and API management
- **BluetoothService**: Bluetooth communication
- **DataService**: Data collection and storage
- etc.

Each service should:
1. Inherit from `Service`
2. Implement `begin()` and `end()` methods
3. Store settings in Preferences with its own namespace
4. Provide a clean, focused API for its domain
