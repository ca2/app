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

		camera();
		~camera() override;


      virtual ::block as_block();


	};


} // namespace graphics3d



