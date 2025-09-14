#pragma once

//#include <glad/glad.h>
//#include <string>
//#include <vector>
#include "acme/prototype/collection/static_array.h"
#include "bred/graphics3d/model.h"
//#include "bred/graphics3d/render_system.h"
#include "bred/graphics3d/shape_factory.h"
#include "bred/graphics3d/scene_object.h"
#include "bred/graphics3d/types.h"


namespace graphics3d
{


   class CLASS_DECL_BRED skybox :
   virtual public ::graphics3d::scene_object
   
   {
   public:

      using Vertex = ::graphics3d::shape_factory::Vertex;

      struct cube_face
      {

         ::file::path               m_path;
         ::image::image_pointer     m_pimage;


         cube_face() {}
         cube_face(const ::file::path& path) :
            m_path(path)
         {


         }

      };


      struct cube :
         public ::block_array < cube_face, 6 >
      {
      public:

         cube()
         {

         }
         cube(::std::initializer_list < ::file::path > list)
         {

            int i = 0;

            for (auto& item : list)
            {

               this->element_at(i).m_path = item;

               i++;

            }

         }

      };
      //::particle* pparticle, const ::string_array_base& faces

      //::pointer < engine >                m_pengine;
      ::pointer < ::graphics3d::renderable >          m_pmodelCube;
      ::pointer < ::gpu::texture >                    m_ptexture;
      ::int_size                                      m_sizeSquare;
      ::string                                        m_strTexture;
      //::string                                        m_strModel;
      //::string                                        m_strObject;

      cube                                m_cube;
      //::pointer<::gpu::shader>            m_pshader;

      ::string          m_strCubemapTextureName;

      skybox();
      ~skybox();


      virtual void initialize_sky_box(::graphics3d::scene * pscene, const ::scoped_string & scopedstrName);

      virtual void SetupSkybox();

      virtual void load_cube_map_images();
      virtual void load_cube_map_textures();

      virtual void bind(::gpu::command_buffer* pgpucommandbuffer);
      virtual void draw(::gpu::command_buffer* pgpucommandbuffer);
      virtual void unbind(::gpu::command_buffer* pgpucommandbuffer);

      //void draw(::gpu::context* pgpucontext, ::graphics3d::scene* pscene) override;

      //void draw(::gpu::command_buffer * pcommandbuffer) override;



   //private:




      //unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
      //unsigned int cubemapTexture;
      //::string_array_base facesCubemap;

      
   };



} // namespace graphics3d_opengl



