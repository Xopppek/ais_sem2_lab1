#ifndef VECTOR_H
#define VECTOR_H 

#include "values_info.h"

typedef struct Vector Vector;

Vector* VectorInit(ValuesInfo* valuesInfo, int dim);

Vector* VectorFromArray(ValuesInfo* valuesInfo, int dim, 
										const void* array);

void VectorFree(Vector** vector);

const void* VectorGet(const Vector* vector, int index);
void VectorSet(Vector* vector, int index, const void* value);

int VectorGetDim(const Vector* vector);
ValuesInfo* VectorGetValuesInfo(const Vector* vector);

void VectorSum(const Vector* vector1, const Vector* vector2, Vector* res);
void VectorDot(const Vector* vector1, const Vector* vector2, void* res);

#endif // VECTOR_H
