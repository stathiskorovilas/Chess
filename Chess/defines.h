#pragma once

#include <string>
#include <cmath>
#include <stdlib.h>

#ifndef DEFINES_H
#define DEFINES_H



#define ASSET_PATH ".\\assets\\"
#define CANVAS_WH 800




inline float distance(float x1, float y1, float x2, float y2)
{
	float dx = x1 - x2;
	float dy = y1 - y2;

	return sqrtf(dx * dx + dy * dy);
}


#endif