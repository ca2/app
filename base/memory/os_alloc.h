#pragma once


void * os_alloc(memsize size);
void * os_realloc(void * p, memsize size);
void os_free(void * p);
size_t os_size(void * p);



