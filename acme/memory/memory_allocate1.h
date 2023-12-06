//Created by camilo on 2021-07-23 23:12 BRT <3ThomasBorregaardSorensen!!
#pragma once


CLASS_DECL_ACME void *     ::heap::management::memory(::heap::e_memory_main)->allocate(memsize size);
CLASS_DECL_ACME void *     memory_count_allocate(uptr count, memsize size);
CLASS_DECL_ACME void *     memory_reallocate(void* p, memsize nSize);
CLASS_DECL_ACME void       ::heap::management::memory(::heap::e_memory_main)->free(void* p);
CLASS_DECL_ACME memsize    memory_size(void* p);


CLASS_DECL_ACME void* manage_memory_reallocate(enum_memory_heap eheap, void* p, memsize nSize);
CLASS_DECL_ACME void manage_memory_free(enum_memory_heap eheap, void* p);




