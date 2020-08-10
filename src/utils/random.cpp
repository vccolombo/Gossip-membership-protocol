#pragma once

#include <random>

class Random {
   public:
    static float randomFloat(float min, float max) {
        float random = ((float)rand()) / (float)RAND_MAX;
        float diff = max - min;
        float r = random * diff;
        return min + r;
    }
};
