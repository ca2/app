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


} // namespace gpu


