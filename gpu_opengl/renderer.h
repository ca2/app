#pragma once


#include "bred/gpu/renderer.h"
//#include "mesh.h"
#include "shader.h"
//#include "GLFW/glfw3.h"
#include <memory>
//


namespace gpu_opengl
{


   class CLASS_DECL_GPU_OPENGL renderer :
      virtual public ::gpu::renderer
   {
   public:


      ::i32 instanceCount = 0;

      ::pointer < ::gpu::shader > m_pshaderBlend; 
      ::pointer < ::gpu_opengl::shader > m_pshaderBlend2;

      GLuint m_vaoQuadBlend, m_vboQuadBlend;

      GLuint m_vaoQuadBlend2, m_vboQuadBlend2;

      //::i32_size m_sizeRenderer;



      renderer();
      ~renderer();


      //void set_placement(const ::i32_rectangle& rectanglePlacement);

      void on_context_resize() override;

      //::pointer < ::gpu::frame > beginFrame() override;

      //void start_frame() override;

      //void on_new_frame() override;

      //void on_begin_frame() override;

      //virtual void _ensure_renderer_framebuffer();

      void _on_begin_render(::gpu::layer * pgpulayer) override;

      void on_begin_render(::gpu::layer * pgpulayer) override;

      //void Clear() const;


      //::i32 get_frame_count() override;
      // Draws the skybox using the given mesh and shader
      //void DrawSkybox(const mesh *pskyboxMesh, ::gpu::shader * pshader) const;

      //void DrawInstanced(const ::array<mesh*>& meshes, ::gpu::shader *pshader, ::u32 instanceCount) const;
      void MultiDrawIndirectCommand() {}

      //void DrawModel(const ::array<mesh*>& mehses, ::gpu::shader *pshader);

      //void endFrame() override;

      //void end_frame() override;

      //void endDraw(::user::interaction * puserinteraction) override;

      virtual void do_sampling_to_cpu();
      void sample_to_cpu_buffer() override;

      //virtual void _swap();

      //void endDraw(::draw2d_gpu::graphics * pgraphics, ::user::interaction * puserinteraction) override;

      //virtual void on_layout(::i32 cx, ::i32 cy);

      //void on_start_layer(::gpu::layer * pgpulayer) override;
      //void on_end_layer(::gpu::layer * pgpulayer) override;



      //void blend(::gpu::renderer* prendererSource) override;
      //void clear(::gpu::texture* ptextureSource) override;
      //void copy(::gpu::texture* ptextureTarget, ::gpu::texture* ptextureSource) override;
      //void blend(::gpu::texture* ptextureTarget, ::gpu::texture* ptextureSource) override;
      void _blend_with_shader(::gpu::texture* ptextureTarget, ::gpu::texture* ptextureSource);
      void _blend_with_blit(::gpu::texture* ptextureTarget, ::gpu::texture* ptextureSource);


      //virtual void __blend(::gpu::texture* ptextureTarget, ::gpu::texture* ptextureSource);

      //void defer_update_renderer() override;
      //void on_defer_update_renderer_allocate_render_target(::gpu::enum_output eoutput, const ::i32_size& size, ::gpu::render_target* previous) override;

      //::pointer < ::gpu::render_target > allocate_offscreen_render_target() override;


   };



} // namespace gpu_opengl



