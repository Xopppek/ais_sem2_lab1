#include "vector.h"

Vector* VectorInit(ValuesInfo* valuesInfo, const int dim){
	if (dim < 1)
		return NULL; // INCORRECT_DIM
	Vector* vector = (Vector*) malloc(sizeof(Vector));
	if (vector == NULL)
		return NULL; // malloc failed
	vector->valuesInfo = valuesInfo;
	vector->dim = dim;
	vector->data = calloc(dim, valuesInfo->size);
	return vector;
}

Vector* VectorFromArray(
		ValuesInfo* valuesInfo, 
		const int dim, 
		const void* array
		){
	// should check if array type corresponds with
	// valuesInfo but I don't know how to do it
	if (dim < 1)
		return NULL; // INCORRECT_DIM
	if (array == NULL)
		return NULL; // NULL_PTR
	Vector* vector = (Vector*) malloc(sizeof(Vector));
	vector->valuesInfo = valuesInfo;
	vector->dim = dim;
	vector->data = malloc(dim * valuesInfo->size);
	memcpy(vector->data, array, dim*valuesInfo->size);
	return vector;	
}

void VectorFree(Vector** vector){
	if (*vector == NULL)
		return;
	free((*vector)->data);
	free(*vector);
	*vector = NULL;
}

void VectorFreeData(Vector* vector){
	if (vector == NULL)
		return;
	free(vector->data);
	vector->data = NULL;
	// if data == NULL vector can not be used
	// this function shouldn't be used by user
	// it is used in lib functions to free
	// data in res vector for functions like Sum
}

const void* VectorGet(const Vector* vector, const int index){
	// the user shouldn't be able to change
	// original element (instead use VectorSet()) 
	// so I had ad idea to return a copy
	// but it can cause some issues with memory I think
	// user will be forced to free memoty by himself
	// so for now it just returns ptr to original data
	if (vector == NULL)
		return NULL; // NULL_PTR
	if (vector->data == NULL)
		return NULL; // NULL_PTR
	if ((vector->dim <= index) || (index < 0))
		return NULL; // OUT_OF_RANGE
	return vector->data + index * vector->valuesInfo->size; 	
}

void VectorSet(Vector* vector, const int index, const void* value){
	// should also somehow check if vector->valuesInfo
	// corresponds with value, but how?
	if (vector == NULL)
		return; // NULL_PTR
	if (vector->data == NULL)
		return; // NULL_PTR
	if ((vector->dim <= index) || (index < 0))
		return; // OUT_OF_RANGE
	vector->valuesInfo->Set(vector->data + 
			index * vector->valuesInfo->size, value);
}

void VectorSum(const Vector* vector1, const Vector* vector2, Vector* res){
	if ((vector1 == NULL) || (vector2 == NULL) || (res == NULL))
		return; // NULL_PTR
	if ((vector1->data == NULL) || (vector2->data == NULL))
		return; // NULL_PTR
	if ((vector1->dim != vector2->dim) ||
		       	(vector2->dim != res->dim))
		return; // DIM_NOT_CORRESPOND
	if ((vector1->valuesInfo != vector2->valuesInfo) ||
			(vector2->valuesInfo != res->valuesInfo))
		return; // VALUES_NOT_CORRESPOND
	int dim = res->dim;
	int elemSize = res->valuesInfo->size;
	if (res->data != NULL)
		VectorFreeData((Vector*) res);
        res->data = malloc(dim * elemSize);
	for (int i = 0; i < dim; i++)
		res->valuesInfo->Sum(
				vector1->data + i * elemSize,
				vector2->data + i * elemSize,
				res->data + i * elemSize
				);	
}

void* VectorDot(const Vector* vector1, const Vector* vector2){
	// there user is forced to free memoty by himself
	// I didn't use (Vector*, Vector*, void* res) like before
	// (it would be more clear for user to free void* res created
	// by himself)
	// because I don't know how to check res type in that case
	// I could probably put something like type information 
	// inside of the type structure, but I didn't actually want to
	// It could cause some issues with new user types
	// Something like hash fuction could be used
	// but again I didn't want to overcomplicate 
	
	// also I probably should've put conjugation function
	// for types to implement correct dot product for
	// something like complex numbers but I didn't do it for now
	// so this fucnction is just sum of pairwise products
	// not exactly the dot product :D
	if ((vector1 == NULL) || (vector2 == NULL))
		return NULL; // NULL_PTR
	if ((vector1->data == NULL) || (vector2->data == NULL))
		return NULL; // NULL_PTR
	if ((vector1->dim != vector2->dim))
		return NULL; // DIM_NOT_CORRESPOND
	if (vector1->valuesInfo != vector2->valuesInfo)
		return NULL; // VALUES_NOT_CORRESPOND
	int dim = vector1->dim;
	ValuesInfo* info = vector1->valuesInfo;
	int elemSize = info->size;
	void* result = malloc(1 * elemSize);
	void* temp = malloc(1 * elemSize);
	info->Mult(vector1->data, vector2->data, result);
	for (int i = 1; i < dim; i++){
		info->Mult(
			vector1->data + i * elemSize,
			vector2->data + i * elemSize,
			temp
			);
		info->Sum(result, temp, result);
	}
	free(temp);
	return result;
}
