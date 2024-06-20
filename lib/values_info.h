#ifndef VALUES_INFO_H
#define VALUES_INFO_H
#include <stddef.h>
#include <stdlib.h>

typedef struct ValuesInfo
{
	size_t size;
	void (*Sum)(const void* a, const void* b, void* res);
	void (*Mult)(const void* a, const void* b, void* res);
	void (*Set)(void* ptr, const void* value);
} ValuesInfo;

ValuesInfo* InitValuesInfo(
		size_t size,
		void (*Sum)(const void* a, const void* b, void* res),
		void (*Mult)(const void* a, const void* b, void* res),
		void (*Set)(void* ptr, const void* value)
		);


#endif // VALUES_INFO_H
