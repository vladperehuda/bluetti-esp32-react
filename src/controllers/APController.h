// #ifndef AP_CONTROLLER_H
// #define AP_CONTROLLER_H

// #include <ESPAsyncWebServer.h>
// #include <ArduinoJson.h>
// #include "../services/APService.h"

// /**
//  * @brief REST API controller for Access Point management
//  * 
//  * Provides HTTP endpoints under /api/access-point/* for managing
//  * the Access Point service via REST API.
//  */
// class APController {
// public:
//     /**
//      * @brief Construct a new APController
//      * @param apService Reference to the APService instance
//      */
//     APController(APService& apService);
    
//     /**
//      * @brief Register all routes with the web server
//      * @param server Reference to the AsyncWebServer instance
//      */
//     void registerRoutes(AsyncWebServer& server);

// private:
//     APService& apService_;
    
//     /**
//      * @brief GET /api/access-point/status
//      * Returns current AP status (active, IP, client count)
//      */
//     void handleGetStatus(AsyncWebServerRequest* request);
    
//     /**
//      * @brief GET /api/access-point/settings
//      * Returns current AP settings (SSID, enabled)
//      */
//     void handleGetSettings(AsyncWebServerRequest* request);
    
//     /**
//      * @brief PUT /api/access-point/settings
//      * Update AP settings
//      * Body: { "ssid": "...", "password": "...", "enabled": true/false }
//      */
//     void handleUpdateSettings(AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total);
    
//     /**
//      * @brief POST /api/access-point/start
//      * Start the Access Point
//      */
//     void handleStart(AsyncWebServerRequest* request);
    
//     /**
//      * @brief POST /api/access-point/stop
//      * Stop the Access Point
//      */
//     void handleStop(AsyncWebServerRequest* request);
    
//     /**
//      * @brief POST /api/access-point/reset
//      * Reset AP settings to defaults
//      */
//     void handleReset(AsyncWebServerRequest* request);
    
//     /**
//      * @brief Send JSON error response
//      */
//     void sendError(AsyncWebServerRequest* request, int code, const char* message);
    
//     /**
//      * @brief Send JSON success response
//      */
//     void sendSuccess(AsyncWebServerRequest* request, JsonDocument& doc);
// };

// #endif // AP_CONTROLLER_H
