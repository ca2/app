// From bred/gpu/shader.cpp by camilo on 2025-12-11 00:25 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "binding.h"
#include "acme/exception/interface_only.h"
#include "bred/gpu/input_layout.h"
#include "bred/gpu/pixmap.h"
#include "context.h"
#include "renderer.h"
#include "shader.h"
// #include "_.h"
// #include "_gpu.h"


namespace gpu
{



   bool binding_set::has_global_ubo() const
   {

      for (auto &pbinding: *this)
      {

         if (pbinding->is_global_ubo())
         {

            return true;
         }
      }

      return false;
   }


   ::gpu::binding * binding_set::binding(int iSlot)
   {

      auto &pbinding = this->ø(iSlot);

      if (!pbinding)
      {

         øconstruct(pbinding);

         pbinding->m_bSet = true;
         pbinding->m_iSlot = iSlot;

      }

      return pbinding;
   }


   bool binding_set_array::has_global_ubo() const
   {

      for (auto &bindingsetinstance: *this)
      {

         if (bindingsetinstance.m_pbindingset->has_global_ubo())
         {

            return true;
         }
      }

      return false;
   }

} // namespace gpu
