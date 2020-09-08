#pragma once

//namespace user
//{
//
//   class impact_data;
//
//}


#define MESSAGE_OLE_DRAGENTER WM_APP + 324
#define MESSAGE_OLE_DRAGOVER WM_APP + 325
#define MESSAGE_OLE_DRAGLEAVE WM_APP + 326
#define MESSAGE_OLE_DRAGDROP WM_APP + 327

namespace message
{


   class CLASS_DECL_AQUA create:
      public ::message::base
   {
   public:


      ::user::create_struct * m_lpcreatestruct;


      create() { }


      virtual void set(::user::primitive * pwnd, UINT uiMessage, WPARAM wparam, ::lparam lparam) override;

      virtual void error(const char * pcszErrorMessage);

      virtual void failed(const char * pcszErrorMessage);

      ::generic_object * get_impact_data();

      ::create* get_create();


   };


   class CLASS_DECL_AQUA activate: public ::message::base
   {
   public:


      UINT  m_nState;
      ::user::interaction * m_pWndOther;
      bool  m_bMinimized;


      activate();

      using ::message::base::set;

      virtual void set(::user::primitive * pwnd, UINT uiMessage, WPARAM wparam, ::lparam lparam) override;


   };

   class CLASS_DECL_AQUA move: public ::message::base
   {
   public:


      point m_point;

      move() { }

      using ::message::base::set;

      virtual void set(::user::primitive * pwnd, UINT uiMessage, WPARAM wparam, ::lparam lparam) override;


   };


   class CLASS_DECL_AQUA size: public ::message::base
   {
   public:


      UINT     m_nType;
      ::size   m_size;

      size() { }

      using ::message::base::set;

      virtual void set(::user::primitive * pwnd, UINT uiMessage, WPARAM wparam, ::lparam lparam) override;

   };


   class CLASS_DECL_AQUA scroll: public ::message::base
   {
   public:


      UINT                    m_nSBCode;
      i32                     m_nPos;
      ::user::primitive *     m_pScrollBar;


      scroll() { }

      using ::message::base::set;

      virtual void set(::user::primitive * pwnd, UINT uiMessage, WPARAM wparam, ::lparam lparam) override;


   };


   class CLASS_DECL_AQUA mouse:
      public ::message::base,
      public ::user::mouse
   {
   public:



      mouse();
      virtual ~mouse();

      using ::message::base::set;

      virtual void set(::user::primitive * pwnd, UINT uiMessage, WPARAM wparam, ::lparam lparam) override;

      static mouse * cast(::message::message * pmessage)
      {
         return dynamic_cast < mouse * > (pmessage);
      }

      virtual unsigned int get_message() override
      {
         return (unsigned int) m_id.i64();
      }

   };

   class CLASS_DECL_AQUA mouse_wheel:
      public mouse
   {
   public:


      mouse_wheel() { }

      UINT GetFlags();

      i16 GetDelta();

      point GetPoint();

      using ::message::base::set;

      virtual void set(::user::primitive * pwnd, UINT uiMessage, WPARAM wparam, ::lparam lparam) override;

   };


   class CLASS_DECL_AQUA mouse_activate: public ::message::base
   {
   public:


      mouse_activate() {}

      ::user::interaction * get_desktop_window();

      UINT GetHitTest();

      UINT get_message();

   };


   class CLASS_DECL_AQUA context_menu: public ::message::base
   {
   public:


      context_menu() { }

      point GetPoint();


   };


   class CLASS_DECL_AQUA set_cursor: public ::message::base
   {
   public:


      ::user::primitive *     m_pWnd;
      UINT                    m_nHitTest;
      UINT                    m_message;


      set_cursor() { }


   };


   class CLASS_DECL_AQUA show_window: public ::message::base
   {
   public:

      
      bool m_bShow;
      UINT  m_nStatus;


      show_window() { }

      using ::message::base::set;

      virtual void set(::user::primitive * pwnd, UINT uiMessage, WPARAM wparam, ::lparam lparam) override;


   };


   class CLASS_DECL_AQUA kill_focus : public ::message::base
   {
   public:

      
      oswindow       m_oswindowNew;

      kill_focus() { }

      using ::message::base::set;

      virtual void set(::user::primitive * pwnd, UINT uiMessage, WPARAM wparam, ::lparam lparam) override;


   };


   class CLASS_DECL_AQUA on_draw: public ::message::base
   {
   public:

      ::draw2d::graphics * m_pdc;

      on_draw() { }


   };


   class CLASS_DECL_AQUA erase_bkgnd: public ::message::base
   {
   public:


      ::draw2d::graphics * m_pdc;


      erase_bkgnd();

      void set_result(bool bResult);


   };


   // WM_PAINT -> aqua
   // WM_MOUSELEAVE -> aqua


   class CLASS_DECL_AQUA nchittest: public ::message::base
   {
   public:


      point m_point;

      nchittest() { }

   };


   class CLASS_DECL_AQUA key:
      public ::user::key
   {
   public:


      key();

      using ::message::base::set;

      virtual void set(::user::primitive * pwnd, UINT uiMessage, WPARAM wparam, ::lparam lparam) override;

   };


   class CLASS_DECL_AQUA nc_activate: public ::message::base
   {
   public:


      bool m_bActive;


      nc_activate();

      using ::message::base::set;
      virtual void set(::user::primitive * pwnd, UINT uiMessage, WPARAM wparam, ::lparam lparam) override;

   };


   class CLASS_DECL_AQUA notify: public ::message::base
   {
   public:


      notify() { }

#ifdef WINDOWS_DESKTOP

      LPNMHDR get_lpnmhdr();

#endif

      i32 get_ctrl_id();

   };


   class CLASS_DECL_AQUA command: public ::message::base
   {
   public:


      command() { }

      UINT GetNotifyCode();

      UINT GetId();

      oswindow get_oswindow();

   };


   class CLASS_DECL_AQUA ctl_color: public ::message::base
   {
   public:


      HBRUSH                     m_hbrush;
      ::draw2d::graphics *       m_pdc;
      UINT                       m_nCtlType;

      ctl_color() { }


   };


   class CLASS_DECL_AQUA set_focus: public ::message::base
   {
   public:


      set_focus() { }

      using ::message::base::set;

      virtual void set(::user::primitive * pwnd, UINT uiMessage, WPARAM wparam, ::lparam lparam) override;


   };



   class CLASS_DECL_AQUA window_pos: public ::message::base
   {
   public:


      WINDOWPOS * m_pwindowpos;


      window_pos() {}

      using ::message::base::set;

      virtual void set(::user::primitive * pwnd, UINT uiMessage, WPARAM wparam, ::lparam lparam) override;


   };



#ifdef WINDOWS_DESKTOP


   class CLASS_DECL_AQUA measure_item: public ::message::base
   {
   public:


      i32 m_i;
      LPMEASUREITEMSTRUCT m_lpmis;

      measure_item() { }


   };


#endif


   class CLASS_DECL_AQUA nc_calc_size: public ::message::base
   {
   public:


      NCCALCSIZE_PARAMS * m_pparams;


      nc_calc_size() { }

      bool GetCalcValidRects();

      using ::message::base::set;

      virtual void set(::user::primitive * pwnd, UINT uiMessage, WPARAM wparam, ::lparam lparam) override;


   };


   class CLASS_DECL_AQUA enable: public ::message::base
   {
   public:


      enable() { }

      bool get_enable();

   };


   class CLASS_DECL_AQUA drag_and_drop : public ::message::base
   {
   public:

      
      drag_and_drop(::user::primitive * pwnd,UINT uiMessage)
      {

         m_lresult = 0;

         set(pwnd,uiMessage,0,0);

      }

#ifdef WINDOWS

      IDataObject *  pDataObj;// [in] DragEnter, Drop
      POINTL         point; // [in] DragEnter, DragOver, Drop
      DWORD          grfKeyState; // [in] DragEnter, DragOver, Drop
      DWORD          dwEffect; // [in][out] DragEnter, DragOver, Drop

#endif

   };

} // namespace message


