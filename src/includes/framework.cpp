#include "framework.hpp"

namespace UI {
    
    char HelpInformation[32];    // copy help info to this.
    
    std::string GetInput(const char* prompt) {
        
        std::string     sanitized_input = "";
        char            input_buffer[64];
        
        printf(prompt);
        
        if(fgets(input_buffer, 64, stdin) != NULL)) // should probably add sanitization but im lazy
        {
            sanitized_input.push_back(input_buffer);   
            return sanitized_input;
        }
        
        return sanitized_input;        
    }
    
    namespace Controls {
        bool GrabInput(const char* prompt) {
            char input_buffer[32];
            printf(prompt);
            
            fgets(input_buffer, 1, stdin);
            return 1;
        }
    }
}
