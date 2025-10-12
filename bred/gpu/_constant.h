#pragma once


namespace gpu
{


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



   enum enum_shader_source
   {

      e_shader_source_neort,
      e_shader_source_shadertoy,

   };


   enum enum_cull_mode
   {

      e_cull_mode_none,
      e_cull_mode_front,
      e_cull_mode_back,

   };


   enum enum_command_buffer
   {

      e_command_buffer_none,
      e_command_buffer_graphics,
      e_command_buffer_copy,
      e_command_buffer_present,
      e_command_buffer_transfer,

   };


   enum enum_topology
   {

      e_topology_none,
      e_topology_triangle_list,
      e_topology_triangle_strip,
      e_topology_line_list,

   };




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


   enum enum_renderable_type
   {

      e_renderable_type_none,
      e_renderable_type_wavefront_obj,
      e_renderable_type_gltf

   };


   enum enum_renderable_usage
   {

      e_renderable_usage_default,
      e_renderable_usage_skybox

   };


   enum enum_gltf_texture
   {

      e_gltf_texture_albedo, 
      e_gltf_texture_metallic_roughness,
      e_gltf_texture_normal,
      e_gltf_texture_ambient_occlusion,
      e_gltf_texture_emissive,

   };



} // namespace gpu



