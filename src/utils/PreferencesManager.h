#ifndef PREFERENCES_MANAGER_H
#define PREFERENCES_MANAGER_H

#include <Preferences.h>
#include <Arduino.h>

/**
 * @brief Centralized manager for ESP32 Preferences
 * 
 * This class provides a singleton interface for managing persistent storage
 * across all services. Each service should use its own namespace to avoid conflicts.
 */
class PreferencesManager {
public:
    /**
     * @brief Get the singleton instance
     * @return Reference to the PreferencesManager instance
     */
    static PreferencesManager& getInstance();
    
    /**
     * @brief Open a preferences namespace
     * @param name Namespace name (max 15 characters)
     * @param readOnly If true, open in read-only mode
     * @return true if successful, false otherwise
     */
    bool begin(const char* name, bool readOnly = false);
    
    /**
     * @brief Close the current namespace
     */
    void end();
    
    /**
     * @brief Get a string value
     * @param key Key name
     * @param defaultValue Default value if key doesn't exist
     * @return The value
     */
    String getString(const char* key, const String& defaultValue = "");
    
    /**
     * @brief Set a string value
     * @param key Key name
     * @param value Value to set
     * @return Number of bytes written
     */
    size_t putString(const char* key, const String& value);
    
    /**
     * @brief Get a boolean value
     * @param key Key name
     * @param defaultValue Default value if key doesn't exist
     * @return The value
     */
    bool getBool(const char* key, bool defaultValue = false);
    
    /**
     * @brief Set a boolean value
     * @param key Key name
     * @param value Value to set
     * @return Number of bytes written
     */
    size_t putBool(const char* key, bool value);
    
    /**
     * @brief Get an integer value
     * @param key Key name
     * @param defaultValue Default value if key doesn't exist
     * @return The value
     */
    int getInt(const char* key, int defaultValue = 0);
    
    /**
     * @brief Set an integer value
     * @param key Key name
     * @param value Value to set
     * @return Number of bytes written
     */
    size_t putInt(const char* key, int value);
    
    /**
     * @brief Get an unsigned integer value
     * @param key Key name
     * @param defaultValue Default value if key doesn't exist
     * @return The value
     */
    unsigned int getUInt(const char* key, unsigned int defaultValue = 0);
    
    /**
     * @brief Set an unsigned integer value
     * @param key Key name
     * @param value Value to set
     * @return Number of bytes written
     */
    size_t putUInt(const char* key, unsigned int value);
    
    /**
     * @brief Remove a key from current namespace
     * @param key Key name
     * @return true if successful, false otherwise
     */
    bool remove(const char* key);
    
    /**
     * @brief Clear all keys in current namespace
     * @return true if successful, false otherwise
     */
    bool clear();
    
    /**
     * @brief Check if a key exists
     * @param key Key name
     * @return true if key exists, false otherwise
     */
    bool isKey(const char* key);

private:
    PreferencesManager() {}
    ~PreferencesManager() { preferences_.end(); }
    
    // Prevent copying
    PreferencesManager(const PreferencesManager&) = delete;
    PreferencesManager& operator=(const PreferencesManager&) = delete;
    
    Preferences preferences_;
};

#endif // PREFERENCES_MANAGER_H
