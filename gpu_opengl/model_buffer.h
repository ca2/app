// From gpu_vulkan/model_buffer.h by
// camilo on 2025-07-01 20:34 <3ThomasBorregaardSørensen!!
// Created by camilo on 2025-06-11 01:06 <3ThomasBorregaardSørensen!!
#pragma once


#include "bred/gpu/model_buffer.h"
#include "acme/prototype/prototype/poolable.h"
#include "bred/graphics3d/types.h"
#include "gpu_opengl/context.h"
//#include "gpu_opengl/context_object.h"
#include "gpu_opengl/memory_buffer.h"



namespace gpu_opengl
{

 
   class CLASS_DECL_GPU_OPENGL model_buffer :
      virtual public ::gpu::model_buffer
   {
   public:
      
      
      GLuint m_gluVao;


      model_buffer();
      ~model_buffer();


      void on_initialize_gpu_context_object() override;

      //void sequence2_uv_create_rectangle(::gpu::context* pcontext, bool bIndexed, bool bYSwap) override;

      //template < typename VERTEX >
      //void create_vertex_array(::gpu_vulkan::context* pcontext, int iVertexCount)
      //{

      //   initialize_gpu_context_object(pcontext);

      //   m_iVertexCount = iVertexCount;

      //   auto size = sizeof(VERTEX) * m_iVertexCount;

      //   pcontext->defer_construct_new(m_pbufferVertex, size);

      //}

    /*  void sequence2_color_create_rectangle(::gpu_vulkan::context* pcontext);
      void sequence2_color_create_line(::gpu_vulkan::context* pcontext);
      void sequence3_color_create_rectangle(::gpu_vulkan::context* pcontext);
      void sequence3_color_create_line(::gpu_vulkan::context* pcontext);*/

      //void sequence3_color_set_rectangle(
      //   const ::double_point points1[4],
      //   const  ::color::color& color,
      //   const ::double_size& size);

      //void sequence2_color_set_rectangle(
      //   const ::double_point points1[4],
      //   const ::color::color& color,
      //   const ::double_size& size);

      //void sequence3_color_set_line(
      //   const ::double_point& pointA,
      //   const ::double_point& pointB,
      //   const  ::color::color& color,
      //   const ::double_size& size);

      //void sequence2_color_set_line(
      //   const ::double_point& pointA,
      //   const ::double_point& pointB,
      //   const  ::color::color& color,
      //   const ::double_size& size);

 /*     template < typename VERTEX > 
      memory_map < memory_buffer, VERTEX > map()
      {

         return { m_pbufferVertex.m_p, (VERTEX*)nullptr };

      }*/

      //virtual void * _map(memsize start, memsize count);
      //virtual void unmap();

      void bind(::gpu::command_buffer* pcommandbuffer) override;

      void draw(::gpu::command_buffer* pcommandbuffer) override;

      void draw_lines(::gpu::command_buffer* pcommandbuffer) override;

      void unbind(::gpu::command_buffer* pcommandbuffer) override;


      void defer_set_input_layout(::gpu::input_layout* pinputlayout) override;


   };


} // namespace gpu_opengl



