#include "framework.h"

#if OBJECT_TYPE_COUNTER

int g_iObjTypCtrInit = 0;
huge_integer g_iObjTypCtr = 0;

critical_section g_csObjTypCtr;

map < const char*, const char*, huge_integer, huge_integer > * g_pmapObjTypCtr = nullptr;

void object_type_counter_increment(::particle * pparticle)
{

   if (!g_iObjTypCtrInit)
   {

      return;

   }

   critical_section_lock synchronouslock(&g_csObjTypCtr);

   const ::scoped_string & scopedstr = typeid(*pparticle).name();

   auto i = atomic_increment(&g_pmapObjTypCtr->operator[](psz));

   if (i >= 1024)
   {

      if (i % 128 == 0)
      {

         informationf("OMG too much of this: " + as_string(psz) + " (" + as_string(i) + ")\n");

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
   const ::scoped_string & scopedstr = typeid(*pparticle).name();

   auto i = atomic_decrement(&g_pmapObjTypCtr->operator[](psz));

   atomic_decrement(&g_iObjTypCtr);

}


#endif
