#ifndef TABLEUTILS_H
#define TABLEUTILS_H

float **createTable(int width, int height);

int freeTable(float **table, int width, int height);

int resetTable(float **table, int width, int height, float newVal);

#endif
