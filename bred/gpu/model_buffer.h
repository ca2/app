// From gpu_vulkan/model_buffer.h by
// camilo on 2025-07-01 12:34 <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/prototype/prototype/poolable.h"
#include "bred/graphics3d/types.h"
#include "bred/gpu/context.h"
#include "bred/gpu/context_object.h"
#include "bred/gpu/memory_buffer.h"



namespace gpu
{


   class CLASS_DECL_BRED model_buffer :
      virtual public context_object,
      virtual public poolable < model_buffer >
   {
   public:


      void* m_pMap;
      ::pointer < memory_buffer > m_pbufferVertex;
      ::pointer < memory_buffer > m_pbufferIndex;
      int m_iVertexCount;
      int m_iIndexCount;




      model_buffer();
      ~model_buffer();

      virtual void sequence2_uv_create_rectangle(::gpu::context* pcontext, bool bIndexed, bool bYSwap);

      template < typename VERTEX >
      void create_vertex_array(::gpu::context* pcontext, int iVertexCount)
      {

         initialize_gpu_context_object(pcontext);

         m_iVertexCount = iVertexCount;

         auto size = sizeof(VERTEX) * m_iVertexCount;

         pcontext->defer_construct_new(m_pbufferVertex, size);

      }

      void sequence2_color_create_rectangle(::gpu::context* pcontext);
      void sequence2_color_create_line(::gpu::context* pcontext);
      void sequence3_color_create_rectangle(::gpu::context* pcontext);
      void sequence3_color_create_line(::gpu::context* pcontext);

      void sequence3_color_set_rectangle(
         const ::double_point points1[4],
         const  ::color::color& color,
         const ::double_size& size);

      void sequence2_color_set_rectangle(
         const ::double_point points1[4],
         const ::color::color& color,
         const ::double_size& size);

      void sequence3_color_set_line(
         const ::double_point& pointA,
         const ::double_point& pointB,
         const  ::color::color& color,
         const ::double_size& size);

      void sequence2_color_set_line(
         const ::double_point& pointA,
         const ::double_point& pointB,
         const  ::color::color& color,
         const ::double_size& size);

      template < typename VERTEX >
      memory_map < memory_buffer, VERTEX > map()
      {

         return { m_pbufferVertex.m_p, (VERTEX*)nullptr };

      }

      //virtual void* _map(memsize start, memsize count);
      //virtual void unmap();

      virtual void bind(::gpu::command_buffer* pcommandbuffer);

      virtual void draw(::gpu::command_buffer* pcommandbuffer);


   };


} // namespace gpus



