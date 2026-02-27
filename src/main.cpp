#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include "services/APService.h"
// #include "controllers/APController.h"

#define SERIAL_BAUD_RATE 115200

AsyncWebServer server(80);
APService apService;
// APController apController(apService);

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.println("\n[MAIN] Bluetti Dashboard Starting...");

  if (!LittleFS.begin(true)){
    Serial.println("[MAIN] LittleFS Mount Failed");
    return;
  }

  // Initialize WiFi driver
  WiFi.mode(WIFI_OFF);
  WiFi.persistent(false);
  WiFi.setAutoReconnect(false);
  WiFi.mode(WIFI_MODE_MAX);
  WiFi.mode(WIFI_MODE_NULL);

  // Initialize AP Service
  apService.begin();

  // Register API routes
  // apController.registerRoutes(server);
  
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
  apService.loop();
}