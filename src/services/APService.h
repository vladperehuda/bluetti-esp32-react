#ifndef AP_SERVICE_H
#define AP_SERVICE_H

#include "Service.h"
#include <WiFi.h>
#include "../utils/PreferencesManager.h"

/**
 * @brief Service for managing WiFi Access Point
 * 
 * This service handles all Access Point related functionality including:
 * - Starting/stopping the AP
 * - Configuring SSID and password
 * - Storing AP settings in persistent storage
 * - Querying AP status and connected clients
 */
class APService : public Service {
public:
    /**
     * @brief Construct a new APService object
     */
    APService();
    
    /**
     * @brief Destroy the APService object
     */
    ~APService();
    
    /**
     * @brief Initialize the AP service and load settings from preferences
     * @return true if initialization was successful, false otherwise
     */
    bool begin() override;
    
    /**
     * @brief Stop the AP service and cleanup
     */
    void end() override;
    
    /**
     * @brief Start the Access Point with current settings
     * @return true if AP started successfully, false otherwise
     */
    bool start();
    
    /**
     * @brief Stop the Access Point
     */
    void stop();
    
    /**
     * @brief Check if AP is currently active
     * @return true if AP is active, false otherwise
     */
    bool isActive() const;
    
    /**
     * @brief Set the SSID for the Access Point
     * @param ssid The SSID to set
     * @param save If true, save to preferences immediately
     * @return true if successful, false otherwise
     */
    bool setSSID(const String& ssid, bool save = true);
    
    /**
     * @brief Set the password for the Access Point
     * @param password The password to set (min 8 characters, or empty for open AP)
     * @param save If true, save to preferences immediately
     * @return true if successful, false otherwise
     */
    bool setPassword(const String& password, bool save = true);
    
    /**
     * @brief Get the current SSID
     * @return The SSID string
     */
    String getSSID() const;
    
    /**
     * @brief Get the AP IP address
     * @return IP address as string
     */
    String getIPAddress() const;
    
    /**
     * @brief Get the number of connected clients
     * @return Number of connected clients
     */
    uint8_t getClientCount() const;
    
    /**
     * @brief Enable or disable AP mode
     * @param enabled True to enable, false to disable
     * @param save If true, save to preferences immediately
     * @return true if successful, false otherwise
     */
    bool setEnabled(bool enabled, bool save = true);
    
    /**
     * @brief Check if AP mode is enabled in settings
     * @return true if enabled, false otherwise
     */
    bool isEnabled() const;
    
    /**
     * @brief Reset AP settings to defaults
     * @return true if successful, false otherwise
     */
    bool resetToDefaults();
    
    /**
     * @brief Manually save current settings to preferences
     */
    void save();

private:
    // AP Settings
    String ssid_;
    String password_;
    bool enabled_;
    bool active_;
    
    // Default values
    static const char* DEFAULT_SSID;
    static const char* DEFAULT_PASSWORD;
    static const bool DEFAULT_ENABLED = false;
    
    // Preferences namespace and keys
    static const char* PREF_NAMESPACE;
    static const char* PREF_KEY_SSID;
    static const char* PREF_KEY_PASSWORD;
    static const char* PREF_KEY_ENABLED;
    
    /**
     * @brief Load settings from preferences
     */
    void loadSettings();
    
    /**
     * @brief Save settings to preferences
     */
    void saveSettings();
};

#endif // AP_SERVICE_H
