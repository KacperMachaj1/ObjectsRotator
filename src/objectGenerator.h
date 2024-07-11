#ifndef OBJECTGENERATOR_H
#define OBJECTGENERATOR_H

float ***generateSquare(int sizeOfObject);

float **generateObjectArray(int sizeOfObject);

int freeObjectArray(int sizeOfObject, float **objectArray);

int centerObjectArray(int sizeOfObject, float **objectArray);

int transformObjectArrayToSquare(int sizeOfObject, float **objectArray);

int printObjectArray(int sizeOfObject, float **objectArray);

int moveObjectRight(int sizeOfObject, float **objectArray, float displacement);

int moveObjectUp(int sizeOfObject, float **objectArray, float displacement);

int moveObjectFront(int sizeOfObject, float **objectArray, float displacement);

int rotateObject(int sizeOfObject, float **objectArray, float *rotationVector);

#endif
