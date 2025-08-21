#pragma once


#include "bred/user/user/graphics3d.h"


namespace sandbox_renderer
{



//#define MAX_LIGHTS 10
   struct IGameObject;
   struct IScene;

   struct point_light {
      inline static const int MAX_LIGHTS=10;
      glm::vec4 position{};
      glm::vec4 color{};
   };

   struct global_ubo {
      glm::mat4 projection{ 1.f };
      glm::mat4 view{ 1.f };
      glm::vec4 ambientLightColor{ 1.f,1.f,1.f,0.02f };
      glm::vec4 viewPos{ 0.f };
      point_light pointLights[point_light::MAX_LIGHTS];
      alignas(4) int numLights = 0;
      // pad up to 16‑byte multiple:
      alignas(16) int _pad[3]{};
   };

   //struct PointLight
   //   glm::vec4 position{};  // ignore w
   // glm::vec4 color{};     // w is intensity

//BEGIN_GPU_PROPERTIES(point_light)
//GPU_PROPERTY("position", ::gpu::e_type_seq4)
//GPU_PROPERTY("color", ::gpu::e_type_seq4)
//END_GPU_PROPERTIES()

//GPU_PROPERTY("radius", ::gpu::e_type_float)

   // GlobalUbo :
   // glm::mat4 projection{ 1.f };
   // glm::mat4 view{ 1.f };
   // glm::mat4 invView{ 1.f };
   // glm::vec4 ambientLightColor{ 1.f, 1.f, 1.f, .02f };
   // PointLight pointLights[MAX_LIGHTS];
   // int numLights;
   // 3XINT PADDING


} // namespace sandbox_renderer


