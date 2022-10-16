/* Framework.hpp written by @JEJ */

#pragma once
#include "../includes.hpp"

namespace UI {
    
    char HelpInformation[512];
    std::string GetInput(const char* prompt);
    
    namespace Controls {
        bool GrabInput(const char* prompt);
    }
}
