#include "APService.h"

// Define static constants
const char* APService::DEFAULT_SSID = "Bluetti-ESP32";
const char* APService::DEFAULT_PASSWORD = "";  // Empty = open network
const char* APService::PREF_NAMESPACE = "ap_service";
const char* APService::PREF_KEY_SSID = "ssid";
const char* APService::PREF_KEY_PASSWORD = "password";
const char* APService::PREF_KEY_ENABLED = "enabled";

APService::APService() 
    : ssid_(DEFAULT_SSID),
      password_(DEFAULT_PASSWORD),
      enabled_(DEFAULT_ENABLED),
      active_(false) {
}

APService::~APService() {
    end();
}

bool APService::begin() {
    // Load settings from preferences
    loadSettings();
    
    // Auto-start AP if enabled
    if (enabled_) {
        return start();
    }
    
    return true;
}

void APService::end() {
    stop();
}

bool APService::start() {
    if (active_) {
        Serial.println("[APService] AP already active");
        return true;
    }
    
    Serial.println("[APService] Starting Access Point...");
    Serial.printf("[APService] SSID: %s\n", ssid_.c_str());
    
    bool success;
    if (password_.length() >= 8) {
        // Secured AP
        success = WiFi.softAP(ssid_.c_str(), password_.c_str());
    } else {
        // Open AP
        success = WiFi.softAP(ssid_.c_str());
    }
    
    if (success) {
        active_ = true;
        Serial.printf("[APService] AP started successfully. IP: %s\n", WiFi.softAPIP().toString().c_str());
    } else {
        Serial.println("[APService] Failed to start AP");
    }
    
    return success;
}

void APService::stop() {
    if (!active_) {
        return;
    }
    
    Serial.println("[APService] Stopping Access Point...");
    WiFi.softAPdisconnect(true);
    active_ = false;
}

bool APService::isActive() const {
    return active_;
}

bool APService::setSSID(const String& ssid, bool save) {
    if (ssid.length() == 0 || ssid.length() > 32) {
        Serial.println("[APService] Invalid SSID length (must be 1-32 characters)");
        return false;
    }
    
    ssid_ = ssid;
    
    if (save) {
        saveSettings();
    }
    
    // Restart AP if it's currently active
    if (active_) {
        stop();
        start();
    }
    
    return true;
}

bool APService::setPassword(const String& password, bool save) {
    // Password must be either empty (open network) or at least 8 characters
    if (password.length() > 0 && password.length() < 8) {
        Serial.println("[APService] Invalid password length (must be empty or at least 8 characters)");
        return false;
    }
    
    if (password.length() > 63) {
        Serial.println("[APService] Invalid password length (max 63 characters)");
        return false;
    }
    
    password_ = password;
    
    if (save) {
        saveSettings();
    }
    
    // Restart AP if it's currently active
    if (active_) {
        stop();
        start();
    }
    
    return true;
}

String APService::getSSID() const {
    return ssid_;
}

String APService::getIPAddress() const {
    if (!active_) {
        return "";
    }
    return WiFi.softAPIP().toString();
}

uint8_t APService::getClientCount() const {
    if (!active_) {
        return 0;
    }
    return WiFi.softAPgetStationNum();
}

bool APService::setEnabled(bool enabled, bool save) {
    enabled_ = enabled;
    
    if (save) {
        saveSettings();
    }
    
    // Start or stop AP based on enabled state
    if (enabled_ && !active_) {
        return start();
    } else if (!enabled_ && active_) {
        stop();
    }
    
    return true;
}

bool APService::isEnabled() const {
    return enabled_;
}

bool APService::resetToDefaults() {
    Serial.println("[APService] Resetting to defaults...");
    
    ssid_ = DEFAULT_SSID;
    password_ = DEFAULT_PASSWORD;
    enabled_ = DEFAULT_ENABLED;
    
    saveSettings();
    
    // Restart with defaults if active
    if (active_) {
        stop();
        if (enabled_) {
            start();
        }
    }
    
    return true;
}

void APService::save() {
    saveSettings();
}

void APService::loadSettings() {
    PreferencesManager& prefs = PreferencesManager::getInstance();
    prefs.begin(PREF_NAMESPACE, false);
    
    ssid_ = prefs.getString(PREF_KEY_SSID, DEFAULT_SSID);
    password_ = prefs.getString(PREF_KEY_PASSWORD, DEFAULT_PASSWORD);
    enabled_ = prefs.getBool(PREF_KEY_ENABLED, DEFAULT_ENABLED);
    
    prefs.end();
    
    Serial.println("[APService] Settings loaded from preferences");
    Serial.printf("[APService] SSID: %s, Enabled: %s\n", 
                  ssid_.c_str(), enabled_ ? "true" : "false");
}

void APService::saveSettings() {
    PreferencesManager& prefs = PreferencesManager::getInstance();
    prefs.begin(PREF_NAMESPACE, false);
    
    prefs.putString(PREF_KEY_SSID, ssid_);
    prefs.putString(PREF_KEY_PASSWORD, password_);
    prefs.putBool(PREF_KEY_ENABLED, enabled_);
    
    prefs.end();
    
    Serial.println("[APService] Settings saved to preferences");
}
