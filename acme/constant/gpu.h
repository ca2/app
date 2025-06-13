// Created by camilo on 2025-05-31 13:56 <3ThomasBorregaardSørensen!!
#pragma once


namespace gpu
{


   enum enum_output
   {

      e_output_none,
      e_output_cpu_buffer,
      e_output_swap_chain,
      e_output_gpu_buffer,
      e_output_color_and_alpha_accumulation_buffers,
      e_output_resolve_color_and_alpha_accumulation_buffers,
      e_output_gpu_buffer_to_swap_chain,

   };


   enum enum_scene
   {
      
      e_scene_none,
      e_scene_2d,
      e_scene_3d,

   };


} // namespace gpu



