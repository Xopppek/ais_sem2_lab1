#include "complexValues.h"

void ComplexSum(const void* a, const void* b, void* res){
	((Complex*) res)->Re = ((Complex*) a)->Re + ((Complex*) b)->Re;
	((Complex*) res)->Im = ((Complex*) a)->Im + ((Complex*) b)->Im;
}

void ComplexMult(const void* a, const void* b, void* res){
	((Complex*) res)->Re = ((Complex*) a)->Re * ((Complex*) b)->Re
	       		     - ((Complex*) a)->Im * ((Complex*) b)->Im;
    	((Complex*) res)->Im = ((Complex*) a)->Re * ((Complex*) b)->Im 
			     + ((Complex*) b)->Re * ((Complex*) a)->Im;
}

void ComplexSet(void* ptr, const void* value){
	((Complex*) ptr)->Re = ((Complex*) value)->Re;
	((Complex*) ptr)->Im = ((Complex*) value)->Im; 
}

ValuesInfo* complexInfo = NULL;

void InitComplexValuesInfo(){
	if (complexInfo == NULL)
		complexInfo = InitValuesInfo(
				sizeof(Complex),
				ComplexSum,
				ComplexMult,
				ComplexSet
				);
}
