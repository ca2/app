#pragma once
//#include <vector>
#include <glm/glm.hpp>
#include "bred/gpu/context_object.h"
#include "bred/graphics3d/model.h"
#include "bred/graphics3d/shape_factory.h"


namespace graphics3d
{



   class CLASS_DECL_BRED mesh:
      virtual public ::gpu::context_object
   {
   public:

      using Vertex = ::graphics3d::shape_factory::Vertex;
      

      ::pointer_array<::gpu::texture>                 m_texturea;
      ::graphics3d::model_data<Vertex>                m_modeldata;
      ::pointer < ::graphics3d::model < Vertex > >    m_pmodel;
      //unsigned int m_VAO, m_VBO, m_EBO;
      unsigned int m_IndexOffset;
      unsigned int m_IndexCount;
      unsigned int m_VertexOffset;
      ::array<glm::mat4> m_ModelMatrices;
      // New instance buffer
      //unsigned int m_InstanceVBO;



      mesh();
      ~mesh() override;


      virtual void initialize_mesh(const model_data<Vertex>& data);

      //void initialize_mesh(
      //   const model_data<Vertex>& data,
      //   unsigned int vertexOffset,
      //   unsigned int indexOffset,
      //   unsigned int indexCount);

      virtual void bind();
      virtual void unbind();
      virtual unsigned int GetIndexCount() const;
      virtual unsigned int GetIndexOffset() const;
      virtual void SetInstanceModelMatrices(const ::array<glm::mat4>& modelmatricies);
      virtual void UpdateInstanceModelMatrices(const ::array<glm::mat4>& modelMatrices);


      virtual void draw_instanced();

      virtual void draw(::gpu::shader * pshader);
   //private:
      virtual void SetupMesh();

    
   };


} // namespace graphics3d


