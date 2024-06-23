#ifndef VECTOR_H
#define VECTOR_H 

#include "values_info.h"

typedef struct Vector
{
	int dim;
	void* data;
	ValuesInfo* valuesInfo;
} Vector;

Vector* VectorInit(
		ValuesInfo* valuesInfo,
		const int dim
		);

Vector* VectorFromArray(
		ValuesInfo* valuesInfo,
		const int dim,
		const void* array
		);

void VectorFree(Vector** vector);

const void* VectorGet(const Vector* vector, const int index);
void VectorSet(Vector* vector, const int index, const void* value);

void VectorSum(const Vector* vector1, const Vector* vector2, Vector* res);
void VectorDot(const Vector* vector1, const Vector* vector2, void* res);

#endif // VECTOR_H
