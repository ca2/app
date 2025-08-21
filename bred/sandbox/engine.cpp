#include "../../../SceneFoundry/sandbox_engine/framework.h"
#include "engine.h"
#include "SceneFoundry/sandbox/key_codes.h"
//#include "spdlog/spdlog.h"
#include "SceneFoundry/sandbox/frame_info.h"
#include <thread>
#include <chrono>

//#include <cassert>

namespace sandbox_engine
{


	sandbox_engine::sandbox_engine() {
		m_assetManager.preloadGlobalAssets();
		initialize();
	}
	void sandbox_engine::initialize() {
		m_windowInput = øcreate_pointer<GLFWWindowInput>(m_window.getGLFWwindow());
		if (auto* userData = static_cast<WindowUserData*>(glfwGetWindowUserPointer(m_window.getGLFWwindow()))) {
			userData->input = m_windowInput.get();
		}
		m_windowInput->lockCursor(m_cursorLocked);
		setupInputCallbacks();
		information("Engine initialized");
	}
	void sandbox_engine::initLayer(IGameLayer* game) {


		game->onInit();

		m_renderer.initializeSystems(m_assetManager);
		information("Game initialized");
	}

	void sandbox_engine::run(::pointer<IGameLayer> game) {
		using clock = std::chrono::high_resolution_clock;
		using duration_t = std::chrono::duration<double>;

		constexpr double TARGET_FPS = 60.0;
		constexpr double TARGET_FRAME_TIME = 1.0 / TARGET_FPS;

		auto lastTime = clock::now();

		IScene& scene = game->getSceneInterface();
		ICamera& cam = scene.getCamera();


		while (!glfwWindowShouldClose(m_window.getGLFWwindow())) {
			// Poll events / process input
			m_windowInput->pollEvents();
			processInput();

			// Compute delta time
			auto now = clock::now();
			double deltaTime = duration_t(now - lastTime).count();
			lastTime = now;

			// Begin recording command buffer
			ISandboxRenderer::FrameContext frame = m_renderer.beginFrame();
			if (!frame.isValid()) break;

			int idx = m_renderer.getFrameIndex();

			FrameInfo info{
			 idx,
			 static_cast<float>(deltaTime),
			 frame.primaryGraphicsCommandBuffer,
			 cam,
			 m_renderer.getGlobalDescriptorSet()[idx],
			 scene.getGameObjects(),
			 scene
			};

			// Update game and subsystems 
			game->onUpdate(static_cast<float>(deltaTime));

			GlobalUbo ubo{};
			ubo.projection = cam.getProjectionMatrix();
			ubo.view = cam.getViewMatrix();
			ubo.viewPos = glm::vec4(cam.getPosition(), 1.0f);

			m_renderer.updateSystems(info, ubo, static_cast<float>(deltaTime));

			auto& uboBuffer = m_renderer.getUboBuffers()[idx];
			uboBuffer->writeToBuffer(&ubo);
			uboBuffer->flush();

			// Render Game
			m_renderer.beginSwapChainRenderPass(frame);
			m_renderer.renderSystems(info);
			m_renderer.endSwapChainRenderPass(frame);
			m_renderer.endFrame(frame);

			// Frame cap sleep
			auto frameEnd = clock::now();
			double frameTime = duration_t(frameEnd - now).count();
			if (frameTime < TARGET_FRAME_TIME) {
				auto sleepDuration = std::chrono::duration<double>(TARGET_FRAME_TIME - frameTime);
				std::this_thread::sleep_for(sleepDuration);
			}
		}
		m_renderer.waitDeviceIdle();

	}

	void sandbox_engine::toggleCursorLock() {
		m_cursorLocked = !m_cursorLocked;
		m_windowInput->lockCursor(m_cursorLocked);
	}

	void sandbox_engine::setupInputCallbacks() {
		m_windowInput->setKeyCallback([this](SandboxKey key, int scancode, KeyAction action, int mods) {
			if (key == SandboxKey::LEFT_ALT && action == KeyAction::PRESS) {
				toggleCursorLock();
			}
			});
	}

	void sandbox_engine::processInput() {

		if (m_windowInput && m_windowInput->isKeyPressed(SandboxKey::ESCAPE)) {
			m_windowInput->requestWindowClose();
		}
	}



} // namespace sandbox_engine


