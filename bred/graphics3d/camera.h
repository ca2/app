// From V0idsEmbrace@Twich continuum project
// by camilo on 2025-05-17 20:12 <3ThomasBorregaardSorensen!!
#pragma once 


#include "bred/graphics3d/types.h"


namespace graphics3d
{


	
	class CLASS_DECL_BRED camera :
		virtual public ::particle
	{
	public:


		::pointer < ::graphics3d::engine > m_pengine;
      ::glm::vec3 m_vec3Position;
      ::glm::vec3 m_vec3Rotation;



		camera();
		~camera() override;


      virtual glm::vec3 position();
      virtual glm::vec3 rotation();

      inline auto &yaw() { return m_vec3Rotation.y; }
      inline auto &pitch() { return m_vec3Rotation.x; }

      virtual ::block as_block();


	};


} // namespace graphics3d



