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
// 
// 
// 
// 
// 
// #include <functional>
//
// //#include <memory>
// //#include <vector>
// //#include <unordered_map>
// //


namespace graphics3d
{




   //template < typename VERTEX >
   //class model :
   //   virtual public ::gpu::model_buffer
   //{
   //public:


   //   //

   //   //struct Builder
   //   //{
   //   //   ::array<VERTEX> vertexes{};
   //   //   ::array<uint32_t> indexes{};

   //   //};


   //   //::pointer < ::gpu::renderer >        m_pgpurenderer;
   //   //bool m_bDummy = false;
   //   //int m_ivertexes = 0;
   //   //::pointer < ::gpu::command_buffer > m_pcommandbufferLoading;

   //   //static ::pointer<model> createModelFromFile(::graphics3d::context * pgpucontext, const ::file::path & path);


   //   model();
   //   ~model();


   //   virtual void initialize_model(::gpu::renderer * prenderer, const model_data < VERTEX > & modeldata);
   //   virtual void initialize_dummy_model(::gpu::renderer* prenderer, int ivertexes);

   //   //virtual void draw(::gpu::context* pgpucontext);
   //   //virtual void bind(::gpu::context* pgpucontext);
   //   //virtual void unbind(::gpu::context* pgpucontext);
   //   //virtual void draw();
   //   //virtual void bind();
   //   //virtual void unbind();

   ////private:
   ////   void createVertexBuffers(const ::array<Vertex>& vertexes);
   ////   void createIndexBuffers(const ::array<uint32_t>& indexes);

   ////   bool hasIndexBuffer = false;
   ////   ::pointer < context > m_pgpucontext;


   ////   ::pointer<buffer> vertexBuffer;
   ////   uint32_t vertexCount;

   ////   ::pointer<buffer> indexBuffer;
   ////   uint32_t indexCount;

   //};


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
      public ::gpu::model_data<::graphics3d::Vertex>
   {

      void loadModel_001(::gpu::context* pgpucontext, const ::file::path& path);
      void loadModel_002(::gpu::context *pgpucontext, const ::file::path &path);
      void loadModel(::gpu::context *pgpucontext, const ::file::path &path);
      bool LoadObjAndConvert( // float bmin[3], float bmax[3], //std::vector<DrawObject> *drawObjects,
                              //                                            std::vector<tinyobj::material_t> &materials,
                              //                                          std::map<std::string, GLuint> &textures,
         ::gpu::context *pgpucontext, 
         const ::file::path &path);

   };

      void LoadObjAndConvert_recompute_normals();


   //template < typename VERTEX >
   //model<VERTEX>::model()
   //{


   //}


   //template < typename VERTEX >
   //model<VERTEX>::~model()
   //{


   //}


   //template < typename VERTEX >
   //void model<VERTEX>::initialize_model(::gpu::renderer* pgpurenderer, const model_data<VERTEX >& modeldata)
   //{

   //   initialize(pgpurenderer);
   //   
   //   initialize_gpu_context_object(pgpurenderer->m_pgpucontext);

   //   bind(pgpurenderer->getLoadAssetsCommandBuffer());

   //   static_initialize_vertexes(modeldata.m_vertexes);

   //   static_initialize_indexes(modeldata.m_indexes);

   //   unbind(pgpurenderer->getLoadAssetsCommandBuffer());

   //}


   //template < typename VERTEX >
   //void model<VERTEX>::initialize_dummy_model(::gpu::renderer* pgpurenderer, int ivertexes)
   //{

   //   initialize(pgpurenderer);

   //   initialize_gpu_context_object(pgpurenderer->m_pgpucontext);

   //   //m_pgpurenderer = pgpurenderer;

   //   m_bDummy = true;

   //   ødefer_construct(m_pbufferVertex);

   //   m_pbufferVertex->initialize_memory_buffer_with_model_buffer(this, 0, ::gpu::memory_buffer::e_type_none);
   //   
   //   m_iVertexCount = ivertexes;

   //}



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

