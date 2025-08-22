#pragma once
//#include "SceneFoundry/graphics3d/renderer_i.h"
//#include "SceneFoundry/graphics3d/scene_i.h"


namespace graphics3d
{

	class game_layer  :
		virtual public ::particle
	{
	public:


	   ::string_map_base < ::pointer < ::graphics3d::scene > >		m_mapScene;
	   ::pointer < ::graphics3d::scene >								m_pscene;
	   ::pointer < ::graphics3d::camera >			m_pcamera;



		// virtual void onInit();
		// virtual void onUpdate(float deltaTime);
		// virtual void on_render(::gpu::frame & frame);
		//virtual IScene& getSceneInterface() = 0;
		//virtual ~IGameLayer() = default;


	};


} // namespace graphics3d

