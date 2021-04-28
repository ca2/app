#pragma once

//namespace user
//{
//
//   class impact_data;
//
//}

enum enum_activate
{

   e_activate_inactive = 0,
   e_activate_active = 1,
   e_activate_click_active = 2,

};

#define MA_ACTIVATE         1
#define MA_ACTIVATEANDEAT   2
#define MA_NOACTIVATE       3
#define MA_NOACTIVATEANDEAT 4

enum enum_mouse_activate
{

   e_mouse_activate_not_set = 0,
   e_mouse_activate = 1,
   e_mouse_activate_and_eat = 2,
   e_mouse_activate_no_activate = 3,
   e_mouse_activate_no_activate_and_eat = 4,

};


#define MESSAGE_OLE_DRAGENTER WM_APP + 324
#define MESSAGE_OLE_DRAGOVER WM_APP + 325
#define MESSAGE_OLE_DRAGLEAVE WM_APP + 326
#define MESSAGE_OLE_DRAGDROP WM_APP + 327


namespace message
{


   
   class CLASS_DECL_AURA create :
      public ::user::message
   {
   public:


      __pointer(::user::system)       m_pusersystem;


      create() { }


      virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam) override;

      virtual void error(const char * pcszErrorMessage);

      virtual void failed(const char * pcszErrorMessage);

      ::create * get_create();

      ::user::system * get_user_create();

      ::matter * get_impact_data();


   };


   class CLASS_DECL_AURA activate : public ::user::message
   {
   public:


      ::enum_activate   m_eactivate;
      ::user::interaction * m_pWndOther;
      bool  m_bMinimized;


      activate();

      using ::user::message::set;

      virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam) override;

      inline bool is_active() const
      {

         return m_eactivate == e_activate_active || m_eactivate == e_activate_click_active;

      }

      inline bool inactive() const
      {

         return m_eactivate == e_activate_inactive;

      }


   };

   class CLASS_DECL_AURA move : public ::user::message
   {
   public:


      point_i32 m_point;

      move() { }

      using ::user::message::set;

      virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam) override;


   };


   class CLASS_DECL_AURA size : public ::user::message
   {
   public:


      ::u32          m_nType;
      ::size_i32     m_size;

      size() { }

      using ::user::message::set;

      virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam) override;

   };


   class CLASS_DECL_AURA scroll : public ::user::message
   {
   public:


      enum_scroll_command    m_ecommand;
      i32                        m_nPos;
      ::user::primitive * m_pscrollbar;


      scroll();
      virtual ~scroll();

      using ::user::message::set;

      virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam) override;


   };


   class CLASS_DECL_AURA mouse :
      public ::user::message,
      public ::user::mouse
   {
   public:



      mouse();
      virtual ~mouse();

      using ::user::message::set;

      virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam) override;




      static mouse * cast(::message::message * pmessage)
      {
         return dynamic_cast <mouse *> (pmessage);
      }

      virtual unsigned int get_message() override
      {
         return (unsigned int)m_id.i64();
      }

   };

   class CLASS_DECL_AURA mouse_wheel :
      public mouse
   {
   public:


      mouse_wheel() { }

      ::u32 GetFlags();

      i16 GetDelta();

      point_i32 GetPoint();

      using ::user::message::set;

      virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam) override;

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


   class CLASS_DECL_AURA set_cursor :
      public ::user::message,
      public ::user::mouse
   {
   public:


      ::user::primitive *        m_pWnd;
      ::u32                      m_nHitTest;
      ::u32                      m_message;


      set_cursor();
      ~set_cursor();


   };


   class CLASS_DECL_AURA show_window : public ::user::message
   {
   public:


      bool m_bShow;
      ::u32  m_nStatus;


      show_window() { }

      using ::user::message::set;

      virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam) override;


   };


   class CLASS_DECL_AURA kill_keyboard_focus : public ::user::message
   {
   public:


      oswindow       m_oswindowNew;

      kill_keyboard_focus() { }

      using ::user::message::set;

      virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam) override;


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

      virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam) override;

      void set_hit_test(enum_hit_test ehittest) { m_lresult = ehittest; }

   };


   class CLASS_DECL_AURA key :
      public ::user::key
   {
   public:


      key();

      using ::user::message::set;

      virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam) override;

   };


   class CLASS_DECL_AURA nc_activate : public ::user::message
   {
   public:


      bool m_bActive;


      nc_activate();

      using ::user::message::set;
      virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam) override;

   };


   class CLASS_DECL_AURA notify : public ::user::message
   {
   public:


      notify() { }
      //
      //#ifdef WINDOWS_DESKTOP
      //
      //      LPNMHDR get_lpnmhdr();
      //
      //#endif

      i32 get_ctrl_id();

   };

   // use ::user::message
   //class CLASS_DECL_AURA command : public ::user::message
   //{
   //public:


   //   command() { }




   //};


   class CLASS_DECL_AURA object : public ::user::message
   {
   public:

      __pointer(::matter)     m_pmatter;

      object();
       virtual ~object();


      virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam) override;


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

      using ::user::message::set;

      virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam) override;


   };


#ifdef WINDOWS_DESKTOP

   class CLASS_DECL_AURA window_pos : public ::user::message
   {
   public:


      void * m_pWINDOWPOS;


      window_pos() {}

      using ::user::message::set;

      virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam) override;


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

      using ::user::message::set;

      virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam) override;


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


      drag_and_drop(oswindow oswindow, ::windowing::window * pwindow, const ::id & id)
      {

         m_lresult = 0;

         set(oswindow, pwindow, id, 0, 0);

      }
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


} // namespace message



