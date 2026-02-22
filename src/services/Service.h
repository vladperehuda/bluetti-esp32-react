#ifndef SERVICE_H
#define SERVICE_H

/**
 * @brief Base interface for all services
 * 
 * This abstract class provides a common interface for all services
 * in the application. Each service should implement the begin() and
 * end() methods for initialization and cleanup.
 */
class Service {
public:
    virtual ~Service() {}
    
    /**
     * @brief Initialize the service
     * @return true if initialization was successful, false otherwise
     */
    virtual bool begin() = 0;
    
    /**
     * @brief Clean up and stop the service
     */
    virtual void end() = 0;
};

#endif // SERVICE_H
