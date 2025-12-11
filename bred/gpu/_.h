// Changed by camilo on 2021-12-10 19:36 PM <3ThomasBorregaardSoerensen!!
#pragma once


#include "_constant.h"



#include "_constant.h"


namespace gpu
{

   //struct start_context_t;

   class cpu_buffer;
   class context;
   class shader;
   class frame_storage;
   class frame_ephemeral;
   //class program;

   class binding;
   class binding_set;
   class binding_set_array;


   struct binding_pointer
   {

      int m_iSet = -1;
      int m_iSlot = -1;
      ::pointer<binding> m_pbinding;

            binding *operator->() 
            { return m_pbinding.m_p; 
            }

   };


   struct binding_set_pointer
   {

      int m_iSet = -1;
      ::pointer<binding_set> m_pbindingset;

      binding_set * operator->()
      {

         return m_pbindingset.m_p;

      }

      ::gpu::binding_pointer binding(int iSlot);


   };




   template<typename VERTEX>
   class model_data;

   CLASS_DECL_BRED int get_type_size(::gpu::enum_type e);

   CLASS_DECL_BRED int get_type_unit_count(::gpu::enum_type e);

   CLASS_DECL_BRED ::gpu::enum_type get_type_unit_type(::gpu::enum_type e);


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

   struct renderable_t;

//   class renderable;

   class device;

   class compositor;


   class draw2d;

   class graphics;

   class renderer;
   class render;

   class frame;

   //class property_descriptor;
   //class property_data;
   class property;
   class properties;

   class queue;

   class swap_chain;

   class render_target;

   class render_state;

   class layer;

   class texture;



   class command_buffer;

   class input_layout;

   class context_object;

   class memory_buffer;

   class model_buffer;

   class pixmap;

} // gpu


namespace draw2d
{


   enum enum_model : int;


} // namespace draw2d


#define __expand_float_pre_rgba(color) (color.f32_opacity()*color.f32_red()),(color.f32_opacity()* color.f32_green()), (color.f32_opacity()*color.f32_blue()), color.f32_opacity()


#include "_types.h"


