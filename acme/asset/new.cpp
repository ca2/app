#undef new



void* MEMORY_DECL operator new(size_t nSize)
{

   return memory_allocate(nSize);

}



void* MEMORY_DECL operator new(size_t nSize, const std::nothrow_t&) noexcept
{

   return memory_allocate(nSize);

}


void MEMORY_DECL operator delete(void* p) del_throw_spec
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

void* MEMORY_DECL operator new[](size_t nSize, const std::nothrow_t&) noexcept
{

   return memory_allocate(nSize);

}


void MEMORY_DECL operator delete[](void* p) del_throw_spec
{

   ::operator delete(p);

}



#undef new


//#if !defined(_UNIVERSAL_WINDOWS)
//
//
#if defined(_UWP) //|| defined(ANDROID)


void* MEMORY_DECL operator new(size_t nSize, void* p) inplace_new_throw_spec
{

   __UNREFERENCED_PARAMETER(nSize);

   return p;

}


void MEMORY_DECL operator delete(void* p, void* palloc) del_throw_spec
{

   __UNREFERENCED_PARAMETER(p);
   __UNREFERENCED_PARAMETER(palloc);

}


#endif
//
//
//#endif // _UNIVERSAL_WINDOWS



void* MEMORY_DECL operator new (size_t size, const c_class&)
{

   return memory_allocate(size);

}


void* MEMORY_DECL operator new[](size_t size, const c_class&)
{

   return memory_allocate(size);

}

#ifdef CPP17
void* MEMORY_DECL operator new(size_t size, std::align_val_t alignment);
void operator delete(void* ptr, std::align_val_t) noexcept;
#endif


#define C_NEW new(c_class::s_cclass)


#if !defined(NO_ACME_MEMORY_MANAGEMENT)


void* MEMORY_DECL operator new(size_t nSize, const char* pszFileName, i32 nLine) new_throw_spec
{

   return ::operator new(nSize, _NORMAL_BLOCK, pszFileName, nLine);

}


void* MEMORY_DECL operator new[](size_t nSize, const char* pszFileName, i32 nLine) new_throw_spec
{

   return ::operator new[](nSize, _NORMAL_BLOCK, pszFileName, nLine);

}


void MEMORY_DECL operator delete(void* pData, const char* /* pszFileName */, i32 /* nLine */) del_throw_spec
{

   ::operator delete(pData, _NORMAL_BLOCK, nullptr, -1);

}


void MEMORY_DECL operator delete[](void* pData, const char* /* pszFileName */, i32 /* nLine */) del_throw_spec
{

   ::operator delete(pData, _NORMAL_BLOCK, nullptr, -1);

}


void* MEMORY_DECL operator new(size_t nSize, i32 nType, const char* pszFileName, i32 nLine)
{

#if MEMDLEAK

   return ace_memory_alloc(nSize);

#else

   return memory_allocate_debug(nSize, nType, pszFileName, nLine);

#endif

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


