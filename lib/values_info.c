#include "values_info.h"

ValuesInfo* InitValuesInfo(
		size_t size,
		void (*Sum)(void* a, void* b, void* res),
		void (*Mult)(void* a, void* b, void* res),
		void (*Set)(void* ptr, void* value)
		)
{
	ValuesInfo* info = (ValuesInfo*) malloc(sizeof(ValuesInfo));
	info->size = size;
	info->Sum = Sum;
	info->Mult = Mult;
	info->Set = Set;
	return info;
}
