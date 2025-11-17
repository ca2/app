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
      ::floating_sequence3 m_sequence3Position;
      ::floating_sequence3 m_sequence3Rotation;



		camera();
		~camera() override;


      virtual floating_sequence3 position();
      virtual floating_sequence3 rotation();

      inline auto &yaw() { return m_sequence3Rotation.y; }
      inline auto &pitch() { return m_sequence3Rotation.x; }

      virtual ::block as_block();


	};


} // namespace graphics3d



