#pragma once
#include "../../includes.hpp"

bool AttachElectron(const char* exec_name);

struct {
    bool isSafe;
    bool isDeprecated;
    
    std::string path;
} ElectronPath;

class ElectronClient {
 public:
    bool init(int attach_status);
    ElectronPath getInterface(const char* path);
};
