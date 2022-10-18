// Created by camilo on 2021-01-22 06:11 AM <3ThomasBorregaardSørensen
#pragma once


namespace user
{


   class drag_client;
   class mouse;


   class CLASS_DECL_ACME drag :
      virtual public ::element
   {
   public:



      ::e_element                m_eelement;
      bool                       m_bLButtonDown;
      ::point_i32                m_pointLButtonDown;
      ::size_i32                 m_sizeLButtonDownOffset;
      ::pointer<::user::mouse>   m_pmouse;
      enum_cursor                m_ecursor;

      bool                       m_bDrag;

      
      drag();
      ~drag() override;


      void start(::user::mouse * pmouse, const ::point_i32 & pointDrag);
      void end();


      ::point_i32 point() const;


   };


   class CLASS_DECL_ACME drag_client :
      virtual public ::object
   {
   public:


      map < e_element, ::pointer<::user::drag >>     m_mapDrag;
      ::pointer<::user::drag>                        m_pdragCurrent;


      drag_client();
      ~drag_client() override;


      void destroy() override;


      virtual void enable_drag(::e_element eelement);
      virtual ::user::drag * drag(::e_element eelement) const;
      virtual bool has_drag(::e_element eelement) const;


      virtual bool drag_on_button_down(::item * pitemButtonDown);
      virtual void drag_on_button_down(::user::drag * pdrag, ::user::mouse * pmouse);
      virtual bool drag_on_mouse_move(::user::mouse * pmouse);
      virtual bool drag_on_mouse_hover(::item * pitemButtonHover);
      virtual bool drag_on_button_up(::user::mouse * pmouse);


      virtual void drag_set_capture() = 0;
      virtual ::point_i32 on_drag_start(::user::drag * pdrag) = 0;
      virtual bool drag_shift(::user::drag * pdrag) = 0;
      virtual bool drag_hover(::user::drag * pdrag) = 0;
      virtual void drag_release_capture() = 0;
      virtual void drag_set_cursor(::user::drag * pdrag) = 0;


   };


} // namespace user



