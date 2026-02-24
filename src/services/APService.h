#ifndef AP_SERVICE_H
#define AP_SERVICE_H
#include <DNSServer.h>
#include <WiFi.h>

#include "../utils/PreferencesManager.h"

#ifndef FACTORY_AP_PROVISION_MODE
#define FACTORY_AP_PROVISION_MODE AP_MODE_DISCONNECTED
#endif

#ifndef FACTORY_AP_SSID
#define FACTORY_AP_SSID "bluetti-esp32-#{unique_id}"
#endif

#ifndef FACTORY_AP_PASSWORD
#define FACTORY_AP_PASSWORD "vlad-bluetti"
#endif

#ifndef FACTORY_AP_LOCAL_IP
#define FACTORY_AP_LOCAL_IP "192.168.4.1"
#endif

#define AP_PREF_NAMESPACE "ap_service"
#define AP_PREF_KEY_SSID "ssid"
#define AP_PREF_KEY_PASSWORD "password"
#define AP_PREF_KEY_IP "ip"
#define AP_PREF_KEY_PROVISION_MODE "provision_mode"

#define AP_MODE_ALWAYS 0
#define AP_MODE_DISCONNECTED 1
#define AP_MODE_NEVER 2

#define MANAGE_NETWORK_DELAY 10000
#define DNS_PORT 53

enum APStatus { ACTIVE, INACTIVE };

class APService {
public:
    APService();
    
    void begin();
    void loop();
    APStatus getAPStatus();

private:
    DNSServer* _dnsServer;

    String _ssid;
    String _password;
    int _provisionMode;

    volatile unsigned long _lastManagedAP;
    volatile boolean _forceReconfigureAP;

    void reconfigureAP();
    void manageAP();
    void startAP();
    void stopAP();
    void handleDNS();
    void loadSettings();
};

#endif // AP_SERVICE_H
