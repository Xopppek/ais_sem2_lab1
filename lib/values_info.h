#ifndef VALUES_INFO_H
#define VALUES_INFO_H
#include <stddef.h>

typedef struct ValuesInfo
{
	size_t size;
	void (*Sum)(const void* a, const void* b, void* res);
	void (*Mult)(const void* a, const void* b, void* res);
	void (*Print)(const void* value);
} ValuesInfo;

#endif // VALUES_INFO_H
