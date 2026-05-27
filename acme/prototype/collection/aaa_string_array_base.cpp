#include "framework.h"
#include <memory.h>

CLASS_DECL_ACME char_pointer const * alloc_c_string_array(const string_array_base & stra)
{
   
   auto iCount = stra.get_count();
   
   char_pointer * p = (char_pointer *) malloc(iCount * sizeof(char_pointer *));
   
   for(::i32 i = 0; i < iCount; i++)
   {
      
      p[i] = strdup(stra[i]);
      
   }
   
   return p;
   
}


CLASS_DECL_ACME void free_c_string_array(char_pointer const * ppszList, ::i32 iCount)
{
   
   if(::is_null(ppszList))
   {
      
      return;
      
   }
   
   for(::i32 i = 0; i < iCount; i++)
   {
      
      if(::is_set(ppszList[i]))
      {
         
         ::free((void*)ppszList[i]);
         
      }
      
   }
   
   
   ::free((void*)ppszList);
   
   
   
}
