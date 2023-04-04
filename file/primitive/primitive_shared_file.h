#pragma once


#if !defined(UNIVERSAL_WINDOWS)


namespace primitive
{

   class CLASS_DECL_CA2_FILE shared_file :
      public ::memory_file
   {
   public:

#ifdef WINDOWS
      shared_file(::particle * pparticle, ::u32 nGrowBytes = 4096, ::u32 nAllocFlags = GMEM_MOVEABLE);
#else
    shared_file(::particle * pparticle, ::u32 nGrowBytes = 4096, ::u32 nAllocFlags = 0);
#endif

      virtual HGLOBAL detach_storage();
      virtual void SetHandle(HGLOBAL hGlobalMemory, bool bAllowGrow = true);

   public:
      virtual ~shared_file();

   };

} // namespace primitive


#endif
