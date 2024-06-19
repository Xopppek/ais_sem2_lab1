#ifndef INTEGET_VALUES_H
#define INTEGER_VALUES_H

#include "values_info.h"

typedef struct Integer
{
	int value;
} Integer;

extern ValuesInfo* integerInfo;

void InitIntegerValuesInfo();

#endif // INTEGER_VALUES_H
