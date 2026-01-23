// From github:/tristancalderbank/OpenGL-PBR-Renderer/gltf_mesh.h by
// camilo on 2025-09-26 18:28 <3ThomasBorregaardSorensen!!
#pragma once


#include "bred/gpu/context_object.h"
#include "bred/graphics3d/renderable.h"
#include "bred/gpu/shader.h"
#include "gpu/model/material.h"
#include "bred/gltf/vertex.h"
#include "bred/graphics3d/types.h" // for Vertex
#include "bred/gpu/model_data.h"


namespace gpu
{


   namespace model
   {


      /**
       * A mesh is a collection of geometry paired with a material.
       */
      class CLASS_DECL_GPU mesh :
         virtual public context_object, 
         virtual public ::graphics3d::renderable
      {
      public:


         //::array_base<::gpu::gltf::vertex> m_vertexa;
         //unsigned_int_array m_indexa;
         //::gpu::model_data<::gpu::gltf::vertex> m_modeldataGltf;
         //::gpu::model_data<::graphics3d::Vertex> m_modeldataWavefront;
         ::pointer<::gpu::model_data_base> m_pmodeldata;
         ::pointer<::gpu::model_buffer> m_pmodelbuffer;
         ::pointer<::gpu::model::material> m_pmaterial;
         struct UniformBlock {
            floating_matrix4 matrix;
            floating_matrix4 jointMatrix[64]{};
            float jointcount{ 0 };
         } uniformBlock;


         mesh();
         ~mesh() override;

         virtual ::collection::index indexes_count() const;


         virtual void initialize_gpu_mesh(::gpu::context * pgpucontext, ::gpu::model::material * pmaterial, ::gpu::model_data_base * pmodeldata);

         //virtual void on_initialize_gpu_mesh();


         void draw2(::gpu::command_buffer *pcommandbuffer) override;


      };


   } // namespace model


} // namespace gpu
