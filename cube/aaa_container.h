// From vk_window by camilo on 2025-05-09 02:32 <3ThomasBorregaardSorensen!!
#pragma once


#include <glm/glm.hpp>


namespace user
{


	enum enum_key_state
	{

		e_key_state_none,
		e_key_state_pressed = 1,

	};


} // namespace user


namespace cube
{


	
	class CLASS_DECL_CUBE container :
		virtual public ::particle
	{
	public:


		container();
		~container() override;
		


	};


} // namespace cube



