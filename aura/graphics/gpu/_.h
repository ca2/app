// Changed by camilo on 2021-12-10 19:36 PM <3ThomasBorregaardSoerensen!!
#pragma once


namespace gpu
{


   class cpu_buffer;
   class context;
   class shader;
   class program;

   enum enum_type
   {

      e_type_none = 0,
      e_type_int = 1,
      e_type_float = 2,

   };

   //using uniform = int;
   struct payload
   {

      union
      {
         int m_iOffset;
         int m_iUniform;
      };
      enum_type m_etype;

   };
   using element = int;


} // gpu


#include "_constant.h"



