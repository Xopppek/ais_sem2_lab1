#include "complexValues.h"
#include <stdlib.h>

void ComplexSum(const void* a, const void* b, void* res){
	Complex* a_ = (Complex*) a;
	Complex* b_ = (Complex*) b;
	Complex* res_ = (Complex*) res;
	res_->Re = a_->Re + b_->Re;
	res_->Im = a_->Im + b_->Im;
}

void ComplexMult(const void* a, const void* b, void* res){
	Complex* a_ = (Complex*) a;
	Complex* b_ = (Complex*) b;
	Complex* res_ = (Complex*) res;
	res_->Re = a_->Re * b_->Re - a_->Im * b_->Im;
    res_->Im = a_->Re * b_->Im + b_->Re * a_->Im;
}

void ComplexSet(void* ptr, const void* value){
	((Complex*) ptr)->Re = ((Complex*) value)->Re;
	((Complex*) ptr)->Im = ((Complex*) value)->Im; 
}

static ValuesInfo* complexInfo = NULL;

ValuesInfo* GetComplexValuesInfo(){
	if (complexInfo == NULL){
		complexInfo = (ValuesInfo*) malloc(sizeof(ValuesInfo));
		complexInfo->size = sizeof(Complex);
		complexInfo->Sum = ComplexSum;
		complexInfo->Mult = ComplexMult;
		complexInfo->Set = ComplexSet;
	}
	return complexInfo;
}
