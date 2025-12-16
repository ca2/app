// From bred/gpu/shader.cpp by camilo on 2025-12-11 00:25 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "binding.h"
#include "acme/exception/interface_only.h"
#include "bred/gpu/empty_texture_source.h"
#include "bred/gpu/input_layout.h"
#include "bred/gpu/pixmap.h"
#include "bred/gpu/texture.h"
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


   ::collection::count binding_set::uniform_buffer_count()
   {

      ::collection::count iUniformBuffer = 0;

      for (::collection::index i = 0; i < this->size(); i++)
      {

         if (::is_null(this->element_at(i)))
         {

            continue;

         }

         if (this->element_at(i)->is_uniform_buffer())
         {

            iUniformBuffer++;

         }

      }

      return iUniformBuffer;

   }
   
   
   ::collection::count binding_set::image_sampler_count()
   {

      ::collection::count iImageSampler = 0;

      for (::collection::index i = 0; i < this->size(); i++)
      {

         if (::is_null(this->element_at(i)))
         {

            continue;

         }

         if (this->element_at(i)->is_image_sampler())
         {

            iImageSampler++;

         }

      }

      return iImageSampler;

   }


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

         auto &bindingslot = this->element_at(iSlot);

         bindingslot.m_iSet = iSet;

         bindingslot.m_iSlot = iSlot;

         bindingslot.m_pbinding = pbinding;

      }

   }


   void binding_slot_set::set_texture(::pointer<::gpu::texture> *ppgputexture,
                                      ::gpu::empty_texture_source *pemptytexturesource) 
   {
   
      for (::collection::index iSlot = 0; iSlot < m_pbindingset->size(); iSlot++)
      {

         auto pbindingslot = binding_slot(iSlot);

         auto &pgputextureSource = ppgputexture[iSlot];

         if (pgputextureSource)
         {

            if (!pgputextureSource->is_ok())
            {

               if (!pgputextureSource->is_ok())
               {

                  throw ::exception(error_wrong_state);

               }

            }

            pbindingslot->m_ptexture = pgputextureSource;

         }
         else
         {

            pbindingslot->m_ptexture = pemptytexturesource->empty_texture();

         }

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



