#include "framework.h"





void os_alloc_check_bounds(u8 * point_i32)
{

	uptr * pinteraction = (uptr *)point_i32;

	byte a[256];

	xxf_zeroa(a);

	if (__memcmp(&point[sizeof(uptr)], a, sizeof(a)) != 0)
	{

		output_debug_string("memory corruption before allocation");

	}
	if (__memcmp(&point[sizeof(uptr) + 256 + *pinteraction], a, sizeof(a)) != 0)
	{

		output_debug_string("memory corruption after allocation");

	}

}


void * os_alloc(size_t size)
{

	critical_section_lock synchronouslock(g_pmutexSystemHeap);

	u8 * point = (u8 *)os_impl_alloc(size + 512 + sizeof(uptr));

	__memset(&point[sizeof(uptr)], 0, 256);

	__memset(&point[sizeof(uptr) + 256 + size], 0, 256);

	uptr * pinteraction = (uptr *)point_i32;

	*pinteraction = size;

	return &point[sizeof(uptr) + 256];

}


void * os_realloc(void * pParam, size_t size)
{

	critical_section_lock synchronouslock(g_pmutexSystemHeap);

	u8 * point = &((u8 *)pParam)[-(iptr)((sizeof(uptr) + 256))];

	os_alloc_check_bounds(point);

	point = (u8 *)os_impl_realloc(point, size + 512 + sizeof(uptr));

	__memset(&point[sizeof(uptr)], 0, 256);

	__memset(&point[sizeof(uptr) + 256 + size], 0, 256);

	uptr * pinteraction = (uptr *)point_i32;

	*pinteraction = size;

	return &point[sizeof(uptr) + 256];

}


void os_free(void * pParam)
{

	critical_section_lock synchronouslock(g_pmutexSystemHeap);

	u8 * point = &((u8 *)pParam)[-(iptr)((sizeof(uptr) + 256))];

	os_alloc_check_bounds(point);

	os_impl_free(point);

}





