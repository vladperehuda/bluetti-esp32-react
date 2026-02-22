#include "PreferencesManager.h"

PreferencesManager& PreferencesManager::getInstance() {
    static PreferencesManager instance;
    return instance;
}

bool PreferencesManager::begin(const char* name, bool readOnly) {
    return preferences_.begin(name, readOnly);
}

void PreferencesManager::end() {
    preferences_.end();
}

String PreferencesManager::getString(const char* key, const String& defaultValue) {
    return preferences_.getString(key, defaultValue);
}

size_t PreferencesManager::putString(const char* key, const String& value) {
    return preferences_.putString(key, value);
}

bool PreferencesManager::getBool(const char* key, bool defaultValue) {
    return preferences_.getBool(key, defaultValue);
}

size_t PreferencesManager::putBool(const char* key, bool value) {
    return preferences_.putBool(key, value);
}

int PreferencesManager::getInt(const char* key, int defaultValue) {
    return preferences_.getInt(key, defaultValue);
}

size_t PreferencesManager::putInt(const char* key, int value) {
    return preferences_.putInt(key, value);
}

unsigned int PreferencesManager::getUInt(const char* key, unsigned int defaultValue) {
    return preferences_.getUInt(key, defaultValue);
}

size_t PreferencesManager::putUInt(const char* key, unsigned int value) {
    return preferences_.putUInt(key, value);
}

bool PreferencesManager::remove(const char* key) {
    return preferences_.remove(key);
}

bool PreferencesManager::clear() {
    return preferences_.clear();
}

bool PreferencesManager::isKey(const char* key) {
    return preferences_.isKey(key);
}
