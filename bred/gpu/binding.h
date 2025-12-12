// From bred/gpu/shader.h by camilo on 2025-12-11 00:16 <3ThomasBorregaardSørensen!!
#pragma once


#include "bred/gpu/properties.h"


namespace gpu
{


   enum enum_binding
   {
      e_binding_none,
      e_binding_global_ubo1,
      e_binding_uniform_buffer,
      e_binding_sampler2d,
      e_binding_cube_sampler,

   };




   class CLASS_DECL_BRED binding : virtual public ::particle
   {
   public:


      bool m_bSet = false;
      int m_iSlot = -1;
      bool m_bVertexShader = false;
      bool m_bFragmentShader = false;
      // bool                       m_bImageSampler = false;
      ::string m_strUniform;
      enum_binding m_ebinding = e_binding_none;

      binding();
      ~binding() override;

      bool is_image_sampler() const
      {

         return m_ebinding == e_binding_sampler2d || m_ebinding == e_binding_cube_sampler;
      }

      bool is_global_ubo() const { return m_ebinding == e_binding_global_ubo1; }
   };

   class CLASS_DECL_BRED binding_set : virtual public ::pointer_array<binding>
   {
   public:


      binding_set();
      ~binding_set() override;

      bool has_global_ubo() const;


      ::gpu::binding * binding(int iSlot);

      virtual void defer_update_binding_set(::gpu::command_buffer *pgpucommandbuffer);


   };


   class CLASS_DECL_BRED binding_set_array : 
      virtual public ::pointer_array<binding_set>
   {
   public:


      binding_set_array();
      ~binding_set_array() override;

      bool has_global_ubo() const;
   };


   class CLASS_DECL_BRED binding_slot
   {
   public:


      int m_iSet = -1;
      int m_iSlot = -1;
      ::pointer<binding> m_pbinding;
      ::pointer<::gpu::texture> m_ptexture;
      ::pointer<::gpu::block> m_pblock;

      // binding *operator->()
      //{ return m_pbinding.m_p;
      // }
      //virtual void update_binding_slot();

   };


   class CLASS_DECL_BRED binding_slot_set :
      virtual public ::array_particle < ::array_base<binding_slot> >
   {
   public:

      int m_iSet = -1;
      ::pointer<binding_set> m_pbindingset;

      // binding_set * operator->()
      //{

      // return m_pbindingset.m_p;

      //}

      ::gpu::binding_slot *binding_slot(int iSlot);

      //::gpu::binding_slot binding_slot(int iSlot);

      virtual void update_binding_slots(int iSet);


   };


   class CLASS_DECL_BRED binding_slot_set_array : 
      virtual public ::pointer_array < binding_slot_set >
   {
   public:

      ::pointer<binding_set_array> m_pbindingseta;

      //::pointer_array<binding_set>        m_bindingseta;
      //::array_base<binding_set_pointer>   m_bindingseta;



      binding_slot_set_array();
      ~binding_slot_set_array() override;

      virtual bool has_global_ubo() const;

      virtual void update_binding_slots();

   };


   //inline ::gpu::binding_slot * binding_set_pointer::binding(int iSlot)
   //{

   //   return {m_iSet, iSlot, m_pbindingset->binding(iSlot)};

   //}


} // namespace gpu
 


