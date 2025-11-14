#include "framework.h"
#include "SceneFoundry/sandbox_game/player.h"
#include <glm/gtc/matrix_transform.hpp>
//#include "SceneFoundry/graphics3d/key_codes.h"
////#include <spdlog/spdlog.h>


namespace sandbox_game
{


   // player::player(::pointer<::graphics3d::IWindowInput> input)
   //    : m_pInput(std::move(input))
   //    , m_camera(floating_sequence3(0.f, 0.f, 3.f))
   // {
   // }
   player::player()
   {
   }


   void player::onInit()
   {

   }


   void player::on_update(float dt)
   {
      if (!m_pInput)
         return;

      try
      {
         double dx = 0, dy = 0;
         m_pInput->getMouseDelta(dx, dy);
         m_controller.mouseCallback(floating_sequence2(dx, dy));
         m_controller.update(dt, m_pInput, m_transform);

         m_camera.setPosition(m_transform.translation);
         m_camera.setRotation(m_transform.rotation);

         int w, h;
         m_pInput->getFramebufferSize(w, h);
         float aspect = h == 0 ? 1.0f : static_cast<float>(w) / h;
         m_camera.updateProjection(aspect, 0.1f, 300.f);
      }
      catch (const ::exception &e)
      {
         error("Exception in player::onUpdate(): {}", e.get_message());
      }
      catch (...)
      {
         error("Unknown exception in player::onUpdate()");
      }
   }


   ::graphics3d::transform &player::transform()
   {
      return m_transform;
   }


   ::graphics3d::IModel *player::model()
   {
      return nullptr;
   }


   camera &player::getCamera()
   {
      return m_camera;
   }


} // namespace sandbox_game
