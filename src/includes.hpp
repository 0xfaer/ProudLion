#pragma once
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <cpr.h>
#include <ctime>

#define CONCAT_IMPL(x, y) x##y
#define MACRO_CONCAT(x, y) CONCAT_IMPL(x, y)
#define PAD(SIZE) BYTE MACRO_CONCAT(_pad, __COUNTER__)[SIZE];

#include "includes/electron/electron_framework.hpp"
#include "includes/electron/discord_sdk/include_me.h"
#include "includes/framework.hpp"

// credits to xen0n for writing electron framework and discord sdk
