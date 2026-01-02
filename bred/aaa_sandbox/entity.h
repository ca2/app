#pragma once
//#include "renderer_i.h"
//
//#include "SceneFoundry/graphics3d/transform_component.h"
//#include "SceneFoundry/graphics3d/camera_i.h"
namespace graphics3d
{

	class IEntity :
		virtual public ::particle
	{
	public:

		virtual void onInit() {};
		virtual void onUpdate(float dt) {};
		virtual void onRender(IFrame * pframe) {};
		virtual ::graphics3d::transform& getTransform() = 0;
		//virtual ~IEntity() = default;
	};


} // namespace graphics3d

