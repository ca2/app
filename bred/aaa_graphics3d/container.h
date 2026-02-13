// From vk_window by camilo on 2025-05-09 02:32 <3ThomasBorregaardSorensen!!
#pragma once


namespace user
{


	enum enum_key_state
	{

		e_key_state_none,
		e_key_state_pressed = 1,

	};


} // namespace user


namespace graphics3d
{


	/** @brief State of mouse/touch input */
	struct mouse_state
	{
		struct 
		{
			
			bool left = false;
			bool right = false;
			bool middle = false;

		} m_buttons;

		::floating_sequence2 m_position;
	};

	
	class CLASS_DECL_BRED container :
		virtual public ::particle
	{
	public:


		::function < void(void*, int, int, int)> m_callbackOffscreen;

		double   m_dCursorX;
		double   m_dCursorY;
		bool		m_bFirstMouse;
		bool		m_bLastMouse;


		bool		m_bShouldClose;
		int		m_iWidth;
		int		m_iHeight;
		bool		m_bFrameBufferResized;

		
		container();
		~container() override;
		

		virtual bool is_absolute_mouse_position();

		virtual bool shouldClose();
		virtual ::int_size size();
		virtual bool wasWindowResized();
		virtual void resetWindowResizedFlag();

		virtual ::user::enum_key_state get_key_state(::user::e_key ekey);

		virtual void initWindow();



	};


} // namespace graphics3d



