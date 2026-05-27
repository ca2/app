// Created by camilo on 2025-06-30 22:38 <3ThomasBorregaardSørensen!!
#pragma once


#include "bred/gpu/command_buffer.h"


namespace gpu_opengl
{


   class CLASS_DECL_GPU_OPENGL command_buffer :
      virtual public ::gpu::command_buffer
   {
   public:


      command_buffer();
      ~command_buffer() override;


      void set_viewport(const ::i32_rectangle& rectangle) override;

      void set_scissor(const ::i32_rectangle& rectangle) override;


      void draw_int_a_count(::i32 a) override;


      void set_render_target() override;
      void draw_vertexes(::i32 iVertexCount) override;
      void draw_indexes(::i32 iIndexCount) override;


      void begin_render(::gpu::shader *pgpushader, ::gpu::texture *pgputextureTarget) override;
      void end_render() override;


   };


} // namespace gpu_opengl



