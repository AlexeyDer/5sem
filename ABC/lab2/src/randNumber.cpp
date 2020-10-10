#include "randNumber.h"

int getRandomInt() {
    int min = -10000;
    int max = 10000;
    static const double randomInt = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
   
    return static_cast<int>(rand() * randomInt * (max - min + 1) + min);
}

float getRandomFloat() {
    float min = -10000;
    float max = 10000;

    float randomFloat = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
    return randomFloat;
}

double getRandomDouble() {
    double min = -10000;
    double max = 10000;

    double f = (double) rand() / RAND_MAX;
    return min + f * (max - min);
}