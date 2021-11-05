#include "_ace.h"

#include <new>

#ifdef _ACID_LIBRARY
#define CLASS_DECL_ACE
#elif defined(_APP_ACE_SHARED)
#define CLASS_DECL_ACE CLASS_DECL_EXPORT
#else
#define CLASS_DECL_ACE CLASS_DECL_IMPORT
#endif


extern "C"
{

   CLASS_DECL_ACE void * MEMORY_DECL ace_memory_alloc(memsize s);


   CLASS_DECL_ACE void MEMORY_DECL ace_memory_free(void * p);

}
