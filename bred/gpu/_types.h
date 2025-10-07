/// Created by camilo on 2025-08-23 <3ThomasBorregaardSorensen!!
#pragma once



namespace gpu
{



	struct point_light
	{

		glm::vec4 position{};  // ignore w
		glm::vec4 color{};     // w is intensity

	};


   struct point_light_push_constants
   {

      glm::vec4 position{}; // ignore w
      glm::vec4 color{}; // w is intensity
      float radius;
   };



} // namespace gpu



