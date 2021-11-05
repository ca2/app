

#if !defined(NO_ACME_MEMORY_MANAGEMENT)

#undef new

#if defined(LINUX)
#include <new>
#endif



void * MEMORY_DECL operator new(size_t nSize, void * p) inplace_new_throw_spec;

void MEMORY_DECL operator delete(void * p, void * palloc) del_throw_spec;

void * MEMORY_DECL operator new(size_t nSize) new_throw_spec;

void MEMORY_DECL operator delete(void * p) del_throw_spec;

void * MEMORY_DECL operator new[](size_t nSize) new_throw_spec;

void MEMORY_DECL operator delete[](void * p) del_throw_spec;

void * MEMORY_DECL operator new(size_t nSize, const char * pszFileName, i32 nLine) new_throw_spec;

void MEMORY_DECL operator delete(void * p, const char * pszFileName, i32 nLine) del_throw_spec;

void * MEMORY_DECL operator new[](size_t nSize, const char * pszFileName, i32 nLine) new_throw_spec;

void MEMORY_DECL operator delete[](void * p, const char * pszFileName, i32 nLine) del_throw_spec;

void * MEMORY_DECL operator new(size_t nSize, i32 nType, const char * pszFileName, i32 nLine);

void * MEMORY_DECL operator new[](size_t nSize, i32 nType, const char * pszFileName, i32 nLine);

void MEMORY_DECL operator delete(void * p, i32 nType, const char * pszFileName, i32 nLine);

void MEMORY_DECL operator delete[](void * p, i32 nType, const char * pszFileName, i32 nLine);


#endif


#define new ACME_NEW



