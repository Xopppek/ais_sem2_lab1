#ifndef COMPLEX_VALUES_H
#define COMPLEX_VALUES_H

#include "values_info.h"

typedef struct
{
	int Re;
	int Im;
} Complex;

const ValuesInfo* GetComplexValuesInfo(); //get const complex info*

#endif // COMPLEX_VALUES_H
