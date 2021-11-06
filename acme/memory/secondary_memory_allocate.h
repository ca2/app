//Copied by camilo on 2021-07-25 17:37 BRT <3ThomasBorregaardSørensen!!
#pragma once


CLASS_DECL_ACME void *     secondary_memory_allocate(memsize size);
CLASS_DECL_ACME void *     secondary_memory_count_allocate(uptr count, memsize size);
CLASS_DECL_ACME void *     secondary_memory_reallocate(void* p, memsize nSize);
CLASS_DECL_ACME void       secondary_memory_free(void* p);
CLASS_DECL_ACME memsize    secondary_memory_size(void* p);


