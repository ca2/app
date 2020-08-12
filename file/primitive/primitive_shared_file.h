#pragma once


#if !defined(_UWP)


namespace primitive
{

   class CLASS_DECL_CA2_FILE shared_file :
      public ::memory_file
   {
   public:

#ifdef WINDOWS
      shared_file(::object * pobject, UINT nGrowBytes = 4096, UINT nAllocFlags = GMEM_MOVEABLE);
#else
    shared_file(::object * pobject, UINT nGrowBytes = 4096, UINT nAllocFlags = 0);
#endif

      virtual HGLOBAL detach_storage();
      virtual void SetHandle(HGLOBAL hGlobalMemory, bool bAllowGrow = TRUE);

   public:
      virtual ~shared_file();

   };

} // namespace primitive


#endif
