#ifndef COMPLEX_VALUES_H
#define COMPLEX_VALUES_H

#include "values_info.h"

typedef struct
{
	int Re;
	int Im;
} Complex;

extern ValuesInfo* complexInfo;

void InitComplexValuesInfo();

#endif // COMPLEX_VALUES_H
