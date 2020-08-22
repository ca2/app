#include "framework.h"
#include <memory.h>

char * const * alloc_c_string_array(string_array & stra)
{
   
   auto iCount = stra.get_count();
   
   char ** p = (char**) malloc(iCount * sizeof(char**));
   
   for(int i = 0; i < iCount; i++)
   {
      
      p[i] = strdup(stra[i]);
      
   }
   
   return p;
   
}


void free_c_string_array(char * const * ppszList, int iCount)
{
   
   if(::is_null(ppszList))
   {
      
      return;
      
   }
   
   for(int i = 0; i < iCount; i++)
   {
      
      if(::is_set(ppszList[i]))
      {
         
         ::free((void*)ppszList[i]);
         
      }
      
   }
   
   
   ::free((void*)ppszList);
   
   
   
}
