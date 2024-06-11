#ifndef OBJECTGENERATOR_H
#define OBJECTGENERATOR_H

float **generateObjectArray(int sizeOfObject);

int freeObjectArray(int sizeOfObject, float **objectArray);

int centerObjectArray(int sizeOfObject, float **objectArray);

int transformObjectArrayToSquare(int sizeOfObject, float **objectArray);

int printObjectArray(int sizeOfObject, float **objectArray);

int moveObjectRight(int sizeOfObject, float **objectArray, int displacement);

int moveObjectUp(int sizeOfObject, float **objectArray, int displacement);

int moveObjectFront(int sizeOfObject, float **objectArray, int displacement);

#endif
