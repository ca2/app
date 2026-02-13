#pragma once


#include "bred/gpu/context_object.h"
#include "bred/gpu/properties.h"
//#include "bred/graphics3d/window_input.h"
//#include "bred/graphics3d/entity.h"
//#include "bred/prodevian/actor.h"
//#include "bred/graphics3d/asset_manager.h"
//#include "bred/prodevian/game_object.h"
//#include <memory>
//#include <vector>
//////#include <stdexcept>
//#include <fstream>
//#include <optional>


namespace graphics3d
{


	class CLASS_DECL_BRED scene_base :
		virtual public ::gpu::context_object
	{
	public:


	   ::string                                                    m_strSceneName;

	   bool                                                        m_bInitialized;
	   bool                                                        m_bLoadedScene;
	   ::interlocked_count                                         m_interlockedcountSceneObject;
      ::pointer < ::graphics3d::immersion_layer >                 m_pimmersionlayer;
		//::pointer<::graphics3d::IWindowInput>							      m_pwindowinput;
		//::pointer < ::graphics3d::asset_manager >				         m_passetmanager;
      ::pointer < ::graphics3d::camera >                          m_pcameraCurrent;
	   ::pointer < ::graphics3d::camera >                          m_pcameraDefault;
	   ::pointer < ::graphics3d::camera >                          m_pcameraScene;
      ::pointer_array_base<::prodevian::actor>				         m_prodevianactora;
	   ::pointer_array_base<::graphics3d::point_light>				   m_pointlighta;
		::graphics3d::scene_renderable_map                         	m_mapSceneRenderable;
      ::graphics3d::skybox_map                                    m_mapSkybox;
      //::graphics3d::skybox_map                                    m_mapSkybox;
      ::string                                                    m_strSkybox;
      ::pointer<::graphics3d::renderable>                         m_prenderableSkyboxModel;
      ::pointer<::graphics3d::skybox>                             m_pskyboxCurrent2;
      //::string                                                    m_strSkyboxTexture;

      bool m_bInitialCameraLoaded = false;
		//floating_sequence3													            m_initialCameraPosition{ 0.f };
		//floating_sequence3													            m_initialCameraRotation{ 0.f };

		//::string														            m_strSkyboxModelName;
      //::string m_strSkyboxTextureName = "skybox_hdr";
      //::string m_strSkyboxModelName;
      //::string m_strSkyboxTextureName;
		//::pointer<::graphics3d::skybox>							         m_pskyboxCurrent;
	   //string_map < ::pointer < ::graphics3d::skybox > >           m_mapSkybox;
		//::string													               m_strSkybox;
      //::pointer < ::graphics3d::skybox >                          m_pskyboxCurrent;
      //::gpu::properties                                           m_gpupropertiesGlobalUbo;
      ::pointer<::gpu::block> m_pblockGlobalUbo;


		scene_base();
		~scene_base() override;


		// pass input so your Player can read it
		//void initialize_scene(::graphics3d::IWindowInput * input, ::graphics3d::IAssetProvider * passetmanager) override;

	   virtual void initialize_scene(::graphics3d::immersion_layer * pimmersionlayer);


		virtual void on_initialize_scene();                 // load models, spawn entities
		virtual void update(float dt);        // advance all entities
      virtual void loadSceneFile(const ::scoped_string &fileName);


      virtual void load_scene_renderable(const ::property_set &setObject);
      virtual void load_lights(const ::property_set &objJson);
      virtual void load_scene_light(const ::payload &payload);

      virtual bool is_global_ubo_ok();

	   //virtual ::gpu::block * global_ubo();

      virtual ::gpu::block * global_ubo1(::gpu::context *pgpucontext);



	   virtual ::graphics3d::scene_renderable & scene_renderable(const ::scoped_string & scopedstr, bool bCounterClockwise = true, const ::file::path & path = {});

	   virtual ::pointer < ::graphics3d::scene_renderable > _scene_renderable(const ::scoped_string & scopedstr, bool bCounterClockwise, const ::file::path & path);

		virtual ::graphics3d::scene_renderable_map & scene_renderables();

		//virtual ::pair<floating_matrix4, floating_matrix4> getMainCameraMatrices()const;

      //virtual ::pointer<::graphics3d::renderable> get_cube_model();
      //virtual ::pointer<::graphics3d::renderable> get_skybox_cube_model();
      //virtual ::pointer<::graphics3d::renderable> get_skybox_cube_model();
      //virtual ::pointer<::gpu::texture> get_skybox_cube_texture();

		virtual void set_skybox(::graphics3d::skybox * pskybox);
      virtual ::graphics3d::skybox *current_skybox();

		virtual class camera *camera();
      virtual class camera *scene_camera();

	   virtual void set_default_camera(::graphics3d::camera * pgpucamera);
	   virtual ::graphics3d::camera * get_default_camera();


		//virtual void addGameObject(uint32_t id, ::graphics3d::scene_object * obj);
		//virtual void removeGameObject(uint32_t id);

		//virtual ::graphics3d::skybox * current_sky_box();

		//::graphics3d::sandbox_game_object>>
		//	getSkyboxObject();

		//::string getSkyboxCubemapName();

	   ::pointer < ::graphics3d::renderable > create_tinyobj_renderable(const ::file::path& path);

	   ::pointer<::graphics3d::scene_renderable> create_scene_renderable();


	   virtual ::pointer<::graphics3d::skybox> create_sky_box();


		::pointer<::graphics3d::point_light> create_point_light(
		   float intensity = 10.f,
		   float radius = 0.1f,
		   const ::color::color & color = ::color::white);


	   virtual void defer_load_scene(::gpu::context* pgpucontext);


	   virtual void on_load_scene(::gpu::context* pgpucontext);
	   virtual void on_update(::gpu::context* pgpucontext);
	   virtual void on_render(::gpu::context * pgpucontext);

      virtual void generateIbl();

      virtual void generateIblBRDFlut();
      virtual void generateIblIrradianceMap();
      virtual void generateIblPrefilteredEnvMap();


//      /// @brief generatePrefilteredEnvMap
//      /// @param environmentCubeExisting
//      /// @param prenderableSkybox
//      /// @return
//      virtual ::pointer<::gpu::texture> generatePrefilteredEnvMap(
//         ::gpu::texture *environmentCubeExisting,
//         ::graphics3d::renderable *prenderableSkybox);
//      
//      /// generate irradianceCube
//      /// @return irradianceCube
//      virtual ::pointer < ::gpu::texture > generateIrradianceMap(
////         ::gpu::texture * irradianceCube,
//         ::gpu::texture * environmentCube,
//         ::graphics3d::renderable * prenderableSkybox);
//      // ::pointer<::gpu::texture> loadCubemap(
//      //    const ::scoped_string& name,
//      //    const ::scoped_string& ktxFilename,
//      //    VkFormat format,
//      //    VkImageUsageFlags usageFlags,
//      //    VkImageLayout initialLayout);
//      //    virtual void generateBRDFlut(
//      //     ::gpu::texture * lutBrdf);
//      /// generate lutBrdf
//      /// @return lutBrdf
//      virtual ::pointer < ::gpu::texture > generateBRDFlut();


	   //virtual ::pointer < ::graphics3d::renderable> create_tinyobj_scene_object(const ::file::path& path);


	   //virtual ::graphics3d::wavefront_obj_render_system * wavefront_obj_render_system();


	};


} // namespace graphics3d



