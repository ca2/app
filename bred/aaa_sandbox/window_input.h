#pragma once
//#include "SceneFoundry/graphics3d/key_codes.h"
//#include <functional>



namespace graphics3d
{


	using SandboxKeyCallback = ::function<void(SandboxKey key, int scancode, KeyAction action, int mods)>;


	class IWindowInput :
		virtual public ::particle
	{
	public:
		//virtual ~IWindowInput() = default;

		virtual void lockCursor(bool lock) = 0;
		virtual void setCursorCallback(void (*callback)(double, double)) = 0;
		virtual void getFramebufferSize(int& width, int& height) const = 0;
		virtual void getMouseDelta(double& dx, double& dy) = 0;
		virtual bool isKeyPressed(SandboxKey key) const = 0;
		virtual bool isMouseButtonPressed(int button) const = 0;
		virtual void setUserPointer(void* ptr) = 0;
		virtual void setKeyCallback(SandboxKeyCallback callback) = 0;
		virtual bool isWindowShouldClose() const = 0;
		virtual void requestWindowClose() = 0;
		virtual void pollEvents() = 0;

	};


} // namespace graphics3d
