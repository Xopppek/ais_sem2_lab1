#include "integerValues.h"
#include <stdlib.h>
#include <stdio.h>

void IntegerSum(const void* a, const void* b, void* res){
	((Integer*) res)->value = ((Integer*) a)->value + ((Integer*) b)->value;
}

void IntegerMult(const void* a, const void* b, void* res){
	((Integer*) res)->value = ((Integer*) a)->value * ((Integer*) b)->value;
}

void IntegerPrint(const void* value){
	int x = ((Integer*) value)->value;
	printf("%d", x);
}

static ValuesInfo* integerInfo = NULL;

const ValuesInfo* GetIntegerValuesInfo(){
	if (integerInfo == NULL){
		integerInfo = (ValuesInfo*) malloc(sizeof(ValuesInfo));
		integerInfo->size = sizeof(Integer);
		integerInfo->Sum = IntegerSum;
		integerInfo->Mult = IntegerMult;
		integerInfo->Print = IntegerPrint;
	}
	return integerInfo;
}