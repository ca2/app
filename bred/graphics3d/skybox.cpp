#include "framework.h"
#include "immersion_layer.h"
#include "scene_base.h"
#include "skybox.h"
#include "engine.h"
#include "bred/gpu/device.h"
#include "bred/gpu/frame.h"
#include "bred/gpu/render_target.h"
#include "bred/gpu/texture.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "aura/graphics/image/context.h"
#include "aura/platform/application.h"
#include <stb/stb_image.h>
#include <iostream>

#include "gpu/command_buffer.h"


namespace graphics3d
{


   skybox::skybox()
   {


   }


   // Destructor
   skybox::~skybox() 
   {


   }


   void skybox::initialize_sky_box(::graphics3d::scene_base * pscene, const ::scoped_string & scopedstrName)
   {

      ::graphics3d::scene_object::initialize_scene_object(pscene);

      cube cube;

      cube.add(::file::path("matter://textures") / scopedstrName / "right.png");
      cube.add(::file::path("matter://textures") / scopedstrName / "left.png");
      cube.add(::file::path("matter://textures") / scopedstrName / "top.png");
      cube.add(::file::path("matter://textures") / scopedstrName / "bottom.png");
      cube.add(::file::path("matter://textures") / scopedstrName / "front.png");
      cube.add(::file::path("matter://textures") / scopedstrName / "back.png");

      m_cube = cube;

      //m_pengine = pengine;


      //auto modeldataCube = ::graphics3d::shape_factory::create_cube(32.0f);

      ////øconstruct(m_pmodelCube);

      //auto pmodelCube = øcreate<::gpu::model_buffer>();

      //pmodelCube->initialize_model(pscene->m_pimmersionlayer->m_pengine->
      //   gpu_context(), modeldataCube);

      ////m_pmodelCube = pmodelCube;

      //m_prenderable = pmodelCube;

      //m_prenderable->m_ecoordinatesystem = ::gpu::e_coordinate_system_opengl;

      //m_pmodelCube->initialize_model();
      
      initialize(pscene->m_pimmersionlayer->m_pengine->gpu_context());
      
      SetupSkybox();

   }

   // Setup the skybox (VAO, VBO, EBO, and cubemap textures)
   void skybox::SetupSkybox() 
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


   void skybox::load_cube_map_images()
   {

      m_sizeSquare.cx = 0;
      m_sizeSquare.cy = 0;

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
         else if (sizeSquare.cx != sizeSquare.cy)
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
   void skybox::load_cube_map_textures()
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

         //point.x += m_sizeSquare.width();

      }

      ødefer_construct(m_ptexture);

      ::gpu::texture_attributes textureattributes(::int_rectangle{sizeItem},8, 4, 0,
         ::gpu::e_texture_cube_map,  6);

      ::gpu::texture_flags textureflags;

      textureflags.m_bTransferTarget = true;

      ::gpu::texture_data texturedata(imagea);

      auto prenderer = m_pscene->m_pimmersionlayer->m_pengine->gpu_context()->m_pgpurenderer;

      m_ptexture->initialize_texture(prenderer, textureattributes, textureflags, texturedata);

   }


   void skybox::bind(::gpu::command_buffer* pgpucommandbuffer)
   {

      m_prenderable->bind2(pgpucommandbuffer);

   }


   void skybox::draw(::gpu::command_buffer* pgpucommandbuffer)
   {

      m_prenderable->draw2(pgpucommandbuffer);

   }


   void skybox::unbind(::gpu::command_buffer* pgpucommandbuffer)
   {

      m_prenderable->unbind(pgpucommandbuffer);

   }


} // namespace graphics3d



