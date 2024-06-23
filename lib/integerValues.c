#include "integerValues.h"
#include <stdlib.h>

void IntegerSum(const void* a, const void* b, void* res){
	((Integer*) res)->value = ((Integer*) a)->value + ((Integer*) b)->value;
}

void IntegerMult(const void* a, const void* b, void* res){
	((Integer*) res)->value = ((Integer*) a)->value * ((Integer*) b)->value;
}

void IntegerSet(void* ptr, const void* value){
	((Integer*) ptr)->value = ((Integer*) value)->value;
}

static ValuesInfo* integerInfo = NULL;

ValuesInfo* GetIntegerValuesInfo(){
	if (integerInfo == NULL){
		integerInfo = (ValuesInfo*) malloc(sizeof(ValuesInfo));
		integerInfo->size = sizeof(Integer);
		integerInfo->Sum = IntegerSum;
		integerInfo->Mult = IntegerMult;
		integerInfo->Set = IntegerSet;
	}
	return integerInfo;
}