#include "lib/vector.h"
#include "lib/utils.h"
#include "lib/tests.h"
#include "lib/integerValues.h"
#include "lib/complexValues.h"
#include <stdio.h>
#include <stdlib.h>

enum{
	TESTS,
	NEW_VECTOR,
	SET_VALUES,
	GET_VALUES,
	SUM,
	DOT,
	DELETE,
	QUIT
};

void PrintMainKeys(){
	printf("Select option:\n");
	printf("|%d. Run tests\n", TESTS);
	printf("|%d. Create new vector\n", NEW_VECTOR);
	printf("|%d. Set vector values\n", SET_VALUES);
	printf("|%d. Get vector values\n", GET_VALUES);
	printf("|%d. Sum \n", SUM);
	printf("|%d. Dot product\n", DOT);
	printf("|%d. Delete vector\n", DELETE);
	printf("|%d. Quit\n", QUIT);
	printf("\n");
}

void InputVectorIndex(int* index){
	do{
		printf("| Select vector index (1-10): ");
		scanf("%d", index);
		if ((*index < 1) || (*index > 10))
			printf("|| Incorrect index\n");
	}while((*index) < 1 || (*index > 10));
}

void InputInteger(Integer* integer){
	int value;
	scanf("%d", &value);
	integer->value = value;
}

void InputComplex(Complex* z){
	int re, im;
	scanf("%d %d", &re, &im);
	z->Re=re;
	z->Im=im;
}

int main(){
	ValuesInfo* integerInfo = GetIntegerValuesInfo();
	ValuesInfo* complexInfo = GetComplexValuesInfo();

	/*
	// const Get test	
	Integer x = {1};
	Vector* v = VectorInit(integerInfo, 2);
	VectorSet(v, 0, &x);
	VectorPrintInteger(v);
	//Integer* t = VectorGet(v, 0);
	//t->value = 2;
	printf("%d\n", ((Integer*) VectorGet(v, 0))->value);
	VectorPrintInteger(v);
	VectorFree(&v);
	*/

	PrintMainKeys();

	int mainKey = 0;
	int num_vectors = 10;
	
	Vector** vectors = (Vector**) calloc(num_vectors, sizeof(Vector*));
	Vector* sum;	
	
	int input_v_index;
	int v_index;
	int res_v_index;
	int v_index1;
	int v_index2;
	int type;
	int dim;
	ValuesInfo* info;
	ValuesInfo* info1;
	ValuesInfo* info2;
	Integer inputInteger;
	Complex inputComplex;
	Integer* dotInteger = (Integer*) malloc(1 * sizeof(Integer));
	Complex* dotComplex = (Complex*) malloc(1 * sizeof(Complex));

	do{
		printf("Input: ");
		mainKey = getchar();
		while (mainKey == '\n')
			mainKey = getchar();
		mainKey -= '0';	
		printf("\n");
		switch(mainKey){
			case(TESTS):
				RunTests();
				printf("\n");
				break;
			case(NEW_VECTOR):
				printf("Creating new vector\n");
				InputVectorIndex(&input_v_index);
				v_index = input_v_index - 1;
				if (vectors[v_index] != NULL){
					printf("|| Vector with such index already exists\n");
					printf("|| Delete it first, or choose another index\n\n");
					continue;
				}
				do{
					printf("| Select type (1-integer, 2-complex): ");
					scanf("%d", &type);
					if ((type < 1) || (type > 2))
						printf("|| Incorrect type\n");	
				}while((type < 1) || (type > 2));
				do{
					printf("| Select dimention: ");
					scanf("%d", &dim);
					if (dim < 1)
						printf("|| Incorrect dimention\n");
				}while(dim < 1);
				if (type == 1)
					vectors[v_index] = VectorInit(integerInfo, dim);
				else if (type == 2)
					vectors[v_index] = VectorInit(complexInfo, dim);
				if (vectors[v_index] != NULL)
					printf("Vector %d created\n", input_v_index);
				else
					printf("Vector %d wasn't created\n", input_v_index);
				printf("\n");
				break;
			case(SET_VALUES):
				printf("Setting values\n");
				InputVectorIndex(&input_v_index);
				v_index = input_v_index - 1;
				if (vectors[v_index] == NULL){
					printf("|| Vector with such index does not exist\n");
					printf("|| Create it first, or choose another index\n\n");
					continue;
				}
				info = VectorGetValuesInfo(vectors[v_index]);
				for (int i = 0; i < VectorGetDim(vectors[v_index]); i++){
					printf("| Insert %d element: ", i+1);
					if (info == integerInfo){
						InputInteger(&inputInteger);
						VectorSet(vectors[v_index], i, &inputInteger);
					}else if(info == complexInfo){
						InputComplex(&inputComplex);
						VectorSet(vectors[v_index], i, &inputComplex);	
					}
				}
				printf("Vector %d = ", input_v_index);
				VectorPrint(vectors[v_index]);
				printf("\n");
				break;
			case(GET_VALUES):
				printf("Getting values\n");
				InputVectorIndex(&input_v_index);
				v_index = input_v_index - 1;
				if (vectors[v_index] == NULL){
					printf("|| Vector with such index does not exist\n");
					printf("|| Create it first, or choose another index\n\n");
					continue;
				}
				info = VectorGetValuesInfo(vectors[v_index]);
				printf("Vector %d = ", input_v_index);
				VectorPrint(vectors[v_index]);	
				printf("\n");
				break;
			case(SUM):
				printf("Sum of 2 vectors\n");
				do{
					printf("| Press 1 if you want to write result in vector\n");
					printf("| Press 2 if you just want to print result\n");
					scanf("%d", &type);
					if ((type < 1) || (type > 2))
						printf("|| Incorrect input\n");
				}while((type < 1) || (type > 2));
				printf("| Vector a\n");
				InputVectorIndex(&input_v_index);
				v_index1 = input_v_index - 1;
				if (vectors[v_index1] == NULL){
					printf("|| Vector with such index does not exist\n");
					printf("|| Create it first, or choose another index\n\n");
					continue;
				}
				info1 = VectorGetValuesInfo(vectors[v_index1]);
				printf("| Vector a = ");
				VectorPrint(vectors[v_index1]);
				printf("| Vector b\n");
				InputVectorIndex(&input_v_index);
				v_index2 = input_v_index - 1;
				if (vectors[v_index2] == NULL){
					printf("|| Vector with such index does not exist\n");
					printf("|| Create it first, or choose another index\n\n");
					continue;
				}
				info2 = VectorGetValuesInfo(vectors[v_index2]);
				printf("| Vector b = ");
				VectorPrint(vectors[v_index2]);
				if (VectorGetDim(vectors[v_index1]) != VectorGetDim(vectors[v_index2])){
					printf("|| Dimentions do not correspond\n\n");
					continue;
				}
				if (info1 != info2){
					printf("|| Vectors have different types\n\n");
					continue;
				}
				if (type == 1){
					printf("| Result vector\n");
					InputVectorIndex(&input_v_index);
					res_v_index = input_v_index - 1;
					if ((res_v_index == v_index1) || (res_v_index == v_index2)){
						printf("|| Result vector should be different\n\n");
						continue;
					}		
					VectorFree(vectors + res_v_index);
					vectors[res_v_index] = VectorInit(info1, VectorGetDim(vectors[v_index1]));
					VectorSum(vectors[v_index1], vectors[v_index2], vectors[res_v_index]);
					printf("Vector %d = Vector %d + Vector %d = ", res_v_index+1,
							v_index1+1, v_index2+1);
					VectorPrint(vectors[res_v_index]);
				}else if (type == 2){
					sum = VectorInit(info1, VectorGetDim(vectors[v_index1]));		
					VectorSum(vectors[v_index1], vectors[v_index2], sum);
					printf("Vector %d + Vector %d = ", v_index1+1, v_index2+1);
					VectorPrint(sum);
					VectorFree(&sum);
				}
				printf("\n");
				break;
			case(DOT):
				printf("Dot product of 2 vectors\n");
				printf("| Vector a\n");
				InputVectorIndex(&input_v_index);
				v_index1 = input_v_index - 1;
				if (vectors[v_index1] == NULL){
					printf("|| Vector with such index does not exist\n");
					printf("|| Create it first, or choose another index\n\n");
					continue;
				}
				info1 = VectorGetValuesInfo(vectors[v_index1]);
				printf("| Vector a = ");
				VectorPrint(vectors[v_index1]);
				printf("| Vector b\n");
				InputVectorIndex(&input_v_index);
				v_index2 = input_v_index - 1;
				if (vectors[v_index2] == NULL){
					printf("|| Vector with such index does not exist\n");
					printf("|| Create it first, or choose another index\n\n");
					continue;
				}
				info2 = VectorGetValuesInfo(vectors[v_index2]);
				printf("| Vector b = ");
				VectorPrint(vectors[v_index2]);
				if (VectorGetDim(vectors[v_index1]) != VectorGetDim(vectors[v_index2])){
					printf("|| Dimentions do not correspond\n\n");
					continue;
				}
				if (info1 != info2){
					printf("|| Vectors have different types\n\n");
					continue;
				}
				if (info1 == integerInfo){
					VectorDot(vectors[v_index1], vectors[v_index2], dotInteger);
					printf("Vector %d * Vector %d = %d\n\n", v_index1+1, v_index2+1, 
										dotInteger->value);
				}else if (info1 == complexInfo){
					VectorDot(vectors[v_index1], vectors[v_index2], dotComplex);
					printf("Vector %d * Vector %d = %d + %di\n\n", v_index1+1, v_index2+1, 
									dotComplex->Re, dotComplex->Im);
				}
				break;
			case(DELETE):
				printf("Deleting vector\n");
				InputVectorIndex(&input_v_index);
				v_index = input_v_index - 1;
				if (vectors[v_index] == NULL){
					printf("Vector %d does not exist\n\n", input_v_index);
					continue;
				}
				VectorFree(vectors + v_index);
				if (vectors[v_index] == NULL)
					printf("Vector %d deleted\n\n", input_v_index);
				else
					printf("Vector %d was not deleted\n\n", input_v_index);	
				break;
			case(QUIT):
				printf("Goodbye!\n");
				break;
			case('q'-'0'):
				printf("Goodbye!\n");
				break;
			default:
				PrintMainKeys();

		}

	}while ((mainKey != QUIT) && (mainKey != 'q' - '0'));

	for (int i = 0; i < num_vectors; i++)
		VectorFree(vectors + i);
	free(vectors);
	free(dotInteger);
	free(dotComplex);
	free(integerInfo);
	free(complexInfo);
	
	return 0;
}
