#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

#define SERIAL_BAUD_RATE 115200

const char* ssid = "";
const char* password = "";

AsyncWebServer server(80);

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);

  if (!LittleFS.begin(true)){
    Serial.println("LittleFS Mount Failed");
    return;
  }

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println(WiFi.localIP());

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