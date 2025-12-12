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

   binding::binding() {}


   binding::~binding() {}


   binding_set::binding_set() {}


   binding_set::~binding_set() {}


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


   ::gpu::binding *binding_set::binding(int iSlot)
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


   void binding_set::defer_update_binding_set(::gpu::command_buffer *pgpucommandbuffer) {}


   binding_set_array::binding_set_array() {}


   binding_set_array::~binding_set_array() {}


   bool binding_set_array::has_global_ubo() const
   {

      for (auto &pbindingset: *this)
      {

         if (pbindingset->has_global_ubo())
         {

            return true;
         }
      }

      return false;
   }


   ::gpu::binding_slot *binding_slot_set::binding_slot(int iSlot)
   {

      auto &bindingslot = this->ø(iSlot);

      bindingslot.m_iSlot = iSlot;

      return &bindingslot;
   }


   
   void binding_slot_set::update_binding_slots(int iSet)
   {

      if (::is_null(m_pbindingset))
      {

         this->erase_all();

         return;

      }

      this->set_size(this->m_pbindingset->size());

      int iSlot = -1;

      for (auto &pbinding: *this->m_pbindingset)
      {

         iSlot++;

         auto &bindingslot = this->element_at(iSet);

         bindingslot.m_iSet = iSet;

         bindingslot.m_iSlot = iSlot;

         bindingslot.m_pbinding = pbinding;

      }

   }



   binding_slot_set_array::binding_slot_set_array() {}

   binding_slot_set_array::~binding_slot_set_array() {}

   bool binding_slot_set_array::has_global_ubo() const
   {

      if (!m_pbindingseta)
      {

         return false;
      }

      return m_pbindingseta->has_global_ubo();
   }


   void binding_slot_set_array::update_binding_slots()
   {

      if (::is_null(m_pbindingseta))
      {

         this->erase_all();

         return;
      }

      this->set_size(this->m_pbindingseta->size());

      int iSet = -1;

      for (auto &pbindingset: *this->m_pbindingseta)
      {

         iSet++;

         auto &pbindingslotset = this->element_at(iSet);

         ødefer_construct(pbindingslotset);

         pbindingslotset->m_iSet = iSet;

         pbindingslotset->m_pbindingset = pbindingset;

         pbindingslotset->update_binding_slots(iSet);

      }

   }




} // namespace gpu



