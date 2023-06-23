// Created by camilo on 2022-04-25 20:42 <3ThomasBorregaardSorensen!!
#pragma once


#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "acme/primitive/geometry3d/location.h"
#include "aura/graphics/gpu/object.h"


namespace opengl
{


   class object :
      virtual public ::gpu::object
   {
   public:


      ::gpu::element             m_vao_vertices;
      ::gpu::element             m_vao_normals;

      ::gpu::element             m_vbo_vertices;
      ::gpu::element             m_vbo_normals;
      ::gpu::element             m_vbo_uvs;

      ::gpu::element             m_ibo_elements;

      ::array<unsigned short>    m_indices;
      ::array<::glm::vec3>       m_vertices;
      ::array<::glm::vec2>       m_uvs;
      ::array<::glm::vec3>       m_normals;

      ::gpu::uniform             m_iTextureUniform;
      ::gpu::element             m_uniformTexture;


      ::file::path               m_path;


      object();
      ~object() override;


      void load(const ::file::path & path) override;


      //void prepare(::gpu::approach * papproach) override;


      void _prepare(::gpu::approach * papproach) override;


      void draw() override;

      
      void set_texture_uniform(::gpu::uniform uniformTexture) override;


   };



} // namespace opengl


