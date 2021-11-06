//Created by camilo on 2021-07-23 21:39 BRT <3ThomasBorregaardSørensen!!
#pragma once


CLASS_DECL_ACME void *     string_memory_allocate(memsize size);
CLASS_DECL_ACME void *     string_memory_count_allocate(uptr count, memsize size);
CLASS_DECL_ACME void *     string_memory_reallocate(void* p, memsize nSize);
CLASS_DECL_ACME void       string_memory_free(void* p);
CLASS_DECL_ACME memsize    string_memory_size(void* p);


