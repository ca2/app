//
//  aaa_memory_new.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 26/07/20.
//
#include "framework.h"
//#include "memory_allocate.h"
//
//#if !defined(UNIVERSAL_WINDOWS) && !defined(__ANDROID__)
//
//
//#if !defined(NO_ACME_MEMORY_MANAGEMENT)
//
//
//void MEMORY_DECL operator delete(void * p, size_t n) del_throw_spec
//{
//
//   ::operator delete(p);
//
//}
//
//
//#endif
//
//
//void* MEMORY_DECL operator new(size_t nSize)
//{
//
////   return ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(nSize);
//   return memory_allocate(nSize);
//
//}
//
//
//
//void* MEMORY_DECL operator new(size_t nSize, const std::nothrow_t&) noexcept
//{
//
//   return memory_allocate(nSize);
//
//}
//
//
//void MEMORY_DECL operator delete(void* p) del_throw_spec
//{
//
//   memory_free(p);
//
//}
//
//
//#ifdef WINDOWS
//
//void* MEMORY_DECL operator new[](size_t nSize)
//{
//
//   return ::operator new(nSize);
//
//}
//
//#else
//
//void* MEMORY_DECL operator new[](size_t nSize) new_throw_spec
//{
//
//   return ::operator new(nSize);
//
//}
//
//#endif
//
//void* MEMORY_DECL operator new[](size_t nSize, const std::nothrow_t&) noexcept
//{
//
//   return ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(nSize);
//
//}
//
//
//void MEMORY_DECL operator delete[](void* p) del_throw_spec
//{
//
//   ::operator delete(p);
//
//}
//
//
////#if !defined(_UNIVERSAL_WINDOWS)
////
////
//#if defined(UNIVERSAL_WINDOWS) //|| defined(__ANDROID__)
//
//
//void* MEMORY_DECL operator new(size_t nSize, void* p) inplace_new_throw_spec
//{
//
//   __UNREFERENCED_PARAMETER(nSize);
//
//   return p;
//
//}
//
//
//void MEMORY_DECL operator delete(void* p, void* palloc) del_throw_spec
//{
//
//   __UNREFERENCED_PARAMETER(p);
//   __UNREFERENCED_PARAMETER(palloc);
//
//}
//
//
//#endif
////
////
////#endif // _UNIVERSAL_WINDOWS
//
////
////
////void* MEMORY_DECL operator new (size_t size, const c_class&)
////{
////
////   return ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(size);
////
////}
////
////
////void* MEMORY_DECL operator new[](size_t size, const c_class&)
////{
////
////   return ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(size);
////
////}
////
////#ifdef CPP17
////void* MEMORY_DECL operator new(size_t size, std::align_val_t alignment);
////void operator delete(void* ptr, std::align_val_t) noexcept;
////#endif
////
////
////#define C_NEW __allocate<  >(c_class::s_cclass)
//
//
//#if !defined(NO_ACME_MEMORY_MANAGEMENT)
//
//
//void* MEMORY_DECL operator new(size_t nSize, const_char_pointer pszFileName, int nLine) new_throw_spec
//{
//
//   return ::operator new(nSize, _NORMAL_BLOCK, pszFileName, nLine);
//
//}
//
//
//void* MEMORY_DECL operator new[](size_t nSize, const_char_pointer pszFileName, int nLine) new_throw_spec
//{
//
//   return ::operator new[](nSize, _NORMAL_BLOCK, pszFileName, nLine);
//
//}
//
//
//void MEMORY_DECL operator delete(void* pData, const_char_pointer /* pszFileName */, int /* nLine */) del_throw_spec
//{
//
//   ::operator delete(pData, _NORMAL_BLOCK, nullptr, -1);
//
//}
//
//
//void MEMORY_DECL operator delete[](void* pData, const_char_pointer /* pszFileName */, int /* nLine */) del_throw_spec
//{
//
//   ::operator delete(pData, _NORMAL_BLOCK, nullptr, -1);
//
//}
//
//
//void* MEMORY_DECL operator new(size_t nSize, int nType, const_char_pointer pszFileName, int nLine)
//{
//
//#if MEMDLEAK
//
//   return ace_memory_alloc(nSize);
//
//#else
//
//   return memory_allocate_debug(nSize, nType, pszFileName, nLine);
//
//#endif
//
//}
//
//
//void MEMORY_DECL operator delete(void* p, int nType, const_char_pointer /* pszFileName */, int /* nLine */)
//{
//
//   memory_free_debug(p, nType);
//
//}
//
//
//void* MEMORY_DECL operator new[](size_t nSize, int nType, const_char_pointer pszFileName, int nLine)
//{
//
//   return ::operator new(nSize, nType, pszFileName, nLine);
//
//}
//
//
//void MEMORY_DECL operator delete[](void* p, int nType, const_char_pointer pszFileName, int nLine)
//{
//
//   ::operator delete(p, nType, pszFileName, nLine);
//
//}
//
//
//#endif
//
//
//#endif // !defined(UNIVERSAL_WINDOWS)
//
////#endif // __ACME_ASSET_NEW_CPP__
//
//
//
