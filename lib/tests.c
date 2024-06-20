#include "tests.h"

void RunTests(){
	InitIntegerValuesInfo();
	InitComplexValuesInfo();
	
	int num_vectors = 11;

	Vector** vectors = calloc(num_vectors, sizeof(Vector*));

	Vector* sum;

	Integer* dot_integer;
	Complex* dot_complex;
	
	int dims[num_vectors];
	
	for (int i = 0; i < num_vectors; i++){
		if (i < 2)
			dims[i] = 2;
		else if (i < 4)
			dims[i] = 3;
		else if (i == 4)
			dims[i] = 2;
		else if (i == 5)
			dims[i] = 0;
		else if (i == 6)
			dims[i] = 1;
		else if (i == 7)
			dims[i]= -2;
		else 
			dims[i] = 4;
	}

	printf("Initialization tests:\n");
	for (int i = 0; i < num_vectors; i++){
		if (i < 9)
			if (i == 4)
				vectors[i] = VectorInit(complexInfo, dims[i]);
			else
				vectors[i] = VectorInit(integerInfo, dims[i]);
		else // last 2 vectors are complex + vec4
			vectors[i] = VectorInit(complexInfo, dims[i]);

		if (i < 2){ // correct dim = 2 integer
			assert(vectors[i]->dim == 2);
			assert(vectors[i]->valuesInfo == integerInfo);
		}
		else if (i < 4){ // correct dim = 3 integer
			assert(vectors[i]->dim == 3);
			assert(vectors[i]->valuesInfo == integerInfo);
		}
		else if (i == 4){
			assert(vectors[i]->dim == 2);
			assert(vectors[i]->valuesInfo == complexInfo);
		}
		else if (i == 5) // incorrect dim = 0
			assert(vectors[i] == NULL);	
		else if (i == 6){ // correct dim = 1
			assert(vectors[i]->dim == 1);	
			assert(vectors[i]->valuesInfo == integerInfo);
		}
		else if (i == 7) // incorrect dim < 0
			assert(vectors[i] == NULL);
		else if (i < 9){ // correct dim = 4 integer
			assert(vectors[i]->dim == 4);
			assert(vectors[i]->valuesInfo == integerInfo);
		}
		else{ // correct dim = 4 complex
			assert(vectors[i]->dim == 4);
			assert(vectors[i]->valuesInfo == complexInfo);
		}

			
		printf("- Test %2d passed\n", i + 1);	
	}

	printf("Initialization[OK]\n\n");
	
	// there will be integers from -5 to 5
	Integer* integers = (Integer*) malloc(11 * sizeof(Integer));
	for (int i = 0; i < 11; i++)
		integers[i].value = i - 5;

	Complex* complexes = (Complex*) malloc(8 * sizeof(Complex));
	for (int i = 0; i < 8; i++){
		if (i < 4){ // z0 = 0 + 2i, z1 = 1 + i,
			    // z2 = 2 + 0i, z3 = 3 - i
			complexes[i].Re = i;
			complexes[i].Im = -i+2;
		}
		else{ // z4 = 0 + 3i, z5 = -1 + 4i
		      // z6 = -2 + 5i, z7 = -3 + 6i
			complexes[i].Re = -i+4;
			complexes[i].Im = i-1;
		}
	}

	printf("GetSet tests:\n");

	for (int i = 0; i < 8; i++){
		switch(i){
			case 0: // correct setted 
				// v0 = [-5, 0], v1 = [4, 1] 
				VectorSet(vectors[0], 0, integers + 0); // -5 + 0 = -5
				VectorSet(vectors[0], 1, integers + 5); // -5 + 5 = 0
									//
				VectorSet(vectors[1], 0, integers + 9); // -5 + 9 = 4
				VectorSet(vectors[1], 1, integers + 6); // -5 + 6 = 1
			
				assert(((Integer*) VectorGet(vectors[0], 0))->value == -5);
				assert(((Integer*) VectorGet(vectors[0], 1))->value == 0);

		       		assert(((Integer*) VectorGet(vectors[1], 0))->value == 4);
				assert(((Integer*) VectorGet(vectors[1], 1))->value == 1);
	
				break;
			case 1: // correct setted from array
				// v2 = [-5, -4, -3], v3 = [0, 1, 2]
				VectorFree(vectors + 2); // need to free because that 
				VectorFree(vectors + 3); // vectors were initialized before

				vectors[2] = VectorFromArray(integerInfo, 3, integers);
				vectors[3] = VectorFromArray(integerInfo, 3, integers + 5);
				
				assert((vectors[2])->dim == 3);
				assert((vectors[3])->dim == 3);

				assert(((Integer*) VectorGet(vectors[2], 0))->value == -5);
				assert(((Integer*) VectorGet(vectors[2], 1))->value == -4);
		       		assert(((Integer*) VectorGet(vectors[2], 2))->value == -3);

				assert(((Integer*) VectorGet(vectors[3], 0))->value == 0);
				assert(((Integer*) VectorGet(vectors[3], 1))->value == 1);
				assert(((Integer*) VectorGet(vectors[3], 2))->value == 2);

				break;
			case 2: // incorrect try to Set in NULL (v5)
				// it actually just checks if program fall
				VectorSet(vectors[5], 0, integers + 1);
				assert(vectors[5] == NULL);
				break;
			case 3: // correct for complex
				// v9 = [0 + 2i, 0+3i, 2, -2 + 5i] = [z0, z4, z2, z6]
				// v10 = [-1 + 4i, 1 + i, -3 + 6i, 3 - i] = [z5, z1, z7, z3] 
				VectorSet(vectors[9], 0, complexes + 0);
				VectorSet(vectors[9], 1, complexes + 4);
				VectorSet(vectors[9], 2, complexes + 2);
				VectorSet(vectors[9], 3, complexes + 6);

				VectorSet(vectors[10], 0, complexes + 5);
				VectorSet(vectors[10], 1, complexes + 1);
				VectorSet(vectors[10], 2, complexes + 7);
				VectorSet(vectors[10], 3, complexes + 3);

				assert(((Complex*) VectorGet(vectors[9], 0))->Re == 0);
				assert(((Complex*) VectorGet(vectors[9], 0))->Im == 2);	
				assert(((Complex*) VectorGet(vectors[9], 1))->Re == 0);
				assert(((Complex*) VectorGet(vectors[9], 1))->Im == 3);
				assert(((Complex*) VectorGet(vectors[9], 2))->Re == 2);
				assert(((Complex*) VectorGet(vectors[9], 2))->Im == 0);
				assert(((Complex*) VectorGet(vectors[9], 3))->Re == -2);
				assert(((Complex*) VectorGet(vectors[9], 3))->Im == 5);

				assert(((Complex*) VectorGet(vectors[10], 0))->Re == -1);
				assert(((Complex*) VectorGet(vectors[10], 0))->Im == 4);
				assert(((Complex*) VectorGet(vectors[10], 1))->Re == 1);
				assert(((Complex*) VectorGet(vectors[10], 1))->Im == 1);
				assert(((Complex*) VectorGet(vectors[10], 2))->Re == -3);
				assert(((Complex*) VectorGet(vectors[10], 2))->Im == 6);
				assert(((Complex*) VectorGet(vectors[10], 3))->Re == 3);
				assert(((Complex*) VectorGet(vectors[10], 3))->Im == -1);
				break;
			case 4: // incorrect try to Get from NULL
				// should return NULL
				assert(VectorGet(vectors[5], 0) == NULL);
				assert(VectorGet(vectors[7], 1) == NULL);
				break;
			case 5: // correct for integer
				// v8 = [3, 1, -4. 2]
				VectorSet(vectors[8], 0, integers + 8); // -5 + 8 = 3
				VectorSet(vectors[8], 1, integers + 6); // -5 + 6 = 1
				VectorSet(vectors[8], 2, integers + 1); // -5 + 1 = -4
				VectorSet(vectors[8], 3, integers + 7); // -5 + 7 = 2

				assert(((Integer*) VectorGet(vectors[8], 0))->value == 3);
				assert(((Integer*) VectorGet(vectors[8], 1))->value == 1);
				assert(((Integer*) VectorGet(vectors[8], 2))->value == -4);
				assert(((Integer*) VectorGet(vectors[8], 3))->value == 2);
				break;
			case 6: // correct for complex
				// v4 = [0 + 2i, 1 + i] = [z0, z1]
				VectorSet(vectors[4], 0, complexes + 0);
				VectorSet(vectors[4], 1, complexes + 1);

				assert(((Complex*) VectorGet(vectors[4], 0))->Re == 0);
				assert(((Complex*) VectorGet(vectors[4], 0))->Im == 2);
				assert(((Complex*) VectorGet(vectors[4], 1))->Re == 1);
				assert(((Complex*) VectorGet(vectors[4], 1))->Im == 1);	
				break;
			case 7: // correct for integer
				// v6 = [1]
				VectorSet(vectors[6], 0, integers + 6); // -5 + 6 = 1

				assert(((Integer*) VectorGet(vectors[6], 0))->value == 1);
				break;
		}

		printf("- Test %d passed\n", i+1);
	}

	printf("GetSet[OK]\n\n");

	// after that part all vectors should be either initialized either NULL (v5, v7)
	
	printf("Sum tests:\n");

	for (int i = 0; i < 6; i++){
		switch(i){
			case 0: // correct integer
				// v0 + v1 = [-5, 0] + [4, 1] = [-1, 1]
				sum = VectorInit(integerInfo, 2);
				VectorSum(vectors[0], vectors[1], sum);

				assert(((Integer*) VectorGet(sum, 0))->value == -1);
				assert(((Integer*) VectorGet(sum, 1))->value == 1);

				VectorFree(&sum);
				break;
			case 1: // incorrect try to Sum vectors with different dim
				// v1 + v3 = [4, 1] + [0, 1, 2]
				// sum vector should stay unchanged [-5, -4]
				sum = VectorFromArray(integerInfo, 2, integers);
				VectorSum(vectors[7], vectors[3], sum);

				assert(((Integer*) VectorGet(sum, 0))->value == -5);
				assert(((Integer*) VectorGet(sum, 1))->value == -4);

				VectorFree(&sum);
				break;
			case 2: // correct complex
				// v9 + v10 = [0 + 2i, 0 + 3i, 2, -2 + 5i] + 
				// + [-1 + 4i, 1 + i, -3 + 6i, 3 - i] =
				// [-1 + 6i, 1 + 4i, -1 + 6i, 1 + 4i]
				sum = VectorInit(complexInfo, 4);
				VectorSum(vectors[9], vectors[10], sum);

				assert(((Complex*) VectorGet(sum, 0))->Re == -1);
				assert(((Complex*) VectorGet(sum, 0))->Im == 6);	
				assert(((Complex*) VectorGet(sum, 1))->Re == 1);
				assert(((Complex*) VectorGet(sum, 1))->Im == 4);
				assert(((Complex*) VectorGet(sum, 2))->Re == -1);
				assert(((Complex*) VectorGet(sum, 2))->Im == 6);
				assert(((Complex*) VectorGet(sum, 3))->Re == 1);
				assert(((Complex*) VectorGet(sum, 3))->Im == 4);

				VectorFree(&sum);
				break;
			case 3: // incorrect try to use Sum with NULL res vector
				// user should correctly initialize res vector
				// before using Sum function
				// test just checks if program falls
				VectorSum(vectors[0], vectors[1], sum);

				assert(sum == NULL);
				break;
			case 4: // incorrect try to Sum vectors with 
				// different values
				// v4 + v0 = [-5, 0]  + [0 + 2i, 1 + i]
				// there is no casting, operation is incorrect
				// sum should stay unchanged [0 + 2i, 1 + i]
				sum = VectorFromArray(complexInfo, 2, complexes);
				VectorSum(vectors[0], vectors[4], sum);

				assert(((Complex*) VectorGet(sum, 0))->Re == 0);
				assert(((Complex*) VectorGet(sum, 0))->Im == 2);
				assert(((Complex*) VectorGet(sum, 1))->Re == 1);
				assert(((Complex*) VectorGet(sum, 1))->Im == 1);

				VectorFree(&sum);
				break;
			case 5: // incorrect res vector has incorrect values type
				// user should correctly initialize res vector
				// v0 + v1 = integers + integers
				// sum should stay unchanged [0 + 2i, 1 + i]
				sum = VectorFromArray(complexInfo, 2, complexes);
				VectorSum(vectors[0], vectors[1], sum);

				assert(((Complex*) VectorGet(sum, 0))->Re == 0);
				assert(((Complex*) VectorGet(sum, 0))->Im == 2);
				assert(((Complex*) VectorGet(sum, 1))->Re == 1);
				assert(((Complex*) VectorGet(sum, 1))->Im == 1);

				VectorFree(&sum);
				break;
		}
		printf("- Test %d passed\n", i+1);
	}

	printf("Sum[OK]\n\n");
	
	printf("Dot tests:\n");
	
	for (int i = 0; i < 6; i++){
		switch(i){
			case 0: // correct integer
				// v0 * v1 = [-5, 0] * [4, 1] = -20	
				dot_integer = (Integer*) VectorDot(vectors[0], vectors[1]);
				
				assert(dot_integer->value == -20);

				free(dot_integer);
				break;
			case 1: // incorrect try to Dot vectors with different dim
				// v1 * v3 = [4, 1] * [0, 1, 2]
				// NULL should be returned
				dot_integer = (Integer*) VectorDot(vectors[7], vectors[3]);

				assert(dot_integer == NULL);

				free(dot_integer);
				break;
			case 2: // correct complex
				// v9 * v10 = [0 + 2i, 0 + 3i, 2, -2 + 5i] + 
				// * [-1 + 4i, 1 + i, -3 + 6i, 3 - i] =
				// -18 + 39i
				dot_complex = (Complex*) VectorDot(vectors[9], vectors[10]);

				assert(dot_complex->Re == -18);
				assert(dot_complex->Im == 30);	
					
				free(dot_complex);
				break;
			case 3: // incorrect try to Dot vectors with 
				// different values
				// v4 * v0 = [-5, 0]  * [0 + 2i, 1 + i]
				// there is no casting, operation is incorrect
				// NULL should be returned
				dot_complex = (Complex*) VectorDot(vectors[0], vectors[4]);

				assert(dot_complex == NULL);

				free(dot_complex);
				break;
			case 4: // incorrect one of the vectors is NULL
				// NULL should be returned
				dot_integer = (Integer*) VectorDot(vectors[3], vectors[5]);
					
				assert(dot_integer == NULL);

				free(dot_integer);
				break;
			case 5: // correct integer
				// v2 * v3 = [-5, -4, -3] * [0, 1, 2] = -10
				dot_integer = (Integer*) VectorDot(vectors[2], vectors[3]);

				assert(dot_integer->value == -10);

				free(dot_integer);
				break;
		}
		printf("- Test %d passed\n", i+1);
	}

	printf("Dot[OK]\n\n");

	printf("All tests passed\n");

	free(complexes);
	free(integers);
	for (int i = 0; i < num_vectors; i++)
		VectorFree(vectors + i);
	free(vectors);	
}
