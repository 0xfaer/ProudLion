#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <ctime>

#define _PACK   0

struct Color
{  
    int red;
    int green;
    int blue;
    float alpha;
};

namespace FMath
{
    void* GetClientBaseAddr( ) const {
        return &(*(GetBaseAddress() ));
    }
    
}
