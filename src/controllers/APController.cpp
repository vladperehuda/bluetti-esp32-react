// #include "APController.h"

// APController::APController(APService& apService) 
//     : apService_(apService) {
// }

// void APController::registerRoutes(AsyncWebServer& server) {
//     // GET /api/access-point/status
//     server.on("/api/access-point/status", HTTP_GET, 
//         [this](AsyncWebServerRequest* request) {
//             handleGetStatus(request);
//         }
//     );
    
//     // GET /api/access-point/settings
//     server.on("/api/access-point/settings", HTTP_GET,
//         [this](AsyncWebServerRequest* request) {
//             handleGetSettings(request);
//         }
//     );
    
//     // PUT /api/access-point/settings
//     server.on("/api/access-point/settings", HTTP_PUT,
//         [this](AsyncWebServerRequest* request) {
//             sendSuccess(request, JsonDocument());
//         },
//         NULL,
//         [this](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total) {
//             handleUpdateSettings(request, data, len, index, total);
//         }
//     );
    
//     // POST /api/access-point/start
//     server.on("/api/access-point/start", HTTP_POST,
//         [this](AsyncWebServerRequest* request) {
//             handleStart(request);
//         }
//     );
    
//     // POST /api/access-point/stop
//     server.on("/api/access-point/stop", HTTP_POST,
//         [this](AsyncWebServerRequest* request) {
//             handleStop(request);
//         }
//     );
    
//     // POST /api/access-point/reset
//     server.on("/api/access-point/reset", HTTP_POST,
//         [this](AsyncWebServerRequest* request) {
//             handleReset(request);
//         }
//     );
    
//     Serial.println("[APController] Routes registered");
// }

// void APController::handleGetStatus(AsyncWebServerRequest* request) {
//     JsonDocument doc;
    
//     doc["active"] = apService_.isActive();
//     doc["ip"] = apService_.getIPAddress();
//     doc["clientCount"] = apService_.getClientCount();
    
//     sendSuccess(request, doc);
// }

// void APController::handleGetSettings(AsyncWebServerRequest* request) {
//     JsonDocument doc;
    
//     doc["ssid"] = apService_.getSSID();
//     doc["enabled"] = apService_.isEnabled();
//     // Don't expose password for security
    
//     sendSuccess(request, doc);
// }

// void APController::handleUpdateSettings(AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total) {
//     // Only process on final chunk
//     if (index + len != total) {
//         return;
//     }
    
//     JsonDocument doc;
//     DeserializationError error = deserializeJson(doc, data, len);
    
//     if (error) {
//         sendError(request, 400, "Invalid JSON");
//         return;
//     }
    
//     bool success = true;
//     String errorMsg = "";
    
//     // Update SSID if provided
//     if (doc.containsKey("ssid")) {
//         const char* ssid = doc["ssid"];
//         if (!apService_.setSSID(ssid, false)) {
//             success = false;
//             errorMsg = "Invalid SSID";
//         }
//     }
    
//     // Update password if provided
//     if (doc.containsKey("password") && success) {
//         const char* password = doc["password"];
//         if (!apService_.setPassword(password, false)) {
//             success = false;
//             errorMsg = "Invalid password";
//         }
//     }
    
//     // Update enabled state if provided
//     if (doc.containsKey("enabled") && success) {
//         bool enabled = doc["enabled"];
//         if (!apService_.setEnabled(enabled, false)) {
//             success = false;
//             errorMsg = "Failed to update enabled state";
//         }
//     }
    
//     if (!success) {
//         sendError(request, 400, errorMsg.c_str());
//         return;
//     }
    
//     // Save all changes at once
//     apService_.save();
    
//     JsonDocument responseDoc;
//     responseDoc["message"] = "Settings updated successfully";
//     responseDoc["ssid"] = apService_.getSSID();
//     responseDoc["enabled"] = apService_.isEnabled();
    
//     sendSuccess(request, responseDoc);
// }

// void APController::handleStart(AsyncWebServerRequest* request) {
//     if (apService_.start()) {
//         JsonDocument doc;
//         doc["message"] = "Access Point started";
//         doc["ip"] = apService_.getIPAddress();
//         sendSuccess(request, doc);
//     } else {
//         sendError(request, 500, "Failed to start Access Point");
//     }
// }

// void APController::handleStop(AsyncWebServerRequest* request) {
//     apService_.stop();
    
//     JsonDocument doc;
//     doc["message"] = "Access Point stopped";
//     sendSuccess(request, doc);
// }

// void APController::handleReset(AsyncWebServerRequest* request) {
//     if (apService_.resetToDefaults()) {
//         JsonDocument doc;
//         doc["message"] = "Settings reset to defaults";
//         doc["ssid"] = apService_.getSSID();
//         sendSuccess(request, doc);
//     } else {
//         sendError(request, 500, "Failed to reset settings");
//     }
// }

// void APController::sendError(AsyncWebServerRequest* request, int code, const char* message) {
//     JsonDocument doc;
//     doc["error"] = message;
    
//     String response;
//     serializeJson(doc, response);
    
//     request->send(code, "application/json", response);
// }

// void APController::sendSuccess(AsyncWebServerRequest* request, JsonDocument& doc) {
//     String response;
//     serializeJson(doc, response);
    
//     request->send(200, "application/json", response);
// }
