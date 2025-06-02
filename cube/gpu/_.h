// Changed by camilo on 2021-12-10 19:36 PM <3ThomasBorregaardSoerensen!!
#pragma once


namespace gpu
{

   struct start_context_t;

   class cpu_buffer;
   class context;
   class shader;
   //class program;

   enum enum_type
   {

      e_type_none = 0,
      e_type_int = 1,
      e_type_float = 2,
      e_type_seq2 = 3,
      e_type_seq3 = 4,
      e_type_seq4 = 5,
      e_type_mat2 = 6,
      e_type_mat3 = 7,
      e_type_mat4 = 8,

   };





   CLASS_DECL_CUBE int get_type_size(enum_type e);
   
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

   class renderer;
   class render;

   class frame;

   class property;
   class properties;

   class device;


} // gpu


#include "_constant.h"



