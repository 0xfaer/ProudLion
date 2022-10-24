#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <Windows.h>
#include <Psapi.h>

#include "Interfaces.h"

static struct Memory memory;

static void* findPattern(PCWSTR module, PCSTR pattern, SIZE_T offset)
{
    MODULEINFO moduleInfo;
    HMODULE moduleHandle = GetModuleHandleW(module);

    if (moduleHandle && GetModuleInformation(GetCurrentProcess(), moduleHandle, &moduleInfo, sizeof(moduleInfo))) {
        PCHAR begin = moduleInfo.lpBaseOfDll;
        PCHAR end = begin + moduleInfo.SizeOfImage;

        for (PCHAR c = begin; c != end; c++) {
            bool matched = true;

            for (PCSTR patternIt = pattern, it = c; *patternIt; patternIt++, it++) {
                if (*patternIt != '?' && *it != *patternIt) {
                    matched = false;
                    break;
                }
            }
            if (matched)
                return c + offset;
        }
    }
  
    exit(EXIT_FAILURE);
}

static PVOID _findRelative(int* address)
{
    return (PBYTE)(address + 1) + *address;
}

PVOID* init(VOID);

const struct Memory* Memory(void)
{
    return &memory;
}
