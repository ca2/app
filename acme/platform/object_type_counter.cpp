#include "framework.h"

#if OBJECT_TYPE_COUNTER

int g_iObjTypCtrInit = 0;
i64 g_iObjTypCtr = 0;

critical_section g_csObjTypCtr;

map < const char*, const char*, ::i64, ::i64 > * g_pmapObjTypCtr = nullptr;

void object_type_counter_increment(::particle * pparticle)
{

   if (!g_iObjTypCtrInit)
   {

      return;

   }

   critical_section_lock synchronouslock(&g_csObjTypCtr);

   const char* psz = typeid(*pparticle).name();

   auto i = atomic_increment(&g_pmapObjTypCtr->operator[](psz));

   if (i >= 1024)
   {

      if (i % 128 == 0)
      {

         output_debug_string("OMG too much of this: " + __string(psz) + " (" + __string(i) + ")\n");

      }


   }

   atomic_increment(&g_iObjTypCtr);

}
void object_type_counter_decrement(::particle * pparticle)
{
   if (!g_iObjTypCtrInit)
   {

      return;

   }

   critical_section_lock synchronouslock(&g_csObjTypCtr);
   const char* psz = typeid(*pparticle).name();

   auto i = atomic_decrement(&g_pmapObjTypCtr->operator[](psz));

   atomic_decrement(&g_iObjTypCtr);

}


#endif
