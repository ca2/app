// From gpu_vulkan/model_buffer.h by
// camilo on 2025-07-01 12:34 <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/prototype/prototype/poolable.h"
#include "bred/gpu/context.h"
#include "bred/gpu/context_object.h"
#include "bred/gpu/frame.h"
#include "bred/gpu/memory_buffer.h"
#include "bred/gpu/model_data.h"
#include "bred/graphics3d/renderable.h"
#include "bred/graphics3d/types.h"


namespace gpu
{


   class CLASS_DECL_BRED model_buffer :
      virtual public context_object,
      virtual public poolable < model_buffer >,
      virtual public ::graphics3d::renderable
   {
   protected:


      virtual void _static_initialize_vertex_buffer(const ::block & blockVertexData);
      virtual void _static_initialize_index_buffer(const ::block & blockIndexData);


   public:


      void* m_pMap;
      ::pointer<model_data_base> m_pmodeldatabase2;
      ::pointer < memory_buffer > m_pbufferVertex;
      ::pointer < memory_buffer > m_pbufferIndex;
      ::pointer < input_layout > m_pinputlayout;
      ::pointer < command_buffer >  m_pcommandbufferLoading;
      
      //bool m_bDummy;
      
      ::string m_strDebugString;



      model_buffer();
      ~model_buffer();

      template < typename VERTEX, typename INDEX = unsigned int >
      ::gpu::model_data_base & model_data()
      {

         if (!m_pmodeldatabase2
            || typeid(VERTEX) != m_pmodeldatabase2->vertex_type()
            || typeid(INDEX) != m_pmodeldatabase2->index_type())
         {

            m_pmodeldatabase2 = øallocate ::gpu::model_data<VERTEX, INDEX>();

         }
         return *m_pmodeldatabase2;


      }




      
      virtual void sequence2_uv_create_rectangle(::gpu::context* pcontext, bool bIndexed, bool bYSwap);


      template < typename VERTEX >
      void create_vertexes(int iVertexCount, bool bDynamic = false)
      {

         auto & modeldata = model_data<VERTEX>();

         modeldata.set_vertex_count(iVertexCount);

         //m_iVertexCount = iVertexCount;

         //m_iVertexTypeSize = sizeof(VERTEX);

         //auto size = m_iVertexTypeSize * m_iVertexCount;

         ødefer_construct(m_pbufferVertex);

         m_pbufferVertex->initialize_memory_buffer_with_model_buffer(
            this,
            modeldata.vertex_bytes(), 
            memory_buffer::e_type_vertex_buffer, bDynamic);

         set_input_layout(m_pgpucontext->input_layout(::gpu_properties< VERTEX >()));

      }


      //template < typename VERTEX >
      //void create_vertex_array(int iCount)
      //{

      //   auto pgpuframe = ::gpu::current_frame();

      //   initialize_gpu_context_object(pgpuframe->gpu_context());

      //   auto pcommandbuffer = pgpuframe->m_pgpucommandbuffer;

      //   bind2(pcommandbuffer);

      //   this->create_vertexes<::graphics3d::sequence2_color >(iCount);

      //   unbind(pcommandbuffer);

      //   //defer_set_input_layout(pcontext->input_layout(::gpu_properties < ::graphics::sequence2_color>()));

      //}


      template < typename VERTEX >
      void static_initialize_vertexes(const ::array_base<VERTEX> & vertexa)
      {

         auto &modeldata = model_data<VERTEX>();

         modeldata.set_vertexes(vertexa);

         ødefer_construct(m_pbufferVertex);

         auto blockVertexData = modeldata.vertex_data();

         m_pbufferVertex->static_initialize_memory_buffer_with_model_buffer(
            this, blockVertexData, memory_buffer::e_type_vertex_buffer);

         set_input_layout(m_pgpucontext->input_layout(::gpu_properties< VERTEX >()));

      }


      virtual ::gpu::command_buffer* _defer_get_loading_command_buffer();

      virtual void initialize_dummy_model(::gpu::context* pcontext, int iVertexCount);


      //virtual void static_initialize_vertexes_block(const ::block& blockvertexes);
      //virtual void static_initialize_indexes_block(const ::block& blockindexes);

      template < typename INDEX >
      void create_indexes(::collection::count iIndexCount)
      {

         if (m_pmodeldatabase2->vertex_bytes() <= 0)
         {
            // please set the vertex first
            throw ::exception(error_wrong_state);

         }

         m_pmodeldatabase2->set_index_type_and_count<INDEX>(iIndexCount);

         auto size = m_pmodeldatabase2->index_bytes();

         ødefer_construct(m_pbufferIndex);

         m_pbufferIndex->initialize_memory_buffer_with_model_buffer(
            this,
            size,
            memory_buffer::e_type_index_buffer);

      }

      
      template < typename INDEX >
      void static_initialize_indexes(const ::array_base<INDEX>& indexes)
      {

                  if (typeid(INDEX) != m_pmodeldatabase2->index_type())
         {

            throw ::exception(error_wrong_state);
         }


         //m_iIndexCount = (int)indexa.count();

         //m_iIndexTypeSize = sizeof(INDEX);

         //auto size = indexa.get_size_in_bytes();

         //ødefer_construct(m_pbufferIndex);

         //m_pbufferIndex->static_initialize_memory_buffer_with_model_buffer(
         //   this,
         //   indexa.data(),
         //   size,
         //   memory_buffer::e_type_index_buffer);

                  m_pmodeldatabase2->set_indexes(indexes);

      /*m_iIndexCount = (int)iIndexCount;

         m_iIndexTypeSize = (int)iTypeSize;*/

         //auto size = iIndexCount * m_iIndexTypeSize;

         ødefer_construct(m_pbufferIndex);

         auto blockIndexData = m_pmodeldatabase2->index_data();

         m_pbufferIndex->static_initialize_memory_buffer_with_model_buffer(this, 
            blockIndexData,
                                                                           memory_buffer::e_type_index_buffer);


      }

      template<typename VERTEX>
      void static_initialize(const ::gpu::model_data<VERTEX> &modeldata)
      {

         static_initialize_vertexes(modeldata.vertexes());

         if (modeldata.indexes().has_elements())
         {

            static_initialize_indexes(modeldata.indexes());
         }

      }

      void static_initialize(const ::gpu::model_data_base * pmodeldata)
      {

         m_pmodeldatabase2 = pmodeldata;

         _static_initialize_vertex_buffer(pmodeldata->vertex_data());

         if (pmodeldata->index_count() > 0)
         {

            _static_initialize_index_buffer(pmodeldata->index_data());
         }

         set_input_layout(m_pgpucontext->input_layout(m_pmodeldatabase2->gpu_properties()));

      }

      template < typename VERTEX >
      void set_vertexes(const ::array < VERTEX > & vertexa)
      {

         if (typeid(VERTEX) != m_pmodeldatabase2->vertex_type())
         {

            throw ::exception(error_wrong_state);

         }

         m_pmodeldatabase2->set_vertexes(vertexa);


         auto blockVertexData = m_pmodeldatabase2->vertex_data();
         m_pbufferVertex->on_set_memory_buffer(
            blockVertexData);

      }


      template < typename VERTEX >
      void _set_vertexes(const ::array < VERTEX >& vertexa)
      {

         if (typeid(VERTEX) != m_pmodeldatabase2->vertex_type())
         {

            throw ::exception(error_wrong_state);
         }

         m_pbufferVertex->_on_set_memory_buffer(vertexa.data(), vertexa.get_size_in_bytes());

      }


      template < typename INDEX >
      void set_index_array(const INDEX* p, ::collection::count iIndexCount)
      {

         if (typeid(INDEX) != m_pmodeldatabase2->index_type())
         {

            throw ::exception(error_wrong_state);

         }

         m_pbufferIndex->assign(p, sizeof(INDEX) * iIndexCount);

      }


      template < typename VERTEX >
      void _set_vertex_array(const VERTEX* p, ::collection::count iVertexCount)
      {

         if (typeid(VERTEX) != m_pmodeldatabase2->vertex_type())
         {

            throw ::exception(error_wrong_state);

         }

         m_pbufferVertex->_assign(p, sizeof(VERTEX) * iVertexCount);// data = map_base <VERTEX >();

      }


      template < typename INDEX >
      void _set_index_array(const INDEX* p, ::collection::count iIndexCount)
      {

         if (typeid(INDEX) != m_pmodeldatabase2->index_type_size())
         {

            throw ::exception(error_wrong_state);

         }

         m_pbufferIndex->_assign(p, sizeof(INDEX) * iIndexCount);

      }


      virtual void bind_load_assets_command_buffer(::gpu::context *pcontext);
      virtual void unbind_load_assets_command_buffer(::gpu::context *pcontext);

      template < typename VERTEX >
      void set_data(const ::gpu::model_data<VERTEX> &modeldata)
      {

         if (!m_papplication || !m_pgpucontext)
         {

            // should call initialize(pcontext);

            // should call initialize_gpu_context_object(pcontext);

            throw ::exception(error_wrong_state);

         }

         bind_load_assets_command_buffer(m_pgpucontext);

         static_initialize(modeldata);

         unbind_load_assets_command_buffer(m_pgpucontext);

      }


      void set_data(const ::gpu::model_data_base * pmodeldata)
      {

         if (!m_papplication || !m_pgpucontext)
         {

            // should call initialize(pcontext);

            // should call initialize_gpu_context_object(pcontext);

            throw ::exception(error_wrong_state);
         }

         bind_load_assets_command_buffer(m_pgpucontext);

         static_initialize(pmodeldata);

         unbind_load_assets_command_buffer(m_pgpucontext);
      }


      virtual void initialize_dummy_model(::gpu::renderer *pgpurenderer, int ivertexes);


      virtual bool is_dummy() const;

      void sequence2_uv_create_fullscreen_quad(::gpu::frame* pgpuframe);
      void sequence2_color_create_rectangle(::gpu::frame* pgpuframe);
      void sequence2_color_create_line(::gpu::frame* pgpuframe);
      void sequence3_color_create_rectangle(::gpu::frame* pgpuframe);
      void sequence3_color_create_line(::gpu::frame* pgpuframe);


      void sequence3_color_set_rectangle(
         const ::double_point points1[4],
         const  ::color::color& color,
         const ::double_size& size);

      void sequence2_color_set_rectangle(
         const ::double_point * ppoints1 /* [4]tl,tr,br,bl */,
         const ::color::color& color,
         const ::double_size& size);

      void sequence2_color_set_rectangle(
         const ::double_point* ppoints1 /* [4]tl,tr,br,bl */,
         const ::color::color& color);

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
      memory_map < memory_buffer, INDEX > map_indexes()
      {

         return { m_pbufferIndex.m_p, (INDEX*)nullptr };

      }

      //virtual void* _map(memsize start, memsize count);
      //virtual void unmap();

      void bind2(::gpu::command_buffer* pcommandbuffer) override;

      void draw2(::gpu::command_buffer* pcommandbuffer) override;

      virtual void draw_lines(::gpu::command_buffer* pcommandbuffer);

      void unbind(::gpu::command_buffer* pcommandbuffer) override;

      virtual void set_input_layout(::gpu::input_layout* pinputlayout);

      virtual void apply_input_layout();


   };


} // namespace gpu



