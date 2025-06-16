#pragma once


#include "bred/gpu/renderer.h"
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

      ::pointer < ::gpu::shader > m_pshaderBlend; 
      ::pointer < ::gpu_opengl::shader > m_pshaderBlend2;

      GLuint m_vaoQuadBlend, m_vboQuadBlend;

      ::int_size m_sizeRenderer;

      GLuint m_iFrameBufferRenderer;


      renderer();
      ~renderer();


      //void set_placement(const ::int_rectangle& rectanglePlacement);

      void on_context_resize() override;

      ::pointer < ::gpu::frame > beginFrame() override;

      void _on_begin_render();

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

      virtual void do_sampling_to_cpu();

      virtual void _swap();

      void endDraw(::draw2d_gpu::graphics * pgraphics, ::user::interaction * puserinteraction) override;

      //virtual void on_layout(int cx, int cy);

      void on_start_layer(::gpu::layer* player) override;

      void blend(::gpu::renderer* prendererSource) override;
      void clear(::gpu::texture* ptextureSource) override;
      void blend(::gpu::texture* ptextureTarget, ::gpu::texture* ptextureSource) override;

      void defer_update_renderer() override;

   };



} // namespace gpu_opengl



