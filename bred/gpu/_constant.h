#pragma once


namespace gpu
{


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

   };


   enum enum_topology
   {

      e_topology_none,
      e_topology_triangle_list,
      e_topology_triangle_strip,
      e_topology_line_list,

   };


} // namespace gpu



