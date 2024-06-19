#include "integerValues.h"

void IntegerSum(void* a, void* b, void* res){
	((Integer*) res)->value = ((Integer*) a)->value + ((Integer*) b)->value;
}

void IntegerMult(void* a, void* b, void* res){
	((Integer*) res)->value = ((Integer*) a)->value * ((Integer*) b)->value;
}

void IntegerSet(void* ptr, void* value){
	((Integer*) ptr)->value = ((Integer*) value)->value;
}

ValuesInfo* integerInfo = NULL;

void InitIntegerValuesInfo(){
	if (integerInfo == NULL)
		integerInfo = InitValuesInfo(
				sizeof(int),
				IntegerSum,
				IntegerMult,
				IntegerSet
				);
}
