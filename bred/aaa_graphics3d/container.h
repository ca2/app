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


		::function < void(void*, ::i32, ::i32, ::i32)> m_callbackOffscreen;

		::f64   m_dCursorX;
		::f64   m_dCursorY;
		bool		m_bFirstMouse;
		bool		m_bLastMouse;


		bool		m_bShouldClose;
		::i32		m_iWidth;
		::i32		m_iHeight;
		bool		m_bFramebufferResized;

		
		container();
		~container() override;
		

		virtual bool is_absolute_mouse_position();

		virtual bool shouldClose();
		virtual ::i32_size size();
		virtual bool wasWindowResized();
		virtual void resetWindowResizedFlag();

		virtual ::user::enum_key_state get_key_state(const ::user::e_key & ekey);

		virtual void initWindow();



	};


} // namespace graphics3d



