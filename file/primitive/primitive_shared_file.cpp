#include "framework.h"


#if !defined(UNIVERSAL_WINDOWS)


namespace prototype
{


   shared_file::shared_file(::particle * pparticle, unsigned int nAllocFlags, unsigned int nGrowBytes) :
      ::object(pparticle)
   {

      __UNREFERENCED_PARAMETER(nGrowBytes);

      __UNREFERENCED_PARAMETER(nAllocFlags);

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


} // namespace prototype


#endif

