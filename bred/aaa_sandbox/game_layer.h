#pragma once
//#include "SceneFoundry/graphics3d/renderer_i.h"
//#include "SceneFoundry/graphics3d/scene_i.h"


namespace graphics3d
{

	class IGameLayer  :
		virtual public ::particle
	{
	public:


		virtual void onInit() = 0;
		virtual void onUpdate(float deltaTime) = 0;
		virtual void on_render(::gpu::frame & frame) {};
		virtual IScene& getSceneInterface() = 0;
		//virtual ~IGameLayer() = default;


	};


} // namespace graphics3d

