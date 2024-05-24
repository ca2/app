//Created by camilo on 2021-07-25 03:20 BRT <3ThomasBorregaardSorensen!!
#pragma once


CLASS_DECL_ACID void *     array_memory_allocate(memsize size);
CLASS_DECL_ACID void *     array_memory_count_allocate(uptr count, memsize size);
CLASS_DECL_ACID void *     array_memory_reallocate(void* p, memsize nSize);
CLASS_DECL_ACID void       array_memory_free(void* p);
CLASS_DECL_ACID memsize    array_memory_size(void* p);




void array_initialize_memory_management(::memory_heap* pheap);

