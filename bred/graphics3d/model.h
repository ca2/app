// From V0idsEmbrace@Twich continuum project
// by camilo on 2025-05-17 02:40 <3ThomasBorregaardSorensen!!
#pragma once


//#include "device.h"
//#include "buffer.h"
#include "bred/gpu/model_buffer.h"
#include "bred/gpu/renderer.h"
#include "bred/graphics3d/utilities.h"
#include "bred/graphics3d/types.h"

//
//
// #define GLM_FORCE_RADIANS
// #define GLM_FORCE_DEPTH_ZERO_TO_ONE
// #include <glm/glm.hpp>
// #include <glm/vec3.hpp>
// #include <glm/vec2.hpp>
// #include <functional>
//
// //#include <memory>
// //#include <vector>
// //#include <unordered_map>
// //


namespace graphics3d
{



   template < typename VERTEX >
   class model_data
   {
   public:

      ::array<VERTEX> m_vertexes;
      ::array<unsigned int > m_indexes;


      //::pointer <::graphics3d::model> create_model(
      //   ::gpu::renderer* prenderer)
      //{

      //   auto pmodel = prenderer->øcreate < ::graphics3d::model >();

      //   pmodel->initialize_model(
      //      prenderer,
      //      m_vertexes.as_block(),
      //      m_indexes.as_block());

      //   auto pgpucontext = prenderer->m_pgpucontext;

      //   auto pinputlayout = pgpucontext->input_layout(::gpu_properties< VERTEX >());

      //   pmodel->defer_set_input_layout(pinputlayout);

      //   return pmodel;

      //}


   };


   template < typename VERTEX >
   class model :
      public ::pointer < ::gpu::model_buffer >
   {
   public:


      //

      //struct Builder
      //{
      //   ::array<VERTEX> vertexes{};
      //   ::array<uint32_t> indexes{};

      //};


      //::pointer < ::gpu::renderer >        m_pgpurenderer;
      //bool m_bDummy = false;
      //int m_ivertexes = 0;
      //::pointer < ::gpu::command_buffer > m_pcommandbufferLoading;

      //static ::pointer<model> createModelFromFile(::graphics3d::context * pgpucontext, const ::file::path & path);


      model();
      ~model();


      virtual void initialize_model(::gpu::renderer * prenderer, const model_data < VERTEX > & modeldata);
      virtual void initialize_dummy_model(::gpu::renderer* prenderer, int ivertexes);

      //virtual void draw(::gpu::context* pgpucontext);
      //virtual void bind(::gpu::context* pgpucontext);
      //virtual void unbind(::gpu::context* pgpucontext);
      //virtual void draw();
      //virtual void bind();
      //virtual void unbind();

   //private:
   //   void createVertexBuffers(const ::array<Vertex>& vertexes);
   //   void createIndexBuffers(const ::array<uint32_t>& indexes);

   //   bool hasIndexBuffer = false;
   //   ::pointer < context > m_pgpucontext;


   //   ::pointer<buffer> vertexBuffer;
   //   uint32_t vertexCount;

   //   ::pointer<buffer> indexBuffer;
   //   uint32_t indexCount;

   };


   //using model_pointer = ::pointer < ::model >;
   //template < typename VERTEX >
   //class model_pointer :
   //   public ::pointer < ::model >
   //{
   //public:


   //   //::pointer < model > m_pmodel;




   //   //::pointer < ::gpu::renderer >        m_pgpurenderer;
   //   //bool m_bDummy = false;
   //   //int m_ivertexes = 0;
   //   //::pointer < ::gpu::command_buffer > m_pcommandbufferLoading;

   //   //static ::pointer<model> createModelFromFile(::graphics3d::context * pgpucontext, const ::file::path & path);


   //   model_pointer()
   //   {
   //   
   //   }

   //   ~model_pointer()
   //   {
   //   
   //   }


      //virtual void initialize_model(
      //   ::gpu::renderer* prenderer,
      //   const model_data<VERTEX>& data)
      //{

      //   prenderer->ødefer_construct(m_pmodelbase);

      //   m_pmodelbase->initialize_model(
      //      prenderer,
      //      data.m_vertexes.as_block(),
      //      data.m_indexes.as_block());

      //}

      //virtual void initialize_dummy_model(::gpu::renderer* prenderer, int ivertexes)
      //{

      //   prenderer->ødefer_construct(m_pmodelbase);

      //   m_pmodelbase->initialize_dummy_model(
      //      prenderer,
      //      ivertexes);

      //}

      //virtual void draw(::gpu::context* pgpucontext);
      //virtual void bind(::gpu::context* pgpucontext);
      //virtual void unbind(::gpu::context* pgpucontext);
      //virtual void draw() { m_pmodelbase->draw(); }
      //virtual void bind() { m_pmodelbase->bind(); }
      //virtual void unbind() { m_pmodelbase->unbind(); }

      //private:
      //   void createVertexBuffers(const ::array<Vertex>& vertexes);
      //   void createIndexBuffers(const ::array<uint32_t>& indexes);

      //   bool hasIndexBuffer = false;
      //   ::pointer < context > m_pgpucontext;


      //   ::pointer<buffer> vertexBuffer;
      //   uint32_t vertexCount;

      //   ::pointer<buffer> indexBuffer;
      //   uint32_t indexCount;

   // };




   //virtual void initialize_dummy_model(::gpu::renderer* prenderer, int ivertexes)
   //{

   //   prenderer->ødefer_construct(m_pmodelbase);

   //   m_pmodelbase->initialize_dummy_model(
   //      prenderer,
   //      ivertexes);

   //}

   struct CLASS_DECL_BRED tinyobjloader_Builder :
      public model_data<::graphics3d::Vertex>
   {

      void loadModel(::gpu::context* pgpucontext, const ::file::path& path);

   };


   template < typename VERTEX >
   model<VERTEX>::model()
   {


   }


   template < typename VERTEX >
   model<VERTEX>::~model()
   {


   }


   template < typename VERTEX >
   void model<VERTEX>::initialize_model(::gpu::renderer* pgpurenderer, const model_data<VERTEX >& modeldata)
   {

      pgpurenderer->ødefer_construct(*this);
      
      m_p->initialize_gpu_context_object(pgpurenderer->m_pgpucontext);

      m_p->bind(pgpurenderer->getLoadAssetsCommandBuffer());

      m_p->static_initialize_vertexes(modeldata.m_vertexes);

      m_p->static_initialize_indexes(modeldata.m_indexes);

      m_p->unbind(pgpurenderer->getLoadAssetsCommandBuffer());

   }


   template < typename VERTEX >
   void model<VERTEX>::initialize_dummy_model(::gpu::renderer* pgpurenderer, int ivertexes)
   {

      pgpurenderer->ødefer_construct(*this);

      m_p->initialize_gpu_context_object(pgpurenderer->m_pgpucontext);

      //m_p->m_pgpurenderer = pgpurenderer;

      m_p->m_bDummy = true;

      m_p->ødefer_construct(m_p->m_pbufferVertex);

      m_p->m_pbufferVertex->initialize_memory_buffer_with_model_buffer(m_p, 0, ::gpu::memory_buffer::e_type_none);
      
      m_p->m_iVertexCount = ivertexes;

   }



   //template < typename VERTEX >
   //void model<VERTEX>::draw()
   //{


   //}



   //template < typename VERTEX >
   //void model<VERTEX>::bind()
   //{



   //}


   //template < typename VERTEX >
   //void model<VERTEX>::unbind()
   //{



   //}





}  // namespace graphics3d





//namespace std {
//   template <>
//   struct hash<::gpu::Vertex>
//   {




//   };
//
//}  // namespace std
//

