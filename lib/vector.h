#ifndef VECTOR_H
#define VECTOR_H 

#include "values_info.h"
#include <stdlib.h>
#include <string.h>

typedef struct Vector
{
	int dim;
	void* data;
	ValuesInfo* valuesInfo;
} Vector;

Vector* VectorFromArray(
		ValuesInfo* valuesInfo,
		int dim,
		void* array
		);

Vector* VectorInit(
		ValuesInfo* valuesInfo,
		int dim
		);

void* VectorGet(Vector* vector, int index);
void VectorSet(Vector* vector, int index, void* value);

void VectorSum(Vector* vector1, Vector* vector2, Vector* res);
void* VectorDot(Vector* vector1, Vector* vector2); // free after usage
void VectorFree(Vector** vector);

#endif // VECTOR_H
