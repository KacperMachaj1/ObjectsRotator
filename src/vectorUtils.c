#include <math.h>

#include "vectorUtils.h"

int rotateVector(float *vector, float *angle)
{
    float sinA = sinf(angle[0] * M_PI / 180);
    float cosA = cosf(angle[0] * M_PI / 180);
    float sinB = sinf(angle[1] * M_PI / 180);
    float cosB = cosf(angle[1] * M_PI / 180);
    float sinC = sinf(angle[2] * M_PI / 180);
    float cosC = cosf(angle[2] * M_PI / 180);
    float x = vector[0];
    float y = vector[1];
    float z = vector[2];

    float newX = x * (cosB * cosC) + y * (sinA * sinB * cosC - cosA * sinC) + z * (cosA * sinB * cosC + sinA * sinC);
    float newY = x * (cosB * sinC) + y * (sinA * sinB * sinC + cosA * cosC) + z * (cosA * sinB * sinC - sinA * cosC);
    float newZ = x * (-sinB) + y * (sinA * cosB) + z * (cosA * cosB);

    vector[0] = newX;
    vector[1] = newY;
    vector[2] = newZ;

    return 0;
}
