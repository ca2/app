// Created by camilo on 2023-11-26 19:45 <3ThomasBorregaardSorensen!!
#pragma once


#include "memory_allocate.h"


#if !defined(NO_ACME_MEMORY_MANAGEMENT)


void MEMORY_DECL operator delete(void* p, size_t n) del_throw_spec
{

   ::operator delete(p);

}


#endif


// CLASS_DECL_ACME void task_on_operator_new(void * p, memsize s);


void* MEMORY_DECL operator new(size_t size)
{

   auto p = memory_allocate(size);
   
   return p;

}


void* MEMORY_DECL operator new(size_t nSize, const std::nothrow_t&) noexcept
{

   auto p = memory_allocate(nSize);

//#if REFERENCING_DEBUGGING
//
//   task_on_operator_new(p, nSize);
//
//#endif

   return p;

}


void MEMORY_DECL operator delete(void * p) del_throw_spec
{

   memory_free(p);

}


#ifdef WINDOWS


void* MEMORY_DECL operator new[](size_t nSize)
{

   return ::operator new(nSize);

}


#else


void* MEMORY_DECL operator new[](size_t nSize) new_throw_spec
{

   return ::operator new(nSize);

}


#endif


void* MEMORY_DECL operator new[](size_t size, const std::nothrow_t&) noexcept
{

   return memory_allocate(size);

}


void MEMORY_DECL operator delete[](void * p) del_throw_spec
{

   ::operator delete(p);

}


//#if !defined(_UNIVERSAL_WINDOWS)
//
//
#if defined(UNIVERSAL_WINDOWS) //|| defined(ANDROID)


void* MEMORY_DECL operator new(size_t size, void* p) inplace_new_throw_spec
{

   __UNREFERENCED_PARAMETER(size);

   return p;

}


void MEMORY_DECL operator delete(void * p, void* palloc) del_throw_spec
{

   __UNREFERENCED_PARAMETER(p);
   __UNREFERENCED_PARAMETER(palloc);

}


#endif
//
//
//#endif // _UNIVERSAL_WINDOWS

//
//
//void* MEMORY_DECL operator new (size_t size, const c_class&)
//{
//
//   return memory_allocate(size);
//
//}
//
//
//void* MEMORY_DECL operator new[](size_t size, const c_class&)
//{
//
//   return memory_allocate(size);
//
//}
//
//#ifdef CPP17
//void* MEMORY_DECL operator new(size_t size, std::align_val_t alignment);
//void operator delete(void* ptr, std::align_val_t) noexcept;
//#endif
//
//
//#define C_NEW memory_new(c_class::s_cclass)


#if !defined(NO_ACME_MEMORY_MANAGEMENT)


void* MEMORY_DECL operator new(size_t size, const char * pszFileName, i32 nLine) new_throw_spec
{

   auto p = ::operator new(size, _NORMAL_BLOCK, pszFileName, nLine);

//#if REFERENCING_DEBUGGING
//
//   task_on_operator_new(p, nSize);
//
//#endif

   return p;

}


void* MEMORY_DECL operator new[](size_t size, const char* pszFileName, i32 nLine) new_throw_spec
{

   return ::operator new[](size, _NORMAL_BLOCK, pszFileName, nLine);

}


void MEMORY_DECL operator delete(void * pData, const char* /* pszFileName */, i32 /* nLine */) del_throw_spec
{

   ::operator delete(pData, _NORMAL_BLOCK, nullptr, -1);

}


void MEMORY_DECL operator delete[](void* pData, const char* /* pszFileName */, i32 /* nLine */) del_throw_spec
{

   ::operator delete(pData, _NORMAL_BLOCK, nullptr, -1);

}


void* MEMORY_DECL operator new(size_t size, i32 nType, const char* pszFileName, i32 nLine)
{

#if MEMDLEAK

   auto p = memory_allocate(size);
   //auto p = ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(nSize);

#else

   auto p = memory_allocate_debug(size, nType, pszFileName, nLine);
   //auto p = ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate_debug(nSize, nType, pszFileName, nLine);

#endif

//#if REFERENCING_DEBUGGING
//
//   task_on_operator_new(p, nSize);
//
//#endif

   return p;

}


void MEMORY_DECL operator delete(void* p, i32 nType, const char* /* pszFileName */, i32 /* nLine */)
{

   memory_free_debug(p, nType);

}


void* MEMORY_DECL operator new[](size_t nSize, i32 nType, const char* pszFileName, i32 nLine)
{

   return ::operator new(nSize, nType, pszFileName, nLine);

}


void MEMORY_DECL operator delete[](void* p, i32 nType, const char* pszFileName, i32 nLine)
{

   ::operator delete(p, nType, pszFileName, nLine);

}


#endif


//#endif // __ACME_ASSET_NEW_CPP__



