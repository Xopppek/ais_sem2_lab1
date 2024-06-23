#include "utils.h"
#include "integerValues.h"
#include "complexValues.h"
#include <stdio.h>

void VectorPrint(Vector* vector){
	int n = VectorGetDim(vector);
	printf("[");
	for (int i = 0; i < n; i++){
		if (i != n-1){
			VectorGetValuesInfo(vector)->Print(VectorGet(vector, i));
			printf(", ");
		}
		else{
			VectorGetValuesInfo(vector)->Print(VectorGet(vector, i));
			printf("]\n");
		}
	}
}
