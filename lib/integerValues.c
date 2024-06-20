#include "integerValues.h"

void IntegerSum(const void* a, const void* b, void* res){
	((Integer*) res)->value = ((Integer*) a)->value + ((Integer*) b)->value;
}

void IntegerMult(const void* a, const void* b, void* res){
	((Integer*) res)->value = ((Integer*) a)->value * ((Integer*) b)->value;
}

void IntegerSet(void* ptr, const void* value){
	((Integer*) ptr)->value = ((Integer*) value)->value;
}

ValuesInfo* integerInfo = NULL;

void InitIntegerValuesInfo(){
	if (integerInfo == NULL)
		integerInfo = InitValuesInfo(
				sizeof(Integer),
				IntegerSum,
				IntegerMult,
				IntegerSet
				);
}
