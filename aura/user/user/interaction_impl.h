#pragma once


#include "primitive_impl.h"
#include "window_util.h"
#include "interaction.h"


#ifdef __DEBUG

#define PRODEVIAN_QUIT_TIMEOUT_SECONDS 180

#else //__DEBUG

#define PRODEVIAN_QUIT_TIMEOUT_SECONDS 5

#endif //!__DEBUG


#if defined _UWP && defined(__cplusplus_winrt)


//namespace user
//{
//
//
//   class CLASS_DECL_AURA native_window
//   {
//   public:
//
//
//      ::aura::system_window ^ m_pwindow;
//
//
//   };
//
//
//} // namespace user



//#define interaction_impl ::user::interaction

#elif defined(APPLE_IOS)

class CLASS_DECL_AURA native_window
{
public:

};

//#define interaction_impl ::user::interaction

#else

class native_window;

#endif


namespace user
{


   class prodevian;
   class thread;


   class CLASS_DECL_AURA interaction_impl:
      virtual public ::user::primitive_impl
   {
   public:


#if defined(WINDOWS_DESKTOP) && !defined(ENABLE_TEXT_SERVICES_FRAMEWORK)
      //HIMC                                    m_himc;
#endif
      bool                                      m_bEatSizeEvent;
      bool                                      m_bEatMoveEvent;
      bool                                      m_bTransparentMouseEvents;
      bool                                      m_bOfflineRender;

      bool                                      m_bCursorRedraw;
      bool                                      m_bLockWindowUpdate;
      bool                                      m_bOkToUpdateScreen;
      bool                                      m_bScreenRelativeMouseMessagePosition;

      bool                                      m_bTranslateMouseMessageCursor;
      bool                                      m_bComposite;
      bool                                      m_bUpdateGraphics;
      bool                                      m_bPointInside;

      bool                                      m_bPendingRedraw;
      bool                                      m_bPadding1;
      bool                                      m_bPadding2;
      bool                                      m_bPadding3;

      ::IDENTIFIER_SUFFIX_OPERATING_SYSTEM(aura_)::interaction_impl *  m_pImpl2;
      ::rectangle_i32                           m_rectangleWindowScreen;
      ::rectangle_i32                           m_rectangleClientScreen;
      int                                       m_iState1;
      ::u32                                     m_uCodePage;
      int                                       m_iLangId;
      ::duration                                    m_durationLastExposureAddUp;
      __reference(prodevian)                    m_pprodevian;
      __reference(::user::thread)               m_puserthread;
      __pointer_array(::matter)                 m_matteraProdevian;
      string                                    m_strBitmapSource;
      __pointer(::windowing::windowing)         m_pwindowing;
      double                                    m_dProdevianFps;
      double                                    m_dNominalFps;
      double                                    m_dOutputFps;
      point_i32                                 m_pointMouseMove;
      ::size_i32                                m_sizeDrawn;
      reference_addressa                        m_ptraRedraw;

      ::rectangle_i32                           m_rectangleUpdateBuffer;
      ::thread_pointer                          m_pthreadMouseLeave;

      ::list < __pointer(::message::message) >  m_messagelist;

      ::point_i32                               m_pointInside;
      //::user::primitive *                       m_pprimitiveFocus;
      __pointer(::user::element)                m_pelementSoftwareKeyboard;

      __pointer(::windowing::window)            m_pwindow;

      point_i32                                 m_point;
      size_i32                                  m_size;

      //native_window *                         m_pwindow;

      __composite(::graphics::graphics)         m_pgraphics;

      __pointer(::mutex)                        m_pmutexDraw;
      __pointer(::mutex)                        m_pmutexRedraw;

      ::user::interaction_ptra                  m_userinteractionaMouseHover;

      ::u32                                     m_uiMessage;
      wparam                                    m_wparam;
      lparam                                    m_lparam;
      lparam                                    m_lparamLastMouseMove;

      __pointer(::user::interaction)            m_puserinteractionMouseCapture;
      __pointer(::user::interaction)            m_puserinteractionKeyboardFocus;
      __pointer(::user::interaction)            m_puserinteractionKeyboardFocusRequest;
      /// message handling helper besides (possibly duplicate of) m_puserinteractionKeyboardFocusRequest
      __pointer(::user::interaction)            m_puserinteractionKeyboardGainingFocusIfAny;
      __pointer(::user::interaction)            m_puserinteractionToKillKeyboardFocus;

      ::duration                                m_durationLastRedraw;
      ::user::interaction_array                 m_userinteractionaHideOnConfigurationChange;
      
      ::nanosecond                              m_nanosDeviceDrawBeg;
      ::nanosecond                              m_nanosDeviceDrawEnd;
      ::duration                                m_durationLastDeviceDraw;



      interaction_impl();
      ~interaction_impl() override;


      

      void assert_ok() const override;
      void dump(dump_context & dumpcontext) const override;

      virtual void set_prodevian_fps(double dProdevianFps);
      virtual void set_nominal_fps(double dNominalFps);
      virtual void set_fps(double dFps);
      virtual double get_prodevian_fps();
      virtual double get_nominal_fps();
      virtual double get_output_fps();

      void user_common_construct();

      virtual bool __windows_message_bypass(::windowing::window * pwindow, ::u32 message, wparam wparam, lparam lparam, lresult & lresult);

      void install_message_routing(::channel * pchannel) override;

      void default_message_handler(::message::message * pusermessage) override;

      virtual void on_tsf_activate(bool bActivate);

      virtual ::mutex * draw_mutex();

      virtual ::user::interaction_impl * get_user_interaction_impl() override;

      virtual void post(::message::message* pusermessage) override;


      virtual void set_bitmap_source(const string& strBitmapSource) override;
      virtual void clear_bitmap_source() override;


      virtual void update_graphics_resources();



      void queue_message_handler(::message::message * pmessage) override;


      void process_message();



      void set_tool_window(bool bSet) override;


      void create_host(::user::interaction * pinteraction) override;

      virtual ::color::color screen_pixel(int x, int y) const;
      void interaction_post(const ::procedure & procedure) override;

      // call these from window
      //virtual void set_keyboard_focus();
      //virtual void set_capture();
      //virtual void set_active_window();
      //virtual void set_foreground_window();


      virtual bool on_keyboard_focus(::user::primitive* pfocus);
      virtual bool keyboard_focus_OnKillFocus(oswindow oswindowNew) override;
      virtual bool keyboard_focus_OnChildKillFocus() override;

//      virtual void on_final_set_keyboard_focus(::message::set_keyboard_focus * psetkeyboardfocus);
//      virtual void on_final_kill_keyboard_focus(::message::kill_keyboard_focus * pkillkeyboardfocus);

      virtual void on_final_set_keyboard_focus();

      virtual void on_final_kill_keyboard_focus();

      virtual bool has_pending_focus();

      virtual bool set_pending_focus();

      virtual bool clear_pending_focus();

      void create_message_queue(::user::interaction * pinteraction, const ::string & lpszName) override;

      //virtual bool create_native_window(::user::native_window_initialize * pinitialize) override;
      //virtual void set_destroying();

      virtual void _000OnMouseLeave(::message::message * pmessage) override;
      //virtual void _008OnMouse(::message::mouse * pmouse);
      //virtual void _001BaseWndInterfaceMap();

      virtual void prio_install_message_routing(::channel * pchannel) override;
      virtual void last_install_message_routing(::channel * pchannel) override;

      //bool operator==(const interaction_impl& wnd) const;
      //bool operator!=(const interaction_impl& wnd) const;

      //virtual u32 GetStyle() const override;
      //virtual u32 GetExStyle() const override;
      //virtual bool ModifyStyle(u32 dwRemove,u32 dwAdd,::u32 nFlags = 0) override;
      //virtual bool ModifyStyleEx(u32 dwRemove,u32 dwAdd,::u32 nFlags = 0) override;


      virtual void set_icon(::windowing::icon* picon);
      virtual __pointer(::windowing::icon) get_icon() const;


      void mouse_hover_add(::user::interaction * pinterface) override;
      bool mouse_hover_erase(::user::interaction * pinterface) override;


      void _task_transparent_mouse_event() override;


      virtual void track_mouse_hover() override;
      virtual void track_mouse_leave() override;

      virtual void _on_mouse_move_step(const ::point_i32 & pointCursor, bool bMouseLeave = false);

      //virtual void mouse_hover_step(const __status < ::point_i32 > & statusPointCursor);


      void add_prodevian(::matter * pmatter) override;
      void erase_prodevian(::matter * pmatter) override;
      bool is_prodevian(const ::matter * pmatter) const override;
      inline bool has_prodevian() const noexcept { return m_matteraProdevian.has_element(); }

      void prodevian_stop() override;


      //virtual ::user::interaction * get_owner();
      ::user::primitive * set_owner(::user::primitive * pprimitiveOwner) override;

      bool has_pending_redraw_flags() override;

      virtual ::user::interaction_impl * from_os_data(void * pdata);
      virtual void * get_os_data() const;

      //bool attach(::windowing::window * pwindow_New) override;
      //oswindow detach() override;

      virtual void destroy() override;

      void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;

      DECLARE_MESSAGE_HANDLER(_002OnDraw);

      DECLARE_MESSAGE_HANDLER(on_message_kill_focus);
      DECLARE_MESSAGE_HANDLER(on_prio_message_set_focus);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);
      DECLARE_MESSAGE_HANDLER(_001OnApplyVisual);
      DECLARE_MESSAGE_HANDLER(on_message_move);
      DECLARE_MESSAGE_HANDLER(on_message_size);
      DECLARE_MESSAGE_HANDLER(_001OnDestroyWindow);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      DECLARE_MESSAGE_HANDLER(_001OnRedraw);
      DECLARE_MESSAGE_HANDLER(_001OnDoShowWindow);


//#if (WINVER >= 0x0500) && defined(WINDOWS_DESKTOP)
//
//      bool GetWindowInfo(PWINDOWINFO pwi) const;
//      bool GetTitleBarInfo(PTITLEBARINFO pti) const;
//
//#endif   // WINVER >= 0x0500

      // subclassing/unsubclassing functions
      void pre_subclass_window() override;
      //virtual bool subclass_window(::windowing::window * pwindow) override;
      //virtual bool SubclassDlgItem(::u32 nID, ::user::interaction_impl * pParent);
      //virtual oswindow unsubclass_window() override;

      // handling of RT_DLGINIT resource (extension to RT_DIALOG)
      //virtual bool ExecuteDlgInit(const ::string & pszResourceName);

      //virtual bool ExecuteDlgInit(void * pResource);





      //using ::user::primitive::create_interaction;
      //using ::user::primitive::create_window_ex;


      // for child windows, views, panes etc
      //virtual bool create_interaction(::user::interaction * pinteraction, ::u32 uExStyle, u32 uStyle, const ::rectangle_i32 & rectangle, ::user::primitive * puiParent, ::create * pcreate = nullptr) override;


      // advanced creation (allows access to extended styles)
      //virtual bool create_window_ex(::user::interaction * pinteraction, __pointer(::user::system) pcs, ::user::primitive * puiParent, atom atom) override;

      //virtual bool create_interaction() override;


      //virtual bool _native_create_window(::user::interaction * pinteraction, ::windowing::window * pwindow);

      
      //virtual bool _native_create_window_ex(__pointer(::user::system) pusersystem);

      //virtual bool _native_create_window_ex(__pointer(::user::system) pusersystem);

      //virtual bool create_host();

      virtual void operating_system_create_host();

      virtual void native_create_host_alternate();


      void destroy_impl_only() override;
      void start_destroying_window() override;
      void destroy_window() override;

      // special pre-creation and interaction_impl rectangle_i32 adjustment hooks
      virtual bool pre_create_window(::user::system * pusersystem);

      // Advanced: virtual AdjustWindowRect
//      enum AdjustType { adjustBorder = 0,adjustOutside = 1 };
      //virtual void CalcWindowRect(RECTANGLE_I32 * pClientRect,::u32 nAdjustType = adjustBorder) override;

      inline ::windowing::window * window() const { return m_pwindow; }
      inline ::windowing::windowing * windowing() const { return m_pwindowing; }



      virtual bool _is_window() const override;

#if(WINVER >= 0x0500)

      virtual ::user::interaction_impl* GetAncestor(::u32 gaFlags) const;

#endif   // WINVER >= 0x0500

      lresult send_message(const ::atom& atom, ::wparam wParam = 0, ::lparam lParam = 0, const ::point_i32 & point = nullptr) override;


//#ifdef LINUX
//
//      virtual lresult send_x11_event(void * pevent) override; // XEvent *
//
//#endif


      void post_message(const ::atom & atom,wparam wParam = 0,lparam lParam = 0) override;


      //virtual bool SendNotifyMessage(::u32 message,wparam wParam,lparam lParam);

      //virtual bool SendChildNotifyLastMsg(lresult* pResult = nullptr);

      //virtual bool DragDetect(const ::point_i32 & point) const;



      // Window Text Functions
      virtual void set_window_text(const ::string & pszString) override;

      strsize get_window_text(char * pszStringBuf, strsize nMaxCount) override;

      void get_window_text(string & rString) override;
      strsize get_window_text_length() override;


      // Window size_i32 and position Functions
      virtual bool window_is_iconic();
      virtual bool window_is_zoomed();
      //virtual i32 SetWindowRgn(HRGN hRgn,bool bRedraw);
      //virtual i32 GetWindowRgn(HRGN hRgn);

      //using ::user::primitive::set_window_position;
      //virtual bool set_window_position(class zorder zorder, i32 x, i32 y, i32 cx,i32 cy, ::u32 nFlags = SWP_SHOWWINDOW) override;
      virtual ::u32 ArrangeIconicWindows() override;
      //virtual bool BringWindowToTop() override;

//#ifdef WINDOWS_DESKTOP
//      virtual bool GetWindowPlacement(WINDOWPLACEMENT* puserinteractionpl);
//
//      virtual bool SetWindowPlacement(const WINDOWPLACEMENT* puserinteractionpl);
//
//#endif

      // Coordinate Mapping Functions
      virtual void MapWindowPoints(::user::interaction_impl* puserinteractionTo,POINT_I32 * pPoint,::u32 nCount);

      virtual void MapWindowPoints(::user::interaction_impl* puserinteractionTo,RECTANGLE_I32 * prectangle);


      virtual void Print(::draw2d::graphics_pointer & pgraphics,u32 dwFlags) const;
      virtual void PrintClient(::draw2d::graphics_pointer & pgraphics,u32 dwFlags) const;

      void UpdateWindow() override;
      void SetRedraw(bool bRedraw = true) override;
      //virtual bool GetUpdateRect(RECTANGLE_I32 * prectangle,bool bErase = false) override;

      //i32 GetUpdateRgn(::draw2d::region* pRgn,bool bErase = false) override;
      virtual void Invalidate(bool bErase = true) override;
      void InvalidateRect(const ::rectangle_i32 & rectangle,bool bErase = true) override;

      void InvalidateRgn(::draw2d::region* pRgn,bool bErase = true) override;
      void ValidateRect(const ::rectangle_i32 & rectangle) override;

      void ValidateRgn(::draw2d::region* pRgn) override;
      //virtual bool display(::e_display edisplay) override;
      //virtual bool _is_window_visible() override;
      void ShowOwnedPopups(bool bShow = true) override;

      //virtual __pointer(::draw2d::graphics) GetDCEx(::draw2d::region* prgnClip,u32 flags);
      virtual void LockWindowUpdate();
      virtual void UnlockWindowUpdate();

      void prodevian_update_screen() override;

      void prodevian_redraw(bool bUpdateBuffer) override;

//#ifdef WINDOWS
//
//      virtual bool RedrawWindow(const ::rectangle_i32 & rectangleUpdate = nullptr, ::draw2d::region* prgnUpdate = nullptr,::u32 flags = RDW_INVALIDATE | RDW_ERASE);
//
//#else

      void RedrawWindow(const ::rectangle_i32 & rectangleUpdate = nullptr, ::draw2d::region* prgnUpdate = nullptr,::u32 flags = 0) override;

//#endif


//#ifdef WINDOWS_DESKTOP
//
//      virtual bool EnableScrollBar(i32 nSBFlags,::u32 nArrowFlags = ESB_ENABLE_BOTH);
//
//#else

      //virtual void EnableScrollBar(i32 nSBFlags,::u32 nArrowFlags = 3);

//#endif


      //virtual ::point_i32 get_cursor_position() const override;

      void set_mouse_cursor(::windowing::cursor * pcursor) override;

      //virtual void set_cursor(enum_cursor ecursor) override;

      //virtual bool DrawCaption(::draw2d::graphics_pointer & pgraphics,const rectangle_i32 & prc,::u32 uFlags);


//#if(WINVER >= 0x0500)
//
//      virtual bool AnimateWindow(const ::duration & duration,u32 dwFlags);
//
//#endif


//#if(_WIN32_WINNT >= 0x0501)
//
//      virtual bool PrintWindow(::draw2d::graphics_pointer & pgraphics,::u32 nFlags) const;
//
//#endif


//#if(_WIN32_WINNT >= 0x0500)
//
//      virtual bool SetLayeredWindowAttributes(::color::color crKey,byte bAlpha,u32 dwFlags);
//      virtual bool UpdateLayeredWindow(::draw2d::graphics * pDCDst,POINT_I32 *pptDst,SIZE_I32 *psize,::draw2d::graphics * pDCSrc,POINT_I32 *pptSrc,::color::color crKey,BLENDFUNCTION *pblend,u32 dwFlags);
//
//#endif   // _WIN32_WINNT >= 0x0500

//#if(_WIN32_WINNT >= 0x0501)
//
//      virtual bool GetLayeredWindowAttributes(::color::color *pcrKey,byte *pbAlpha,u32 *pdwFlags) const;
//
//#endif   // _WIN32_WINNT >= 0x0501
//


      //virtual bool is_window_enabled() const override;
      void enable_window(bool bEnable = true) override;


      


      //virtual void CheckDlgButton(i32 nIDButton,::u32 nCheck);
      //virtual void CheckRadioButton(i32 nIDFirstButton,i32 nIDLastButton,
      //                              i32 nIDCheckButton);
      //virtual i32 GetCheckedRadioButton(i32 nIDFirstButton,i32 nIDLastButton);
      //virtual i32 DlgDirList(char * pPathSpec,i32 nIDListBox,

      //                       i32 nIDStaticPath,::u32 nFileType);
      //virtual i32 DlgDirListComboBox(char * pPathSpec,i32 nIDComboBox,

      //                               i32 nIDStaticPath,::u32 nFileType);
      //virtual bool DlgDirSelect(char * pString,i32 nSize,i32 nIDListBox);

      //virtual bool DlgDirSelectComboBox(char * pString,i32 nSize,i32 nIDComboBox);


      //virtual ::u32 GetChildByIdInt(i32 nID,bool* pTrans = nullptr,bool bSigned = true) const;

      //virtual i32 GetChildByIdText(i32 nID,char * pStr,i32 nMaxCount) const;

      //virtual i32 GetChildByIdText(i32 nID,string & rString) const;
      //virtual ::user::interaction_impl * GetNextDlgGroupItem(::user::interaction_impl * pWndCtl,bool bPrevious = false) const;
      //virtual ::user::interaction_impl * GetNextDlgTabItem(::user::interaction_impl * pWndCtl,bool bPrevious = false) const;
      //virtual ::u32 IsDlgButtonChecked(i32 nIDButton) const;
      //virtual lresult SendDlgItemMessage(i32 nID,::u32 message,wparam wParam = 0,lparam lParam = 0);
      //virtual void SetDlgItemInt(i32 nID,::u32 nValue,bool bSigned = true);
      //virtual void SetDlgItemText(i32 nID, const ::string & pszString);


      //virtual i32 GetScrollPos(i32 nBar) const;
      //virtual void GetScrollRange(i32 nBar, int * pMinPos, int * lpMaxPos) const;
      //virtual void ScrollWindow(i32 xAmount,i32 yAmount,
      //   const RECTANGLE_I32 * rectangle = nullptr,
      //   const RECTANGLE_I32 * pClipRect = nullptr);

      //virtual i32 SetScrollPos(i32 nBar,i32 nPos,bool bRedraw = true);
      //virtual void SetScrollRange(i32 nBar, i32 nMinPos, i32 nMaxPos, bool bRedraw = true);
      //virtual void ShowScrollBar(::u32 nBar,bool bShow = true);
      //virtual void EnableScrollBarCtrl(i32 nBar,bool bEnable = true);

      //virtual i32 ScrollWindowEx(i32 dx,i32 dy, const RECTANGLE_I32 * prectScroll, const RECTANGLE_I32 * lprectClip, ::draw2d::region* prgnUpdate, RECTANGLE_I32 * prectUpdate, ::u32 flags);


//#ifdef WINDOWS_DESKTOP
//
//      virtual bool SetScrollInfo(i32 nBar, LPSCROLLINFO pScrollInfo, bool bRedraw = true);
//      virtual bool GetScrollInfo(i32 nBar, LPSCROLLINFO pScrollInfo, ::u32 nMask = SIF_ALL);
//
//#endif


      //virtual i32 GetScrollLimit(i32 nBar);

//#if (WINVER >= 0x0500) && defined(WINDOWS_DESKTOP)
//
//      virtual bool GetScrollBarInfo(::i32 idObject,PSCROLLBARINFO psbi) const;
//
//#endif   // WINVER >= 0x0500

      virtual ::user::interaction * ChildWindowFromPoint(const ::point_i32 & point) override;
      virtual ::user::interaction * ChildWindowFromPoint(const ::point_i32 & point,::u32 nFlags) override;

//#ifdef WINDOWS_DESKTOP
  //    virtual ::user::interaction * get_next_window(::u32 nFlag = GW_HWNDNEXT);
//#else
//      virtual ::user::interaction * get_next_window(::u32 nFlag = 0) override;
//#endif



      virtual ::user::interaction * GetTopWindow();

      virtual ::user::interaction * GetLastActivePopup() override;

      //bool FlashWindow(bool bInvert);

      //virtual i32 message_box(const ::string & pszText, const ::string & pszCaption = nullptr,::u32 nType = e_message_box_ok);


//#if(WINVER >= 0x0500)
//
//      // virtual bool FlashWindowEx(u32 dwFlags, ::u32  uCount, ::duration tickTimeout);
//
//#endif   // WINVER >= 0x0500

      //virtual bool ChangeClipboardChain(::windowing::window * pwindow_Next);
      //virtual oswindow SetClipboardImpacter();
      //virtual bool OpenClipboard();

      virtual void HideCaret();
      virtual void ShowCaret();

      virtual void DragAcceptFiles(bool bAccept = true);

      //virtual bool SetWindowContextHelpId(u32 dwContextHelpId);
      //virtual u32 GetWindowContextHelpId() const;


      void update_data(bool bSaveAndValidate = true) override;


      void UpdateDialogControls(channel* pTarget,bool bDisableIfNoHndler);
      void CenterWindow(::user::interaction * pAlternateOwner = nullptr) override;


      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(_001OnPaint);
      DECLARE_MESSAGE_HANDLER(_001OnPrint);
      DECLARE_MESSAGE_HANDLER(_001OnCaptureChanged);
      DECLARE_MESSAGE_HANDLER(_001OnPrioCreate);


#ifdef WINDOWS_DESKTOP

      DECLARE_MESSAGE_HANDLER(_001OnWindowPosChanged);

#endif




      virtual void BeginModalState();
      virtual void EndModalState();

      virtual void pre_translate_message(::message::message * pmessage) override;

      virtual void message_handler(::message::message * pusermessage) override;
      virtual void _message_handler(::message::message* pusermessage);
      //virtual lresult default_window_procedure() override;
      virtual void default_window_procedure(::message::message * pmessage);


      virtual bool on_mouse_message(::message::mouse * pmouse);


      virtual void post_non_client_destroy() override;
      virtual bool OnChildNotify(::message::message * pusermessage) override;
      virtual bool ReflectChildNotify(::message::message * pusermessage);
      //virtual void CheckAutoCenter() override;


      virtual bool HandleFloatingSysCommand(::u32 nID,lparam lParam);
      bool IsTopParentActive() override;
      void ActivateTopParent() override;
      virtual void on_final_release();


      //virtual bool _EnableToolTips(bool bEnable,::u32 nFlag);
      //virtual void PrepareForHelp();


      // for creating dialogs and dialog-like windows
      //virtual bool CreateDlg(const ::string & pszTemplateName, ::user::interaction_impl * puiParent);

      //virtual bool CreateDlgIndirect(LPCDLGTEMPLATE pDialogTemplate, ::user::interaction_impl * puiParent,

      // HINSTANCE hInst);



      //// standard message implementation
      //lresult OnNTCtlColor(wparam wParam,lparam lParam);
      //lresult OnDisplayChange(wparam,lparam);
      //lresult OnDragList(wparam,lparam);

      virtual void _001DeferPaintLayeredWindowBackground(::image * pimage);

      virtual void _001OnDeferPaintLayeredWindowBackground(::image * pimage);

      //virtual ::i32 get_window_long(i32 nIndex) const override;
      //virtual ::i32 set_window_long(i32 nIndex,::i32 lValue) override;
      //virtual iptr get_window_long_ptr(i32 nIndex) const override;
      //virtual iptr set_window_long_ptr(i32 nIndex, iptr lValue) override;

      virtual interaction_impl * get_impl() const;

      virtual void _001UpdateWindow() override;


      virtual void start_window_visual() override;
      //virtual void sketch_to_design(::draw2d::graphics_pointer& pgraphics, bool & bUpdateBuffer, bool & bUpdateWindow) override;
      virtual void _001UpdateBuffer();
      virtual void _001UpdateScreen();
      //virtual void window_apply_visual(const window_state & windowstate) override;


      virtual void window_show();


      //virtual void update_graphics_resources();


      //virtual void set_handle(::windowing::window * pwindow);
      
      
      ::oswindow oswindow() const;


      ::graphics::graphics * get_window_graphics() override;

      
      bool is_composite() override;


      virtual void set_finish(::object * pobject);


      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      virtual void on_start_layout_experience(enum_layout_experience elayoutexperience) override;

      virtual void on_configuration_change(::user::primitive * pprimitiveSource) override;

      ::user::element * get_keyboard_focus() override;
      //virtual void set_keyboard_focus(::user::primitive * pprimitive) override;
      //virtual void erase_keyboard_focus(::user::primitive * pprimitive) override;
      void clear_keyboard_focus(::user::primitive_impl* pprimitiveimplGainingFocusIfAny = nullptr) override;
      //virtual void impl_set_keyboard_focus(::user::primitive * pprimitive) override;
      //virtual void impl_erase_keyboard_focus(::user::primitive * pprimitive) override;
      //virtual void impl_clear_keyboard_focus() override;

      virtual void redraw_add(::object * point_i32) override;
      virtual void redraw_erase(::object * point_i32) override;
      virtual bool has_redraw() override;
      virtual ::mutex * mutex_redraw();

      virtual void _001OnTriggerMouseInside() override;

      virtual bool has_pending_graphical_update() override;

      virtual void on_after_graphical_update() override;

      virtual bool is_this_visible(enum_layout elayout) override;

      virtual void window_show_change_visibility(::e_display edisplay, ::e_activation eactivation) override;


      virtual void ShowWindow(const ::e_display & edisplay);

      //virtual bool check_need_layout() override;
//virtual void clear_need_layout() override;
      virtual void set_need_layout() override;

      //virtual bool window_move(i32 x, i32 y) override;

      //virtual bool check_show_flags() override;

      virtual void on_visual_applied();

      //virtual void set_need_redraw(bool bAscendants = true) override;
      virtual void post_redraw(bool bAscendants = true) override;


      virtual void user_interaction_on_hide() override;

      void show_software_keyboard(::user::element * pelement) override;

      void hide_software_keyboard(::user::element * pelement) override;


      // Occlusion and Translucency
      virtual bool is_occluded();
      virtual i64 approximate_occlusion_area();
      virtual double approximate_occlusion_rate();
      virtual i64 approximate_occlusion_area_except_self_transparent();
      virtual double approximate_occlusion_rate_except_self_transparent();
      virtual i64 _001GetTopLeftWeightedOccludedOpaqueArea();
      virtual double _001GetTopLeftWeightedOccludedOpaqueRate() override;
      virtual i64 _001GetTopLeftWeightedArea();
      virtual i64 _001GetRectTopLeftWeightedArea(const RECTANGLE_I32 * lpcrect);

      virtual i64 opaque_area(const RECTANGLE_I32 * lpcrect);
      virtual void approximate_occlusion_rects(rectangle_i32_array& raTest);

      virtual i64 opaque_area();

      /// from top to bottom
      virtual void non_top_most_upper_window_rects(::rectangle_i32_array& recta);


      virtual void android_fill_plasma(const void * pixels, int width, int height, int stride, ::i64 time_ms);

   };


   class CLASS_DECL_AURA guie_message_wnd:
      virtual public interaction_impl
   {
   public:


      ::user::interaction * m_puiForward;


      guie_message_wnd(::property_object * pobject);


      virtual void message_handler(::message::message * pmessage);


   }; // guie_message_wnd


   class device_draw_life_time
   {
   public:


      ::user::interaction_impl * m_pimpl;

      
      device_draw_life_time(::user::interaction_impl * pimpl) :
         m_pimpl(pimpl)
      {

         m_pimpl->m_nanosDeviceDrawBeg.Now();

      }

      
      ~device_draw_life_time()
      {

         m_pimpl->m_nanosDeviceDrawEnd.Now();

      }

      
   };


} // namespace user


CLASS_DECL_AURA ::user::interaction * __interaction(::windowing::window * pwindow);



