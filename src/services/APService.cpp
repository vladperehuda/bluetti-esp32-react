#include "APService.h"

APService::APService() 
    : _ssid(FACTORY_AP_SSID),
      _password(FACTORY_AP_PASSWORD),
      _provisionMode(FACTORY_AP_PROVISION_MODE) {
}

void APService::begin() {
    loadSettings();
}

void APService::loop() {
    handleDNS();
}

void APService::reconfigureAP() {
    _lastManagedAP = millis() - MANAGE_NETWORK_DELAY;
    _forceReconfigureAP = true;
}

void APService::manageAP() {
    WiFiMode_t currentWiFiMode = WiFi.getMode();

    if (_provisionMode == AP_MODE_ALWAYS || (_provisionMode == AP_MODE_DISCONNECTED && WiFi.status() != WL_CONNECTED)) {
        if (_forceReconfigureAP || currentWiFiMode == WIFI_OFF || currentWiFiMode == WIFI_STA) {
            startAP();
        }
    } else if ((currentWiFiMode == WIFI_AP || currentWiFiMode == WIFI_AP_STA) && (_forceReconfigureAP || !WiFi.softAPgetStationNum())) {
        stopAP();
    }

    _forceReconfigureAP = false;
}

void APService::startAP() {
    Serial.println(F("[APService] Starting Access Point"));
    WiFi.softAP(_ssid.c_str(), _password.c_str());

    if (!_dnsServer) {
        IPAddress apIp = WiFi.softAPIP();

        Serial.println(F("[APService] SSID: "));
        Serial.print(_ssid);
        Serial.println(F("[APService] IP: "));
        Serial.print(apIp);

        _dnsServer = new DNSServer;
        _dnsServer->start(DNS_PORT, "*", apIp);
    }
}

void APService::stopAP() {
    if (_dnsServer) {
        Serial.println(F("[APService] Stopping captive portal"));
        _dnsServer->stop();
        delete _dnsServer;
        _dnsServer = nullptr;
    }

    Serial.println(F("[APService] Stopping Access Point"));
    WiFi.softAPdisconnect(true);
}

void APService::handleDNS() {
  if (_dnsServer) {
    _dnsServer->processNextRequest();
  }
}

void APService::loadSettings() {
    PreferencesManager& prefs = PreferencesManager::getInstance();
    prefs.begin(AP_PREF_NAMESPACE, false);
    
    _ssid = prefs.getString(AP_PREF_KEY_SSID, FACTORY_AP_SSID);
    _password = prefs.getString(AP_PREF_KEY_PASSWORD, FACTORY_AP_PASSWORD);
    _provisionMode = prefs.getBool(AP_PREF_KEY_PROVISION_MODE, FACTORY_AP_PROVISION_MODE);
    
    prefs.end();
    
    Serial.println(F("[APService] Settings loaded from preferences"));
}
