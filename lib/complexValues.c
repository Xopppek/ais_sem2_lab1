#include "complexValues.h"
#include <stdlib.h>
#include <stdio.h>

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

void ComplexPrint(const void* value){
	Complex* z = (Complex*) value;
	if (z->Im == 0)
		printf("%d", z->Re);
	else
		if (z->Re != 0)
			if (z->Im > 0)
				if (z->Im != 1)
					printf("%d + %di", z->Re, z->Im);
				else 
					printf("%d + i", z->Re);
			else
				if (z->Im != -1)
					printf("%d - %di", z->Re, -1 * z->Im);
				else 
					printf("%d - i", z->Re);
		else 
			if (z->Im == 1)
				printf("i");
			else if (z->Im == -1)
				printf("-i");
			else
				printf("%di", z->Im);
	
}

static ValuesInfo* complexInfo = NULL;

const ValuesInfo* GetComplexValuesInfo(){
	if (complexInfo == NULL){
		complexInfo = (ValuesInfo*) malloc(sizeof(ValuesInfo));
		complexInfo->size = sizeof(Complex);
		complexInfo->Sum = ComplexSum;
		complexInfo->Mult = ComplexMult;
		complexInfo->Print = ComplexPrint;
	}
	return complexInfo;
}
