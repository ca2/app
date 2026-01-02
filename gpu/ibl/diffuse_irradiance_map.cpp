// From github:/tristancalderbank/OpenGL-PBR-Renderer/diffuse_irradiance_map.cpp by
// camilo on 2025-09-26 19:53 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "diffuse_irradiance_map.h"
#include "bred/gpu/binding.h"
#include "bred/gpu/command_buffer.h"
#include "bred/gpu/context.h"
#include "bred/gpu/shader.h"
#include "bred/gpu/texture.h"
#include "bred/platform/timer.h"
#include "bred/graphics3d/engine.h"
#include "bred/graphics3d/scene_base.h"
#include "bred/graphics3d/shape_factory.h"
#include "bred/graphics3d/skybox.h"
#include "acme/prototype/mathematics/mathematics.h"


namespace gpu
{


   namespace ibl
   {


      diffuse_irradiance_map::diffuse_irradiance_map()
      {


      }


      diffuse_irradiance_map::~diffuse_irradiance_map()
      {


      }


      ::block diffuse_irradiance_map::embedded_diffuse_irradiance_vert()
      {

         return {};

      }


      ::block diffuse_irradiance_map::embedded_diffuse_irradiance_frag()
      {

         return {};

      }


      void diffuse_irradiance_map::initialize_diffuse_irradiance_map(
         ::graphics3d::scene_base * pscenebase)
      {

         initialize_scene_object(pscenebase);

         øconstruct(m_pshaderDiffuseIrradiance);

         m_pshaderDiffuseIrradiance->m_bDisableDepthTest = true;
         m_pshaderDiffuseIrradiance->m_bEnableBlend = false;
         m_pshaderDiffuseIrradiance->m_ecullmode = ::gpu::e_cull_mode_none;

         auto pgpupropertiesVertex = ::gpu_properties<::graphics3d::shape_factory::Vertex>();

         auto pinputlayoutVertex = m_pgpucontext->input_layout(pgpupropertiesVertex);

         m_pshaderDiffuseIrradiance->m_propertiesPushShared.set_properties(::gpu_properties<push_constants>());

         m_pgpucontext->layout_push_constants(m_pshaderDiffuseIrradiance->m_propertiesPushShared, false);

         auto pbindingCubeSampler = m_pshaderDiffuseIrradiance->binding();
         pbindingCubeSampler->m_ebinding = ::gpu::e_binding_cube_sampler;
         pbindingCubeSampler->m_strUniform = "environmentCubemap";
         pbindingCubeSampler->m_iTextureUnit = 0;

         m_pshaderDiffuseIrradiance->initialize_shader_with_block(
            m_pgpucontext->m_pgpurenderer, 
            embedded_diffuse_irradiance_vert(), 
            embedded_diffuse_irradiance_frag(), 
            pinputlayoutVertex);

         øconstruct(m_ptextureDiffuseIrradianceCubemap);

         ::gpu::texture_attributes textureattributes(::int_rectangle {
            API_CHANGED_ARGUMENT, m_udiffuse_irradiance_mapWidth, m_udiffuse_irradiance_mapHeight});

         textureattributes.set_cubemap();

         //textureattributes.set_cubemap_all_mips();

         ::gpu::texture_flags textureflags;

         textureflags.m_bRenderTarget = true;

         m_ptextureDiffuseIrradianceCubemap->initialize_texture(m_pgpucontext->m_pgpurenderer, textureattributes, textureflags);

         //m_ptextureDiffuseIrradianceCubemap->initialize_mipmap_cubemap_texture(
           // m_pgpucontext->m_pgpurenderer, ::int_rectangle{ API_CHANGED_ARGUMENT,m_udiffuse_irradiance_mapWidth, m_udiffuse_irradiance_mapHeight});

         m_prenderableCube = m_pgpucontext->m_pengine->shape_factory()->create_cube_001(m_pgpucontext, 2.f);

      }


      void diffuse_irradiance_map::computeIrradianceMap(::gpu::command_buffer *pgpucommandbuffer)
      {

         ::bred::Timer timer;

         using namespace graphics3d;

         floating_matrix4 model = ::graphics3d::mIndentity4;

         floating_matrix4 cameraAngles[] = {
             lookAt(origin, unitX, -unitY), // X+ (right)
             lookAt(origin, -unitX, -unitY), // X- (left)
             lookAt(origin, unitY, unitZ), // Y+ (top)
             lookAt(origin, -unitY, -unitZ), // Y- (bottom)
             lookAt(origin, unitZ, -unitY), // Z+ (front)
             lookAt(origin, -unitZ, -unitY) // Z- (back)
          };

          floating_matrix4 projection =
             m_pgpucontext->m_pengine->perspective(90f_degrees, // 90 degrees to cover one face
                                                   1.0f, // its a square
                                                   0.1f, 2.0f);
         
          auto pskybox = m_pscene->current_skybox();

          auto ptextureSkybox = pskybox->m_ptexture;

          int iIrradianceMapWidth = m_udiffuse_irradiance_mapWidth;

          int iIrradianceMapHeight = m_udiffuse_irradiance_mapHeight;

          m_ptextureDiffuseIrradianceCubemap->set_current_mip(-1);

          m_ptextureDiffuseIrradianceCubemap->set_current_layer(-1);

          m_ptextureDiffuseIrradianceCubemap->set_state(pgpucommandbuffer, ::gpu::e_texture_state_color_attachment);

          m_ptextureDiffuseIrradianceCubemap->set_current_mip(0);

          // render to each side of the cubemap
          for (auto i = 0; i < 6; i++)
          {

             auto impact = cameraAngles[i];

             m_ptextureDiffuseIrradianceCubemap->set_current_layer(i);

             pgpucommandbuffer->begin_render(m_pshaderDiffuseIrradiance, m_ptextureDiffuseIrradianceCubemap);

             ::int_rectangle r(0, 0, iIrradianceMapWidth, iIrradianceMapHeight);

             pgpucommandbuffer->set_viewport(r);

             pgpucommandbuffer->set_source(ptextureSkybox);

             auto mvp = projection * impact * model;

             m_pshaderDiffuseIrradiance->set_matrix4("mvp", mvp);

             m_pshaderDiffuseIrradiance->set_float("deltaPhi", (2.0f * float(this->mathematics()->π())) / 180.0f);

             m_pshaderDiffuseIrradiance->set_float("deltaTheta", (0.5f * float(this->mathematics()->π())) / 64.0f);

             m_pshaderDiffuseIrradiance->push_properties(pgpucommandbuffer);

             pgpucommandbuffer->draw(m_prenderableCube);

             pgpucommandbuffer->end_render();
            
          }

          m_ptextureDiffuseIrradianceCubemap->set_current_mip(-1);

          m_ptextureDiffuseIrradianceCubemap->set_current_layer(-1);

          m_ptextureDiffuseIrradianceCubemap->set_state(pgpucommandbuffer, ::gpu::e_texture_state_shader_read);

          m_ptextureDiffuseIrradianceCubemap->set_ok_flag();
         
          timer.logDifference("Rendered diffuse irradiance map");
        
      }


   } // namespace ibl


} // namespace gpu


BEGIN_GPU_PROPERTIES(::gpu::ibl::diffuse_irradiance_map::push_constants)
GPU_PROPERTY("mvp", ::gpu::e_type_mat4)
//GPU_PROPERTY("view", ::gpu::e_type_mat4)
//GPU_PROPERTY("projection", ::gpu::e_type_mat4)
GPU_PROPERTY("deltaPhi", ::gpu::e_type_float)
GPU_PROPERTY("deltaTheta", ::gpu::e_type_float)
END_GPU_PROPERTIES()



