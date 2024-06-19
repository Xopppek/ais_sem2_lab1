#ifndef VALUES_INFO_H
#define VALUES_INFO_H
#include <stddef.h>
#include <stdlib.h>

typedef struct ValuesInfo
{
	size_t size;
	void (*Sum)(void* a, void* b, void* res);
	void (*Mult)(void* a, void* b, void* res);
	void (*Set)(void* ptr, void* value);
} ValuesInfo;

ValuesInfo* InitValuesInfo(
		size_t size,
		void (*Sum)(void* a, void* b, void* res),
		void (*Mult)(void* a, void* b, void* res),
		void (*Set)(void* ptr, void* value)
		);


#endif // VALUES_INFO_H
