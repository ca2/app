// Created by camilo on 2025-05-19 05:39 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "_.h"


namespace gpu
{


   CLASS_DECL_CUBE int get_type_size(enum_type e)
   {

      switch (e)
      {
      case e_type_int: return sizeof(int);
      case e_type_float: return sizeof(float);
      case e_type_seq4: return sizeof(float) * 4;
      case e_type_mat4: return sizeof(float) * 16;
      default:
         throw ::exception(error_wrong_state);

      }

   }


} // namespace gpu


