#pragma once


#include "acme/user/user/mouse.h"
//#include "acme/prototype/geometry2d/_geometry2d.h"
#include "acme/prototype/geometry2d/size.h"

//#include "acme/prototype/prototype/pointer.h"
#include "apex/user/user/message.h"
//#include "aura/user/user/message.h"
#include "aura/user/user/key.h"


namespace message
{


   
   class CLASS_DECL_AURA create :
      public ::user::message
   {
   public:


      //::pointer<::user::system>      m_pusersystem;


      create();


      //virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam) override;

      //virtual void error(const ::string & pcszErrorMessage);

      virtual void failed(const ::string & pcszErrorMessage);

//      ::request * get_request();
//
//      ::user::system * get_user_system();
//
//      ::particle * get_impact_data();


   };


   class CLASS_DECL_AURA activate : public ::user::message
   {
   public:


      ::enum_activate   m_eactivate;
      ::user::interaction * m_pWndOther;
      bool  m_bMinimized;


      activate();

      //// using ::user::message::set;

      //virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam) override;

      inline bool is_active() const
      {

         return m_eactivate == e_activate_active || m_eactivate == e_activate_click_active;

      }

      inline bool inactive() const
      {

         return m_eactivate == e_activate_inactive;

      }


   };

   class CLASS_DECL_AURA reposition : public ::user::message
   {
   public:


      point_i32 m_point;

      reposition() { }

      //// using ::user::message::set;

      //virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam) override;


   };


   class CLASS_DECL_AURA size : public ::user::message
   {
   public:


      ::u32          m_nType;
      ::size_i32     m_size;

      size() { }

      // using ::user::message::set;

      //virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam) override;

   };


   class CLASS_DECL_AURA scroll : public ::user::message
   {
   public:


      enum_scroll_command    m_ecommand;
      f64                    m_dPosition;
#ifdef WINDOWS_DESKTOP
      ::oswindow              m_oswindowScrollBar;
#endif
      //::user::interaction_base * m_pscrollbar;


      scroll();
      ~scroll() override;

      // using ::user::message::set;

      //virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam) override;


   };

   
   class CLASS_DECL_AURA mouse_base :
      virtual public ::user::message,
      virtual public ::user::mouse
   {
   public:


      mouse_base & operator = (const mouse_base & mousebase);


   };


   class CLASS_DECL_AURA mouse :
      virtual public mouse_base
   {
   public:

      
      mouse();
      ~mouse() override;


      // using ::user::message::set;

      //virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam) override;

      static mouse * cast(::message::message * pmessage)
      {
         return dynamic_cast <mouse *> (pmessage);
      }

      virtual unsigned int get_message() override
      {
         return (unsigned int)m_atom.as_i64();
      }


      mouse & operator = (const mouse & mouse);


   };


   class CLASS_DECL_AURA mouse_wheel :
      public mouse
   {
   public:

      i16 m_Δ;

      mouse_wheel();

      ::u32 GetFlags();

      //i16 GetDelta();

      point_i32 GetPoint();

      // using ::user::message::set;

      //virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam) override;

   };


   class CLASS_DECL_AURA set_cursor :
      virtual public ::user::message
   {
   public:


      ::user::interaction_base *                 m_pWnd;
      ::u32                               m_nHitTest;
      ::u32                               m_message;
      


      set_cursor();
      virtual ~set_cursor();


      //virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam) override;


   };


   class CLASS_DECL_AURA mouse_activate : public ::user::message
   {
   public:


      mouse_activate();

      ::user::interaction * get_desktop_window();

      ::u32 GetHitTest();

      ::u32 get_message();

   };


   class CLASS_DECL_AURA context_menu : public ::user::message
   {
   public:


      context_menu();

      point_i32 GetPoint();


   };



   class CLASS_DECL_AURA show_window : public ::user::message
   {
   public:


      bool m_bShow;
      ::u32  m_nStatus;


      show_window() { }

      // using ::user::message::set;

      //virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam) override;


   };


   class CLASS_DECL_AURA kill_keyboard_focus : public ::user::message
   {
   public:


      oswindow       m_oswindowNew;

      kill_keyboard_focus() { }

      // using ::user::message::set;

      //virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam) override;


   };


   class CLASS_DECL_AURA on_draw : public ::user::message
   {
   public:

      ::draw2d::graphics * m_pdc;

      on_draw() { }


   };


   class CLASS_DECL_AURA erase_bkgnd : public ::user::message
   {
   public:


      ::draw2d::graphics * m_pdc;


      erase_bkgnd();

      void set_result(bool bResult);


   };


   // e_message_paint -> aura
   // e_message_mouse_leave -> aura


   class CLASS_DECL_AURA nc_hit_test : public ::user::message
   {
   public:


      point_i32 m_point;

      nc_hit_test() { }

      //virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam) override;

      void set_hit_test(enum_hit_test ehittest) { m_lresult = ehittest; }

   };


   class CLASS_DECL_AURA key :
      public ::user::key
   {
   public:


      key();
      ~key() override;

      // using ::user::message::set;

      //virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam) override;

   };


   class CLASS_DECL_AURA nc_activate : public ::user::message
   {
   public:


      bool m_bActive;


      nc_activate();

      // using ::user::message::set;
      //virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam) override;

   };


   class CLASS_DECL_AURA notify : public ::user::message
   {
   public:


      notify() { }


      i32 get_ctrl_id();


   };


   class CLASS_DECL_AURA particle : public ::user::message
   {
   public:


      ::particle_pointer      m_pparticle;


      particle();
      ~particle() override;


      //virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam) override;


   };


   class CLASS_DECL_AURA ctl_color : public ::user::message
   {
   public:


      void * m_hbrush;
      ::draw2d::graphics * m_pdc;
      ::u32                      m_nCtlType;

      ctl_color() { }


   };


   class CLASS_DECL_AURA set_keyboard_focus : public ::user::message
   {
   public:


      set_keyboard_focus() { }

      // using ::user::message::set;

      //virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam) override;


   };


#ifdef WINDOWS_DESKTOP


   class CLASS_DECL_AURA window_pos : public ::user::message
   {
   public:


      void * m_pWINDOWPOS;


      window_pos() {}

      // using ::user::message::set;

      //virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam) override;


   };


   class CLASS_DECL_AURA measure_item : public ::user::message
   {
   public:


      i32 m_i;
      void * m_LPMEASUREITEMSTRUCT;

      measure_item() { }


   };


   class CLASS_DECL_AURA nc_calc_size : public ::user::message
   {
   public:


      void * m_pNCCALCSIZE_PARAMS;


      nc_calc_size() { }

      bool GetCalcValidRects();

      // using ::user::message::set;

      //virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam) override;


   };


#endif


   class CLASS_DECL_AURA enable : public ::user::message
   {
   public:


      enable() { }

      bool get_enable();

   };


   class CLASS_DECL_AURA drag_and_drop : public ::user::message
   {
   public:


      drag_and_drop(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom);
      //
      //#ifdef WINDOWS
      //
      //      IDataObject *  pDataObj;// [in] DragEnter, Drop
      //      POINTL         point_i32; // [in] DragEnter, DragOver, Drop
      //      ::u32          grfKeyState; // [in] DragEnter, DragOver, Drop
      //      ::u32          dwEffect; // [in][out] DragEnter, DragOver, Drop
      //
      //#endif

   };


//   class CLASS_DECL_AURA text : public ::user::message
//   {
//   public:
//
//
//      string         m_strText;
//
//
//      text();
//
//
//   };



} // namespace message





