#pragma once


#include "aura/graphics/gpu/renderer.h"
//#include "mesh.h"
#include "shader.h"
//#include "GLFW/glfw3.h"
#include <memory>
#include <glm/glm.hpp>


namespace gpu_opengl
{


   class CLASS_DECL_GPU_OPENGL renderer :
      virtual public ::gpu::renderer
   {
   public:


      int instanceCount = 0;

      GLuint m_VAOFullScreenQuad;
      GLuint m_VBOFullScreenQuad;
      ::pointer < ::gpu::shader > m_pshaderBlend; 

      GLuint m_vaoQuadBlend, m_vboQuadBlend;



      //memory m_memory;
      //pixmap m_pixmap;
      renderer();
      ~renderer();


      //void set_placement(const ::int_rectangle& rectanglePlacement);

      void on_context_resize() override;

      ::pointer < ::gpu::frame > beginFrame() override;

      virtual void on_begin_render(::gpu::frame* pframe);

      void Clear() const;


      int get_frame_count() const override;
      // Draws the skybox using the given mesh and shader
      //void DrawSkybox(const mesh *pskyboxMesh, ::gpu::shader * pshader) const;

      //void DrawInstanced(const ::array<mesh*>& meshes, ::gpu::shader *pshader, unsigned int instanceCount) const;
      void MultiDrawIndirectCommand() {}

      //void DrawModel(const ::array<mesh*>& mehses, ::gpu::shader *pshader);

      void endFrame() override;

      //void endDraw(::user::interaction * puserinteraction) override;

      virtual void _sample();

      virtual void _swap();

      void endDraw(::user::interaction * puserinteraction, ::gpu::renderer * pgpurendererSrc) override;

      //virtual void on_layout(int cx, int cy);

      void blend(::gpu::renderer* prendererSource) override;

   };



} // namespace gpu_opengl



