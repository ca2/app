/* Alloc.h -- Memory allocation functions
2009-02-07 : Igor Pavlov : Public domain */
// from 7-zip on 2010-12-19
#pragma once


CLASS_DECL_ACME void * MyAlloc(size_t size);
CLASS_DECL_ACME void * MyRealloc(void * address, size_t sizeOld, size_t sizeNew);
CLASS_DECL_ACME void MyFree(void *address);



#define __NORMAL_BLOCK    1
#define ___CLIENT_BLOCK (_CLIENT_BLOCK|(0xc0<<16))



#ifdef AAA_WANT_TO_REMOVE

#ifdef XDEBUG

#ifndef ___NO_DEBUG_CRT

CLASS_DECL_ACME void * __alloc_memory_debug(size_t nSize, bool bIsObject,  const ::file::path & path, int nLine);

CLASS_DECL_ACME void __free_memory_debug(void * pbData, bool bIsObject);

CLASS_DECL_ACME bool __default_alloc_hook(size_t, bool, int);

// A failure hook returns whether to permit allocation
typedef bool (* __ALLOC_HOOK)(size_t nSize, bool bObject, int lRequestNumber);

// set __allocate< hook, return old  >(never nullptr)
//CLASS_DECL_ACME __ALLOC_HOOK __set_alloc_hook(__ALLOC_HOOK pfnAllocHook);


CLASS_DECL_ACME int __cdecl __alloc_alloc_hook(int nAllocType, void * pvData, size_t nSize, int nBlockUse, long lRequest, const uchar * szFilename, int nLine);
CLASS_DECL_ACME __ALLOC_HOOK __set_alloc_hook(__ALLOC_HOOK pfnNewHook);

CLASS_DECL_ACME bool __enable_memory_leak_override(bool bEnable);
CLASS_DECL_ACME bool __enable_memory_tracking(bool bTrack);

/////////////////////////////////////////////////////////////////////////////
// Enumerate all objects allocated in the diagnostic memory heap

//struct CLASS_DECL_ACME ___ENUM_CONTEXT
//{
//   void (*m_pfn)(matter*,void *);
//   void * m_pContext;
//};

//CLASS_DECL_ACME void __do_for_all_objects_proxy(void * pObject, void * pContext);
//CLASS_DECL_ACME void __do_for_all_objects(void (c_cdecl *pfn)(matter*, void *), void * pContext);

/////////////////////////////////////////////////////////////////////////////
// Automatic debug memory diagnostics

#endif // ___NO_DEBUG_CRT
#endif // XDEBUG

/////////////////////////////////////////////////////////////////////////////
// Non-diagnostic memory routines

CLASS_DECL_ACME int c_cdecl __allocate_handler(size_t /* nSize */);



#endif // AAA_WANT_TO_REMOVE


