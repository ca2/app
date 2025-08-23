#include "framework.h"
#include "skybox_render_system.h"
#include "bred/gpu/device.h"
#include "bred/gpu/frame.h"
#include "bred/gpu/render_target.h"
#include "bred/gpu/texture.h"
#include "bred/graphics3d/engine.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "aura/graphics/image/context.h"
#include "aura/platform/application.h"
#include <stb/stb_image.h>
#include <iostream>


namespace graphics3d
{


   // Constructor
   skybox_render_system::skybox_render_system()
   {


   }


   // Destructor
   skybox_render_system::~skybox_render_system() {
      //glDeleteVertexArrays(1, &skyboxVAO);
      //glDeleteBuffers(1, &skyboxVBO);
      //glDeleteTextures(1, &cubemapTexture);
   }


   void skybox_render_system::initialize_skybox_render_system(engine * pengine, const ::scoped_string & scopedstrName)
   {

      ::graphics3d::render_system::initialize_render_system(pengine);

      cube cube;

      cube.add(::file::path("matter://textures") / scopedstrName / "right.png");
      cube.add(::file::path("matter://textures") / scopedstrName / "left.png");
      cube.add(::file::path("matter://textures") / scopedstrName / "top.png");
      cube.add(::file::path("matter://textures") / scopedstrName / "bottom.png");
      cube.add(::file::path("matter://textures") / scopedstrName / "front.png");
      cube.add(::file::path("matter://textures") / scopedstrName / "back.png");

      m_cube = cube;

      m_pengine = pengine;


      auto modeldataCube = ::graphics3d::shape_factory::create_cube(32.0f);

      ødefer_construct_new(m_pmodelCube);

      m_pmodelCube->initialize_model(pengine->gpu_context()->m_pgpurenderer, modeldataCube);

      // Initialize skybox shader
      ødefer_construct(m_pshader);

      m_pshader->m_bDisableDepthTest = false;
      m_pshader->m_bDepthTestButNoDepthWrite = true;
      m_pshader->m_bLequalDepth = true;
      m_pshader->m_bEnableBlend = true;
      m_pshader->m_ecullmode = ::gpu::e_cull_mode_none;
      m_pshader->m_bindingCubeSampler.set();

      m_pshader->initialize_shader(pengine->gpu_context()->m_pgpurenderer,
         "matter://shaders/skybox.vert",
         "matter://shaders/skybox.frag",
         {::gpu::shader::e_descriptor_set_slot_global},
         nullptr,
         nullptr,
         pengine->gpu_context()->input_layout<::graphics3d::shape_factory::Vertex>()
      );
      
      initialize(pengine->gpu_context());
      
      SetupSkybox();

   }

   // Setup the skybox (VAO, VBO, EBO, and cubemap textures)
   void skybox_render_system::SetupSkybox() 
   {
      //// Generate buffers
      //glGenVertexArrays(1, &skyboxVAO);
      //glGenBuffers(1, &skyboxVBO);

      //glBindVertexArray(skyboxVAO);

      //glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
      ////glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);

      //// Set the vertex attribute pointer for the graphics3d vertexes
      //glEnableVertexAttribArray(0);
      //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);


      load_cube_map_images();

      // Load cubemap textures
      load_cube_map_textures();

      //glBindVertexArray(0);  // Unbind VAO
   }


   void skybox_render_system::load_cube_map_images()
   {

      m_sizeSquare.cx() = 0;
      m_sizeSquare.cy() = 0;

      for(auto & face : m_cube)
      {
         
         //         unsigned char* data = stbi_load(facesCubemap[i].c_str(), &width, &height, &nrChannels, 0);
               //   auto mem = file()->as_memory();
         auto pimage = image()->path_image(face.m_path.c_str());

         auto sizeSquare = pimage->size();
         //unsigned char* data = stbi_load_from_memory(
         //   (const stbi_uc*)mem.data(),
         //   mem.size(), &width, &height, &nrChannels, 0);
         if (sizeSquare.is_empty())
         {
            
            throw ::exception(error_wrong_state, "All images in skybox shouldn't be empty");

         }
         else if (sizeSquare.cx() != sizeSquare.cy())
         {

            throw ::exception(error_wrong_state, "All images in skybox should be a square");

         }

         if (m_sizeSquare.is_empty())
         {

            m_sizeSquare = sizeSquare;

         }
         else
         {

            if (m_sizeSquare != sizeSquare)
            {

               throw ::exception(error_wrong_state, "All images in skybox should be same size");

            }

         }

         face.m_pimage = pimage;

      }

      m_sizeSquare = m_cube.first().m_pimage->size();

   }


   // Load cubemap textures
   void skybox_render_system::load_cube_map_textures()
   {
      //glGenTextures(1, &cubemapTexture);
      //glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);

      //int w = 0;
      //int h = 0;
    
      //auto pimageCubeMap = image()->create_image({ m_sizeSquare.width() * 6, m_sizeSquare.height()});

      //pimageCubeMap->map();

      auto sizeItem = m_sizeSquare;

      //auto scanCubeMap = pimageCubeMap->m_iScan;

      ::int_point point;

      ::pointer_array < ::image::image > imagea;

      for(auto & face : m_cube)
      {

         auto pimage = face.m_pimage;

         imagea.add(pimage);

         //auto scan = pimage->m_iScan;

         //auto pimage32 = pimage->image32();

         //pimageCubeMap->image32()->copy(point, sizeItem, scanCubeMap, pimage32, scan);

         //point.x() += m_sizeSquare.width();

      }

      ødefer_construct(m_ptextureCubeMap);

      m_ptextureCubeMap->m_bTransferDst = true;

      m_ptextureCubeMap->initialize_image_texture(
         m_pmodelCube->m_pgpucontext->m_pgpurenderer,
         imagea, ::gpu::texture::e_type_cube_map);

      //m_pshader->set_int("skybox", 0);

      //int width, height, nrChannels;

      //   if (data) {
      //      // Load the texture data into the cubemap
      //      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
      //         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      //      stbi_image_free(data);
      //   }
      //   else if (data) {
      //      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
      //         0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
      //      stbi_image_free(data);
      //   }
      //   else {
      //      std::cout << "Failed to load cubemap texture at path: " << facesCubemap[i] << std::endl;
      //      stbi_image_free(data);
      //   }
      //}

      //// Set texture parameters for cubemap
      //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
   }


   void skybox_render_system::bind(::gpu::command_buffer* pgpucommandbuffer)
   {

      // Set uniforms in the shader
      auto iFrameSerial = m_pengine->gpu_context()->m_pgpudevice->m_iFrameSerial2;

      auto ptextureDst = m_pengine->gpu_context()->m_pgpurenderer->current_render_target_texture(::gpu::current_frame());
      
      m_pshader->m_bindingCubeSampler.m_strUniform = "skybox";

      m_pshader->bind(ptextureDst, m_ptextureCubeMap); // Make sure to bind the shader first
      //auto view = m_pengine->m_pcamera->getView();
      //glm::mat4 skyboxView = glm::mat4(glm::mat3(view)); // <-- drop translation
      //m_pshader->set_mat4("view", skyboxView);
      //auto projection = m_pengine->m_pcamera->getProjection();
      //m_pshader->set_mat4("projection", projection);
      //m_pshader->bind_source(m_ptextureCubeMap);
      m_pmodelCube->bind(pgpucommandbuffer);

   }


   void skybox_render_system::draw(::gpu::command_buffer* pgpucommandbuffer)
   {

      m_pmodelCube->draw(pgpucommandbuffer);

   }


   void skybox_render_system::unbind(::gpu::command_buffer* pgpucommandbuffer)
   {

      m_pmodelCube->unbind(pgpucommandbuffer);
      m_pshader->unbind();

   }


   void skybox_render_system::on_render(::gpu::context* pgpucontext, ::graphics3d::scene* pscene)
   {

      auto pcommandbuffer = pgpucontext->m_pgpurenderer->getCurrentCommandBuffer2(::gpu::current_frame());

      bind(pcommandbuffer);
      draw(pcommandbuffer);
      unbind(pcommandbuffer);

   }


} // namespace graphics3d



