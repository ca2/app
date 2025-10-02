#include "framework.h"
#include "actor.h"
#include <glm/gtc/matrix_transform.hpp>
//#include "SceneFoundry/graphics3d/key_codes.h"
////#include <spdlog/spdlog.h>


namespace prodevian
{


   // actor::actor(::pointer<::graphics3d::IWindowInput> input)
   //    : m_pInput(std::move(input))
   //    , m_camera(glm::vec3(0.f, 0.f, 3.f))
   // {
   // }
   actor::actor()
   {
   }


   void actor::initialize_prodevian_actor(graphics3d::scene_base *pscene)
   {



   }


   void actor::on_initialize_actor()
   {


   }


   void actor::on_update(float dt)
   {

      // if (!m_pInput)
      // {
      //
      //    return;
      //
      // }

      // try
      // {
      //    double dx = 0, dy = 0;
      //    m_pInput->getMouseDelta(dx, dy);
      //    m_controller.mouseCallback(glm::vec2(dx, dy));
      //    m_controller.update(dt, m_pInput, m_transform);
      //
      //    m_camera.setPosition(m_transform.translation);
      //    m_camera.setRotation(m_transform.rotation);
      //
      //    int w, h;
      //    m_pInput->getFramebufferSize(w, h);
      //    float aspect = h == 0 ? 1.0f : static_cast<float>(w) / h;
      //    m_camera.updateProjection(aspect, 0.1f, 300.f);
      // }
      // catch (const ::exception &e)
      // {
      //    error("Exception in actor::onUpdate(): {}", e.get_message());
      // }
      // catch (...)
      // {
      //    error("Unknown exception in actor::onUpdate()");
      // }
   }


   // ::graphics3d::transform &actor::transform()
   // {
   //    return m_transform;
   // }
   //
   //
   // ::graphics3d::IModel *actor::model()
   // {
   //    return nullptr;
   // }

   //
   // ::graphics3d::camera * actor::getCamera()
   // {
   //    return m_pcamera;
   // }


} // namespace prodevian



