#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include "services/APService.h"
#include "controllers/APController.h"

#define SERIAL_BAUD_RATE 115200

const char* ssid = "";
const char* password = "";

AsyncWebServer server(80);
APService apService;
APController apController(apService);

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.println("\n[MAIN] Bluetti Dashboard Starting...");

  if (!LittleFS.begin(true)){
    Serial.println("[MAIN] LittleFS Mount Failed");
    return;
  }

  // Initialize AP Service
  if (!apService.begin()) {
    Serial.println("[MAIN] Failed to initialize AP Service");
  }

  // Connect to WiFi if credentials are provided
  if (strlen(ssid) > 0) {
    WiFi.begin(ssid, password);
    Serial.println("[MAIN] Connecting to WiFi...");
    
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
      delay(500);
      Serial.print(".");
      attempts++;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
      Serial.printf("\n[MAIN] WiFi Connected. IP: %s\n", WiFi.localIP().toString().c_str());
    } else {
      Serial.println("\n[MAIN] WiFi connection failed");
    }
  }

  // Register API routes
  apController.registerRoutes(server);
  
  // Serving static
  server.serveStatic("/js/", LittleFS, "/www/js/");
  server.serveStatic("/favicon.ico", LittleFS, "/www/favicon.ico");

  // Process all other GET requests with index.html
  server.onNotFound([](AsyncWebServerRequest* request) {
    if (request->method() == HTTP_GET) {
      request->send(LittleFS, "/www/index.html");
    } else if (request->method() == HTTP_OPTIONS) {
      request->send(200);
    } else {
      request->send(404);
    }
  });
  

  server.begin();
}

void loop() {
}