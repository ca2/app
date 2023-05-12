#pragma once


void * __operating_system_memory_allocate(memsize size);
void * __operating_system_memory_reallocate(void * p, memsize size);
void __operating_system_memory_free(void * p);
memsize __operating_system_memory_size(void * p);



