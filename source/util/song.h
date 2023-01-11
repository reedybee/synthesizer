#pragma once

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include <util/util.h>

struct Song {
public:
    Song(const char* songFilePath);
    unsigned int songLength;
private:

};