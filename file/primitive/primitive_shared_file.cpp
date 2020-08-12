#include "framework.h"


#if !defined(_UWP)


namespace primitive
{


   shared_file::shared_file(::object * pobject, UINT nAllocFlags, UINT nGrowBytes) :
      ::object(pobject)
   {

      UNREFERENCED_PARAMETER(nGrowBytes);

      UNREFERENCED_PARAMETER(nAllocFlags);

   }


   shared_file::~shared_file()
   {

   }


   void shared_file::SetHandle(HGLOBAL hGlobalMemory, bool bAllowGrow)
   {

      get_memory().cast < shared_memory > ()->SetHandle(hGlobalMemory, bAllowGrow);

   }


   HGLOBAL shared_file::detach_storage()
   {

      HGLOBAL hglobal = nullptr;

      get_memory().cast < shared_memory > ()->detach_shared_memory(hglobal);

      return hglobal;

   }


} // namespace primitive


#endif

