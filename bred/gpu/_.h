// Changed by camilo on 2021-12-10 19:36 PM <3ThomasBorregaardSoerensen!!
#pragma once


namespace gpu
{

   //struct start_context_t;

   class cpu_buffer;
   class context;
   class shader;
   class frame_storage;
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
      e_type_properties_array = 0,

   };





   CLASS_DECL_BRED int get_type_size(::gpu::enum_type e);

   CLASS_DECL_BRED int get_type_unit_count(::gpu::enum_type e);


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



   class draw2d;

   class graphics;

   class renderer;
   class render;

   class frame;

   class property;
   class properties;

   class device;

   class compositor;

   class swap_chain;

   class render_target;

   class render_state;

   class layer;

   class texture;



   enum enum_state
   {

      e_state_initial,
      e_state_new_frame,
      e_state_began_frame,
      e_state_began_render,
      e_state_ended_render,
      e_state_ended_frame,
      e_state_no_frame = 256,
      e_state_single_frame = 1024,

   };


   enum enum_happening
   {

      e_happening_reset_frame_counter,
      //e_happening_new_frame,
      e_happening_begin_frame,
      e_happening_begin_render,
      e_happening_end_render,
      e_happening_end_frame,

   };


   enum enum_render_mode
   {

      e_render_mode_none,
      e_render_mode_multiple_frame_states,
      e_render_mode_single_frame_state,

   };

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


#include "_constant.h"




