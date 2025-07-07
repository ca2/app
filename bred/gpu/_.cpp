// Created by camilo on 2025-05-19 05:39 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "_.h"
#include "device.h"


namespace gpu
{


   extern thread_local device* t_pgpudevice;


   CLASS_DECL_BRED int get_type_size(::gpu::enum_type e)
   {

      return t_pgpudevice->get_type_size(e);

   }


   CLASS_DECL_BRED int get_type_unit_count(::gpu::enum_type e)
   {

      switch (e)
      {
      case e_type_int:
         return 1;
      case e_type_float:
         return 1;
      case e_type_seq2:
         return 2;
      case e_type_seq3:
         return 3;
      case e_type_seq4:
         return 4;
      case e_type_mat2:
         return 4;
      case e_type_mat3:
         return 9;
      case e_type_mat4:
         return 16;
      default:
         throw ::exception(error_not_implemented);

      }

   }



} // namespace gpu


