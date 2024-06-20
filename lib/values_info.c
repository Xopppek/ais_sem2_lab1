#include "values_info.h"

ValuesInfo* InitValuesInfo(
		size_t size,
		void (*Sum)(const void* a, const void* b, void* res),
		void (*Mult)(const void* a, const void* b, void* res),
		void (*Set)(void* ptr, const void* value)
		)
{
	ValuesInfo* info = (ValuesInfo*) malloc(sizeof(ValuesInfo));
	info->size = size;
	info->Sum = Sum;
	info->Mult = Mult;
	info->Set = Set;
	return info;
}
