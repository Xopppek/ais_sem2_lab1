#include "utils.h"
#include "integerValues.h"
#include "complexValues.h"
#include <stdio.h>

void VectorPrintInteger(Vector* vector){
	int n = VectorGetDim(vector);
	printf("[");
	for (int i = 0; i < n; i++){
		if (i != n-1)
			printf("%d, ", ((Integer*) VectorGet(vector, i))->value);
		else
			printf("%d]\n", ((Integer*) VectorGet(vector, i))->value);
	}
}

void VectorPrintComplex(Vector* vector){
	int n = VectorGetDim(vector);
	printf("[");
	for (int i = 0; i < n; i++){
		if (i != n-1)
			printf("%d + %di, ", ((Complex*) VectorGet(vector, i))->Re,
					((Complex*) VectorGet(vector, i))->Im);
		else
			printf("%d + %di]\n", ((Complex*) VectorGet(vector, i))->Re,
					((Complex*) VectorGet(vector, i))->Im);

	}
}
