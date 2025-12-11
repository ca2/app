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


   class binding : virtual public ::particle
   {
   public:


      bool m_bSet = false;
      int m_iSlot = -1;
      bool m_bVertexShader = false;
      bool m_bFragmentShader = false;
      // bool                       m_bImageSampler = false;
      ::string m_strUniform;
      enum_binding m_ebinding = e_binding_none;
      ::pointer<::gpu::texture> m_ptexture;

      bool is_image_sampler() const
      {

         return m_ebinding == e_binding_sampler2d || m_ebinding == e_binding_cube_sampler;
      }

      bool is_global_ubo() const { return m_ebinding == e_binding_global_ubo1; }
   };

   class binding_set : virtual public ::pointer_array<binding>
   {
   public:


      bool has_global_ubo() const;


      ::gpu::binding * binding(int iSlot);
   };


   struct binding_set_instance
   {

      ::pointer<binding_set> m_pbindingset;
      int m_iSet = -1;

   };


   class CLASS_DECL_BRED binding_set_array : 
      virtual public ::array_particle<
         ::array_base<binding_set_instance >
      >
   {
   public:
      bool has_global_ubo() const;
   };


} // namespace gpu
 


