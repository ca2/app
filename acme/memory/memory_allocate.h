//Created by camilo on 2021-07-23 23:12 BRT <3ThomasBorregaardSorensen!!
#pragma once


CLASS_DECL_ACME void * memory_allocate(memsize size);
//CLASS_DECL_ACME void * memory_count_allocate(uptr count, memsize size);
CLASS_DECL_ACME void * memory_reallocate(void * p, memsize size);
CLASS_DECL_ACME void memory_free(void * p);
CLASS_DECL_ACME memsize memory_size(void * p);


CLASS_DECL_ACME void * memory_allocate_debug(memsize size, i32 nType, const char* pszFileName, i32 nLine);
CLASS_DECL_ACME void * memory_reallocate_debug(void * p, memsize size, i32 nType, const char* pszFileName, i32 nLine);
CLASS_DECL_ACME void memory_free_debug(void * p, i32 nType);


//CLASS_DECL_ACME void* manage_memory_reallocate(enum_memory_heap eheap, void* p, memsize nSize);
//CLASS_DECL_ACME void manage_memory_free(enum_memory_heap eheap, void* p);




