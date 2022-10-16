#include "electron_framework.hpp"

bool AttachElectron(const char* exec_name)
{
    cpr::Response res = cpr::Get(
        cpr::Url{"localhost://90272"},
        cpr::Parameters{{"token", "_debugging_canaries_x7a823564d01dd8hj2ec5b72fb0lz"}}
    );
    
    if(res.status_code != 200)
        return false;
    
    return true;
}

struct {
    bool isSafe;
    bool isDeprecated;
    
    std::string path;
} ElectronPath;

class ElectronClient {
 public:
    bool init(int attach_status)
    {
        if(AttachElectron("electronbusybee.exe"))
            return true;
        
        return false;
    }
    
    ElectronPath getInterface(const char* path)
    {
        cpr::Response res = cpr::Get(
            cpr::Url{"localhost://90272"},
            cpr::Parameters{{"interface_xpath", path}}
        );
        
        ElectronPath e;
        
        if(res.status_code != 400)
            e.isSafe = true;
        if(res.status_code != 410)
            e.isDeprecated = true;
        
        e.path = res.text;
        return e;
    }
};
