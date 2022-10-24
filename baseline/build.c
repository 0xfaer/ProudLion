#include "../include/includes.h"

struct VmAlloc
{
    PVOID   Base;
    PVOID   KeBaseAddress;
    CHAR*   KeStackDescriptor;

    UINT32  MmAddressSize;
    SIZE_T  length;
};

struct VmEnvironment
{
    struct VmAlloc KeSurface;
    struct VmAlloc KeDrawingLib;
    WNDPROC FWndProc;
    
    PVOID*  VirtualSpace;
    WINAPI* original_func(IDirect3DDevice9* orig_parameter, D3DPRESENT_PARAMETERS* orig_parameter_, const RECTX*, const RECTY*);
};

int main(int argc, char *argv[])
{
    unsigned int *pByteKiller;
    
    /* ... continued */
    
    return 1;
}
