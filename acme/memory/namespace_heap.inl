#pragma once


CLASS_DECL_ACME void* __PREFIX_HEAP_NAMESPACE(memory_allocate)(memsize size)
{

   return ::HEAP_NAMESPACE::_memory_allocate(size);

}


CLASS_DECL_ACME void* __PREFIX_HEAP_NAMESPACE(memory_count_allocate)(uptr count, memsize size)
{

   return ::HEAP_NAMESPACE::_memory_allocate(count * size);

}


CLASS_DECL_ACME void* __PREFIX_HEAP_NAMESPACE(memory_reallocate)(void* p, memsize size)
{

   return ::HEAP_NAMESPACE::_memory_reallocate(p, size);

}


CLASS_DECL_ACME void __PREFIX_HEAP_NAMESPACE(memory_free)(void* p)
{

   ::HEAP_NAMESPACE::_memory_free(p);

}


CLASS_DECL_ACME memsize __PREFIX_HEAP_NAMESPACE(memory_size)(void* p)
{

   return ::HEAP_NAMESPACE::_memory_size(p);

}


CLASS_DECL_ACME void* __PREFIX_HEAP_NAMESPACE(memory_allocate_debug)(memsize size, i32 nBlockUse, const char* szFileName, i32 nLine)
{

   return ::HEAP_NAMESPACE::_memory_allocate_debug(size, nBlockUse, szFileName, nLine);

}


CLASS_DECL_ACME void* __PREFIX_HEAP_NAMESPACE(memory_reallocate_debug)(void* p, memsize size, i32 nBlockUse, const char* szFileName, i32 nLine)
{

   return ::HEAP_NAMESPACE::_memory_reallocate_debug(p, size, nBlockUse, szFileName, nLine);

}


CLASS_DECL_ACME void __PREFIX_HEAP_NAMESPACE(memory_free_debug)(void* p, i32 nBlockUse)
{

   ::HEAP_NAMESPACE::_memory_free_debug(p, nBlockUse);

}


CLASS_DECL_ACME memsize __PREFIX_HEAP_NAMESPACE(memory_size_debug)(void* p, i32 nBlockUse)
{

   return ::HEAP_NAMESPACE::_memory_size_debug(p, nBlockUse);

}



