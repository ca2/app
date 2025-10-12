#pragma once
//#include "SceneFoundry/graphics3d/renderer_i.h"
//#include "SceneFoundry/graphics3d/scene_i.h"


namespace graphics3d
{

	class CLASS_DECL_BRED immersion_layer  :
		virtual public ::particle
	{
	public:


	   ::pointer < ::graphics3d::engine >                          m_pengine;
	   ::string_map_base < ::pointer < ::graphics3d::scene_base > >		m_mapScene;
	   ::pointer < ::graphics3d::scene_base >								   m_pscene;
	   ::pointer < ::graphics3d::camera >			                  m_pcamera;
	   ::pointer < ::graphics3d::asset_manager >			            m_passetmanager;


	   immersion_layer();
	   ~immersion_layer() override;


	   //virtual void initialize_immersion_layer(::graphics3d::engine * pengine, ::graphics3d::asset_manager * passetmanager);

      virtual void initialize_immersion_layer(::graphics3d::engine *pengine);

	   virtual void on_initialize_immersion_layer();

	   virtual void add_scene(::graphics3d::scene_base* pscene);

	   virtual void set_current_scene(::graphics3d::scene_base* pscene);

      virtual ::graphics3d::camera *camera();

      virtual ::graphics3d::asset_manager *asset_manager();

		virtual ::pointer < ::graphics3d::scene_base > create_main_scene();
		// virtual void onUpdate(float deltaTime);
		// virtual void on_render(::gpu::frame & frame);
		//virtual IScene& getSceneInterface() = 0;
		//virtual ~IGameLayer() = default;


      virtual void load_camera(const ::property_set &set);
      virtual void on_initial_camera_load();


      virtual void on_pre_update_camera();


	};


} // namespace graphics3d

