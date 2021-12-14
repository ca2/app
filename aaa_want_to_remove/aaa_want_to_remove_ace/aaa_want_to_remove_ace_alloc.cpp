#include "ace.h"





PFN_MEMORY_ALLOC g_pfnAceAlloc = nullptr;
PFN_MEMORY_REALLOC g_pfnAceRealloc = nullptr;
PFN_MEMORY_FREE g_pfnAceFree = nullptr;
PFN_MEMORY_SIZE g_pfnAceSize = nullptr;


#ifdef APPLEOS


#define ACE_ALIGN_BYTE_COUNT (sizeof(memsize) * 2)


#else


#define ACE_ALIGN_BYTE_COUNT 16


#endif


int g_ace_set = 0;


#define INITIAL_ACE 0xff
#define ACE_SET 0xf7


CLASS_DECL_ACE void * ace_memory_alloc(memsize s)
{

#if OSBIT == 32

   if (s >= 0x100000000ll)
   {

      return nullptr;

   }

#endif

   if(g_ace_set)
   {

      return g_pfnAceAlloc(s);

   }
   else
   {

      auto sizeProvision = heap_memory_aligned_provision_get_size(s, ACE_ALIGN_BYTE_COUNT);

      auto pdata = malloc((size_t)sizeProvision);

      pdata = heap_memory_aligned(pdata, s, INITIAL_ACE, ACE_ALIGN_BYTE_COUNT);

      return pdata;

   }

}


CLASS_DECL_ACE void * ace_memory_realloc(void * pParam, memsize s)
{


#if OSBIT == 32

   if (s >= 0x100000000ll)
   {

      return nullptr;

   }

#endif

   if(heap_memory_get_block_use(pParam) == INITIAL_ACE)
   {

      auto pdata = realloc(heap_memory_base_get(pParam), heap_memory_aligned_provision_get_size(s, ACE_ALIGN_BYTE_COUNT));

      pdata = heap_memory_aligned(pdata, s, INITIAL_ACE, ACE_ALIGN_BYTE_COUNT);

      return pdata;

   }
   else
   {

      return g_pfnAceRealloc(pParam, s);

   }

}


CLASS_DECL_ACE void ace_memory_free(void * pParam)
{

   u8 * pdata = (u8 *) pParam;

   if(((iptr) pdata) < 1024 * 16)
   {

      return;

   }

   if (heap_memory_get_block_use(pParam) == INITIAL_ACE)
   {

      free(heap_memory_base_get(pParam));

   }
   else
   {

      return g_pfnAceFree(pParam);

   }

}


CLASS_DECL_ACE memsize ace_memory_size(void * pParam)
{

   return heap_memory_get_size(pParam);

}


CLASS_DECL_ACE void ace_set_alloc(PFN_MEMORY_ALLOC palloc, PFN_MEMORY_REALLOC prealloc, PFN_MEMORY_FREE pfree, PFN_MEMORY_SIZE psize)
{

   g_pfnAceAlloc = palloc;

   g_pfnAceRealloc = prealloc;

   g_pfnAceFree = pfree;

   g_pfnAceSize = psize;

   g_ace_set = 1;

}


static char * g_pszCacheDir;


CLASS_DECL_EXPORT void nodeos_set_cache_dir(const ::string & pszDir)
{

   if (g_pszCacheDir != nullptr)
   {

      free(g_pszCacheDir);

   }

   g_pszCacheDir = _strdup(pszDir);

}


CLASS_DECL_EXPORT const char * android_get_cache_dir()
{

   return g_pszCacheDir;

}


static char * g_pszHome;


CLASS_DECL_EXPORT void nodeos_set_home(const ::string & pszDir)
{

   if (g_pszHome != nullptr)
   {

      free(g_pszHome);

   }

   g_pszHome = _strdup(pszDir);

}


CLASS_DECL_EXPORT const char * nodeos_get_home()
{

   return g_pszHome;

}


static char * g_pszTemp = nullptr;


CLASS_DECL_EXPORT void nodeos_set_temp(const ::string & pszDir)
{

   if (g_pszTemp != nullptr)
   {

      free(g_pszTemp);

   }

   g_pszTemp = _strdup(pszDir);

}


CLASS_DECL_EXPORT const char * nodeos_get_temp()
{

   return g_pszTemp;

}






