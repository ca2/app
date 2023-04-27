#include "framework.h"


void os_alloc_check_bounds(u8 * point_i32)
{

	uptr * pinteraction = (uptr *)point_i32;

	byte a[256];

	zero(a);

	if (__memcmp(&point[sizeof(uptr)], a, sizeof(a)) != 0)
	{

		output_debug_string("memory corruption before allocation");

	}
	if (__memcmp(&point[sizeof(uptr) + 256 + *pinteraction], a, sizeof(a)) != 0)
	{

		output_debug_string("memory corruption after allocation");

	}

}


void * __operating_system_memory_size(memsize size)
{

	critical_section_lock synchronouslock(critical_section_system_heap());

	u8 * point = (u8 *)operating_system_memory_allocate(size + 512 + sizeof(uptr));

	memory_set(&point[sizeof(uptr)], 0, 256);

	memory_set(&point[sizeof(uptr) + 256 + size], 0, 256);

	uptr * pinteraction = (uptr *)point_i32;

	*pinteraction = size;

	return &point[sizeof(uptr) + 256];

}


void * __operating_system_memory_reallocate(void * pParam, size_t size)
{

	critical_section_lock synchronouslock(critical_section_system_heap());

	u8 * point = &((u8 *)pParam)[-(iptr)((sizeof(uptr) + 256))];

	os_alloc_check_bounds(point);

	point = (u8 *)operating_system_memory_reallocate(point, size + 512 + sizeof(uptr));

	memory_set(&point[sizeof(uptr)], 0, 256);

	memory_set(&point[sizeof(uptr) + 256 + size], 0, 256);

	uptr * pinteraction = (uptr *)point_i32;

	*pinteraction = size;

	return &point[sizeof(uptr) + 256];

}


void __operating_system_memory_free(void * pParam)
{

	critical_section_lock synchronouslock(critical_section_system_heap());

	u8 * point = &((u8 *)pParam)[-(iptr)((sizeof(uptr) + 256))];

	os_alloc_check_bounds(point);

	operating_system_memory_free(point);

}



