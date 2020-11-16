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
   e_activate_active = 0,
   e_activate_click_active = 0,

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


   class CLASS_DECL_AURA create:
      public ::message::base
   {
   public:


      ::user::create_struct * m_lpcreatestruct;


      create() { }


      virtual void set(::layered * playeredUserPrimitive, const ::id & id, WPARAM wparam, ::lparam lparam) override;

      virtual void error(const char * pcszErrorMessage);

      virtual void failed(const char * pcszErrorMessage);

      ::matter * get_impact_data();

      ::create* get_create();


   };


   class CLASS_DECL_AURA activate: public ::message::base
   {
   public:


      ::enum_activate   m_eactivate;
      ::user::interaction * m_pWndOther;
      bool  m_bMinimized;


      activate();

      using ::message::base::set;

      virtual void set(::layered * playeredUserPrimitive, const ::id & id, WPARAM wparam, ::lparam lparam) override;


   };

   class CLASS_DECL_AURA move: public ::message::base
   {
   public:


      point m_point;

      move() { }

      using ::message::base::set;

      virtual void set(::layered * playeredUserPrimitive, const ::id & id, WPARAM wparam, ::lparam lparam) override;


   };


   class CLASS_DECL_AURA size: public ::message::base
   {
   public:


      ::u32     m_nType;
      ::size   m_size;

      size() { }

      using ::message::base::set;

      virtual void set(::layered * playeredUserPrimitive, const ::id & id, WPARAM wparam, ::lparam lparam) override;

   };


   class CLASS_DECL_AURA scroll: public ::message::base
   {
   public:


      ::u32                    m_nSBCode;
      i32                     m_nPos;
      ::user::primitive *     m_pScrollBar;


      scroll() { }

      using ::message::base::set;

      virtual void set(::layered * playeredUserPrimitive, const ::id & id, WPARAM wparam, ::lparam lparam) override;


   };


   class CLASS_DECL_AURA mouse:
      public ::message::base,
      public ::user::mouse
   {
   public:



      mouse();
      virtual ~mouse();

      using ::message::base::set;

      virtual void set(::layered * playeredUserPrimitive, const ::id & id, WPARAM wparam, ::lparam lparam) override;

      static mouse * cast(::message::message * pmessage)
      {
         return dynamic_cast < mouse * > (pmessage);
      }

      virtual unsigned int get_message() override
      {
         return (unsigned int) m_id.i64();
      }

   };

   class CLASS_DECL_AURA mouse_wheel:
      public mouse
   {
   public:


      mouse_wheel() { }

      ::u32 GetFlags();

      i16 GetDelta();

      point GetPoint();

      using ::message::base::set;

      virtual void set(::layered * playeredUserPrimitive, const ::id & id, WPARAM wparam, ::lparam lparam) override;

   };


   class CLASS_DECL_AURA mouse_activate: public ::message::base
   {
   public:


      mouse_activate() {}

      ::user::interaction * get_desktop_window();

      ::u32 GetHitTest();

      ::u32 get_message();

   };


   class CLASS_DECL_AURA context_menu: public ::message::base
   {
   public:


      context_menu() { }

      point GetPoint();


   };


   class CLASS_DECL_AURA set_cursor: public ::message::base
   {
   public:


      ::user::primitive *     m_pWnd;
      ::u32                    m_nHitTest;
      ::u32                    m_message;


      set_cursor() { }


   };


   class CLASS_DECL_AURA show_window: public ::message::base
   {
   public:

      
      bool m_bShow;
      ::u32  m_nStatus;


      show_window() { }

      using ::message::base::set;

      virtual void set(::layered * playeredUserPrimitive, const ::id & id, WPARAM wparam, ::lparam lparam) override;


   };


   class CLASS_DECL_AURA kill_focus : public ::message::base
   {
   public:

      
      oswindow       m_oswindowNew;

      kill_focus() { }

      using ::message::base::set;

      virtual void set(::layered * playeredUserPrimitive, const ::id & id, WPARAM wparam, ::lparam lparam) override;


   };


   class CLASS_DECL_AURA on_draw: public ::message::base
   {
   public:

      ::draw2d::graphics * m_pdc;

      on_draw() { }


   };


   class CLASS_DECL_AURA erase_bkgnd: public ::message::base
   {
   public:


      ::draw2d::graphics * m_pdc;


      erase_bkgnd();

      void set_result(bool bResult);


   };


   // e_message_paint -> aura
   // e_message_mouse_leave -> aura


   class CLASS_DECL_AURA nchittest: public ::message::base
   {
   public:


      point m_point;

      nchittest() { }

   };


   class CLASS_DECL_AURA key:
      public ::user::key
   {
   public:


      key();

      using ::message::base::set;

      virtual void set(::layered * playeredUserPrimitive, const ::id & id, WPARAM wparam, ::lparam lparam) override;

   };


   class CLASS_DECL_AURA nc_activate: public ::message::base
   {
   public:


      bool m_bActive;


      nc_activate();

      using ::message::base::set;
      virtual void set(::layered * playeredUserPrimitive, const ::id & id, WPARAM wparam, ::lparam lparam) override;

   };


   class CLASS_DECL_AURA notify: public ::message::base
   {
   public:


      notify() { }

#ifdef WINDOWS_DESKTOP

      LPNMHDR get_lpnmhdr();

#endif

      i32 get_ctrl_id();

   };


   class CLASS_DECL_AURA command: public ::message::base
   {
   public:


      command() { }

      ::u32 GetNotifyCode();

      ::u32 GetId();

      oswindow get_oswindow();

   };


   class CLASS_DECL_AURA ctl_color: public ::message::base
   {
   public:


      void *                     m_hbrush;
      ::draw2d::graphics *       m_pdc;
      ::u32                      m_nCtlType;

      ctl_color() { }


   };


   class CLASS_DECL_AURA set_focus: public ::message::base
   {
   public:


      set_focus() { }

      using ::message::base::set;

      virtual void set(::layered * playeredUserPrimitive, const ::id & id, WPARAM wparam, ::lparam lparam) override;


   };


#ifdef WINDOWS_DESKTOP

   class CLASS_DECL_AURA window_pos: public ::message::base
   {
   public:


      WINDOWPOS * m_pwindowpos;


      window_pos() {}

      using ::message::base::set;

      virtual void set(::layered * playeredUserPrimitive, const ::id & id, WPARAM wparam, ::lparam lparam) override;


   };


   class CLASS_DECL_AURA measure_item: public ::message::base
   {
   public:


      i32 m_i;
      LPMEASUREITEMSTRUCT m_lpmis;

      measure_item() { }


   };


   class CLASS_DECL_AURA nc_calc_size: public ::message::base
   {
   public:


      NCCALCSIZE_PARAMS * m_pparams;


      nc_calc_size() { }

      bool GetCalcValidRects();

      using ::message::base::set;

      virtual void set(::layered * playeredUserPrimitive, const ::id & id, WPARAM wparam, ::lparam lparam) override;


   };


#endif
   

   class CLASS_DECL_AURA enable: public ::message::base
   {
   public:


      enable() { }

      bool get_enable();

   };


   class CLASS_DECL_AURA drag_and_drop : public ::message::base
   {
   public:

      
      drag_and_drop(::layered * playeredUserPrimitive,const ::id & id)
      {

         m_lresult = 0;

         set(playeredUserPrimitive,id,0,0);

      }

#ifdef WINDOWS

      IDataObject *  pDataObj;// [in] DragEnter, Drop
      POINTL         point; // [in] DragEnter, DragOver, Drop
      ::u32          grfKeyState; // [in] DragEnter, DragOver, Drop
      ::u32          dwEffect; // [in][out] DragEnter, DragOver, Drop

#endif

   };

} // namespace message


