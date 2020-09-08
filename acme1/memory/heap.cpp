#include "framework.h"

#include "plex_heap1.h"

#include "plex_heap_impl1.h"

#ifdef RASPBIAN

#define AXIS_MEMORY_MANAGEMENT TRUE

#else

#define AXIS_MEMORY_MANAGEMENT TRUE

#endif


#if !AXIS_MEMORY_MANAGEMENT


#include "heap_bare.cpp"


#else


#ifdef LINUX


#include <malloc.h>


#endif


#include "align_byte_count.h"


#include "acme/platform/static_start.h"


#ifdef MCHECK


#include "heap_mcheck.cpp"


#elif defined(_VLD)


#include "heap_vld.cpp"


#elif defined(__MCRTDBG)


#include "heap_mcrtdbg.cpp"


#elif MEMDLEAK


#include "heap_memdleak.cpp"


#else


#include "inline/heap_std.cpp"


#endif


#endif


//#if !defined(MCHECK) && !defined(_VLD) && !defined(__MCRTDBG)
//
//const int heap_memory::m_iPaddingAfter = 16;
//
//#endif





c_class c_class::s_cclass;


c_class::c_class()
{
}

c_class::c_class(const c_class &)
{
}

c_class::~c_class()
{
}


//namespace heap
//{
//
//
//   void heap_base::zero()
//   {
//
//      if(size() > 0 && m_p != nullptr)
//      {
//
//         ::zero(m_p, size());
//
//      }
//
//   }
//
//
//} // namespace heap



