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
      ::pointer < input_layout > m_pinputlayout;
      ::pointer < command_buffer >  m_pcommandbufferLoading;
      int m_iVertexCount;
      int m_iVertexByteSize;
      int m_iVertexTypeSize;
      int m_iIndexCount;
      int m_iIndexByteSize;
      int m_iIndexTypeSize;

      bool m_bDummy;
      




      model_buffer();
      ~model_buffer();

      
      virtual void sequence2_uv_create_rectangle(::gpu::context* pcontext, bool bIndexed, bool bYSwap);


      template < typename VERTEX >
      void create_vertices(int iVertexCount)
      {

         m_iVertexCount = iVertexCount;

         m_iVertexTypeSize = sizeof(VERTEX);

         auto size = m_iVertexTypeSize * m_iVertexCount;

         __defer_construct(m_pbufferVertex);

         m_pbufferVertex->initialize_memory_buffer_with_model_buffer(
            this,
            size, 
            memory_buffer::e_type_vertex_buffer);

         set_input_layout(m_pgpucontext->input_layout(::gpu_properties< VERTEX >()));

      }


      template < typename VERTEX >
      void static_initialize_vertices(const ::array<VERTEX> & vertexa)
      {

         static_initialize_vertex_buffer(
            vertexa.data(),
            sizeof(VERTEX),
            vertexa.size());

         set_input_layout(m_pgpucontext->input_layout(::gpu_properties< VERTEX >()));

      }

      virtual void static_initialize_vertex_buffer(const void* data, memsize iTypeSize, ::collection::count iVertexCount);
      virtual void static_initialize_index_buffer(const void* data, memsize iTypeSize, ::collection::count iIndexCount);

      virtual void static_initialize_vertices_block(const ::block& blockVertices);
      virtual void static_initialize_indices_block(const ::block& blockIndices);

      template < typename INDEX >
      void create_indices(::collection::count iIndexCount)
      {

         m_iIndexCount = (int) iIndexCount;

         m_iIndexTypeSize = (int) sizeof(INDEX);

         auto size = m_iIndexTypeSize * m_iIndexCount;

         __defer_construct(m_pbufferIndex);

         m_pbufferIndex->initialize_memory_buffer_with_model_buffer(
            this,
            size,
            memory_buffer::e_type_index_buffer);

      }

      
      template < typename INDEX >
      void static_initialize_indices(const ::array<INDEX>& indexa)
      {

         //m_iIndexCount = (int)indexa.count();

         //m_iIndexTypeSize = sizeof(INDEX);

         //auto size = indexa.get_size_in_bytes();

         //__defer_construct(m_pbufferIndex);

         //m_pbufferIndex->static_initialize_memory_buffer_with_model_buffer(
         //   this,
         //   indexa.data(),
         //   size,
         //   memory_buffer::e_type_index_buffer);

         static_initialize_index_buffer(
            indexa.data(),
            sizeof(INDEX),
            indexa.size());

      }


      template < typename VERTEX >
      void set_vertices(const ::array < VERTEX > & vertexa)
      {

         if (sizeof(VERTEX) != m_iVertexTypeSize)
         {

            throw ::exception(error_wrong_state);

         }

         m_pbufferVertex->on_set_memory_buffer(vertexa.data(), vertexa.get_size_in_bytes());

      }


      template < typename VERTEX >
      void _set_vertices(const ::array < VERTEX >& vertexa)
      {

         if (sizeof(VERTEX) != m_iVertexTypeSize)
         {

            throw ::exception(error_wrong_state);

         }

         m_pbufferVertex->_on_set_memory_buffer(vertexa.data(), vertexa.get_size_in_bytes());

      }


      template < typename INDEX >
      void set_index_array(const INDEX* p, ::collection::count iIndexCount)
      {

         if (sizeof(INDEX) != m_iIndexTypeSize)
         {

            throw ::exception(error_wrong_state);

         }

         m_pbufferIndex->assign(p, sizeof(INDEX) * iIndexCount);

      }


      template < typename VERTEX >
      void _set_vertex_array(const VERTEX* p, ::collection::count iVertexCount)
      {

         if (sizeof(VERTEX) != m_iVertexTypeSize)
         {

            throw ::exception(error_wrong_state);

         }

         m_pbufferVertex->_assign(p, sizeof(VERTEX) * iVertexCount);// data = map <VERTEX >();

      }


      template < typename INDEX >
      void _set_index_array(const INDEX* p, ::collection::count iIndexCount)
      {

         if (sizeof(INDEX) != m_iIndexTypeSize)
         {

            throw ::exception(error_wrong_state);

         }

         m_pbufferIndex->_assign(p, sizeof(INDEX) * iIndexCount);

      }


      virtual bool is_dummy() const;

      void sequence2_uv_create_fullscreen_quad(::gpu::context* pcontext);
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

      template < typename INDEX >
      memory_map < memory_buffer, INDEX > map_indices()
      {

         return { m_pbufferIndex.m_p, (INDEX*)nullptr };

      }

      //virtual void* _map(memsize start, memsize count);
      //virtual void unmap();

      virtual void bind(::gpu::command_buffer* pcommandbuffer);

      virtual void draw(::gpu::command_buffer* pcommandbuffer);

      virtual void draw_lines(::gpu::command_buffer* pcommandbuffer);

      virtual void unbind(::gpu::command_buffer* pcommandbuffer);

      virtual void set_input_layout(::gpu::input_layout* pinputlayout);

      virtual void apply_input_layout();


   };


} // namespace gpus



