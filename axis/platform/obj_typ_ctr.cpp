#include "framework.h"

#if OBJ_TYP_CTR

int g_iObjTypCtrInit = 0;
i64 g_iObjTypCtr = 0;

critical_section g_csObjTypCtr;

map < const char*, const char*, ::i64, ::i64 > * g_pmapObjTypCtr = nullptr;

void obj_type_ctr_inc(::generic_object * pobject)
{

   if (!g_iObjTypCtrInit)
   {

      return;

   }

   cslock sl(&g_csObjTypCtr);

   const char* psz = typeid(*pobject).name();

   auto i = atomic_increment(&g_pmapObjTypCtr->operator[](psz));

   if (i >= 1024)
   {

      if (i % 128 == 0)
      {

         output_debug_string("OMG too much of this: " + __str(psz) + " (" + __str(i) + ")\n");

      }


   }

   atomic_increment(&g_iObjTypCtr);

}
void obj_type_ctr_dec(::generic_object* pobject)
{
   if (!g_iObjTypCtrInit)
   {

      return;

   }

   cslock sl(&g_csObjTypCtr);
   const char* psz = typeid(*pobject).name();

   auto i = atomic_decrement(&g_pmapObjTypCtr->operator[](psz));

   atomic_decrement(&g_iObjTypCtr);

}


#endif