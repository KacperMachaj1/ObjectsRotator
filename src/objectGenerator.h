#ifndef OBJECTGENERATOR_H
#define OBJECTGENERATOR_H

int **generateObjectArray(int sizeOfObject);

int freeObjectArray(int sizeOfObject, int **objectArray);

int centerObjectArray(int sizeOfObject, int **objectArray);

int transformObjectArrayToSquare(int sizeOfObject, int **objectArray);

int printObjectArray(int sizeOfObject, int **objectArray);

int moveObjectRight(int sizeOfObject, int **objectArray, int displacement);

int moveObjectUp(int sizeOfObject, int **objectArray, int displacement);

#endif
