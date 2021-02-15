#pragma once



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

      ::rectangle_i32                           m_rectWindowScreen;
      ::rectangle_i32                           m_rectClientScreen;
      int                                       m_iState1;
      ::u32                                     m_uCodePage;
      int                                       m_iLangId;
      bool                                      m_bEatSizeEvent;
      bool                                      m_bEatMoveEvent;
      millis                                    m_millisLastExposureAddUp;
      __composite(prodevian)                    m_pprodevian;
      __composite(::user::thread)               m_puserthread;
      simple_object_ptra                        m_ptraProdevian;
      bool                                      m_bTransparentMouseEvents;
      bool                                      m_bOfflineRender;
      bool                                      m_bFocus;
      bool                                      m_bCursorRedraw;
      double                                    m_dConfigFps;
      double                                    m_dOutputFps;
      bool                                      m_bLockWindowUpdate;
      point_i32                                 m_pointCursor;
      bool                                      m_bOkToUpdateScreen;
      ::size_i32                                m_sizeDrawn;
      reference_addressa                        m_ptraRedraw;

      ::rectangle_i32                           m_rectUpdateBuffer;
      ::thread_pointer                          m_pthreadMouseLeave;

      bool                                      m_bPointInside;
      ::point_i32                               m_pointInside;
      ::user::primitive *                       m_pprimitiveFocus;
      ::user::primitive *                       m_pprimitiveSoftwareKeyboard;

      __pointer(::windowing::window)            m_pwindow;
      bool                                      m_bScreenRelativeMouseMessagePosition;
      bool                                      m_bTranslateMouseMessageCursor;
      bool                                      m_bComposite;
      bool                                      m_bUpdateGraphics;

      point_i32                                 m_point;
      size_i32                                  m_size;

      //native_window *                         m_pwindow;

      __composite(::graphics::graphics)         m_pgraphics;

      __pointer(::mutex)                        m_pmutexDraw;
      __pointer(::mutex)                        m_pmutexRedraw;

      ::user::interaction_ptra                  m_uiptraMouseHover;

      ::u32                                     m_uiMessage;
      wparam                                    m_wparam;
      lparam                                    m_lparam;
      lparam                                    m_lparamLastMouseMove;

      __pointer(::user::interaction)            m_puserinteractionCapture;
      __pointer(::user::interaction)            m_puserinteractionFocus1;
      __pointer(::user::interaction)            m_puserinteractionFocusRequest;
      __pointer(::user::interaction)            m_puserinteractionToKillFocus;

      bool                                      m_bPendingRedraw;
      millis                                    m_millisLastRedraw;
      ::user::interaction_array                 m_userinteractionaHideOnConfigurationChange;


      interaction_impl();
      virtual ~interaction_impl();


      

      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;

      virtual void set_config_fps(double dConfigFps) override;
      virtual double get_config_fps() override;
      virtual double get_output_fps() override;

      void user_common_construct();

      virtual bool __windows_message_bypass(::windowing::window * pwindow, ::u32 message, wparam wparam, lparam lparam, lresult & lresult);

      virtual void install_message_routing(::channel * pchannel) override;

      virtual void default_message_handler(::message::message * pusermessage) override;

      virtual void on_tsf_activate(bool bActivate);

      virtual ::mutex * draw_mutex();

      virtual ::user::interaction_impl * get_user_interaction_impl() override;

      virtual bool post(::message::message* pusermessage) override;

      virtual ::e_status update_graphics_resources();


      virtual bool create_host(::user::interaction * pinteraction);


      virtual ::e_status main_async(const ::promise::routine & routine, e_priority epriority = priority_normal) override;

      // call these from window
      //virtual ::e_status set_keyboard_focus();
      //virtual ::e_status set_capture();
      //virtual ::e_status set_active_window();
      //virtual ::e_status set_foreground_window();

      virtual void on_final_set_keyboard_focus(::message::set_keyboard_focus * psetkeyboardfocus);
      virtual void on_final_kill_keyboard_focus(::message::kill_keyboard_focus * pkillkeyboardfocus);

      virtual bool has_pending_focus();

      virtual bool set_pending_focus();

      virtual bool clear_pending_focus();

      virtual bool create_message_queue(::user::interaction * pinteraction, const char * lpszName) override;

      //virtual bool create_native_window(::user::native_window_initialize * pinitialize) override;
      virtual void set_destroying();

      virtual void _000OnMouseLeave(::message::message * pmessage) override;
      //virtual void _008OnMouse(::message::mouse * pmouse);
      //virtual void _001BaseWndInterfaceMap();

      virtual void prio_install_message_routing(::channel * pchannel) override;
      virtual void last_install_message_routing(::channel * pchannel) override;

      bool operator==(const interaction_impl& wnd) const;
      bool operator!=(const interaction_impl& wnd) const;

      virtual u32 GetStyle() const override;
      virtual u32 GetExStyle() const override;
      virtual bool ModifyStyle(u32 dwRemove,u32 dwAdd,::u32 nFlags = 0) override;
      virtual bool ModifyStyleEx(u32 dwRemove,u32 dwAdd,::u32 nFlags = 0) override;


      virtual void mouse_hover_add(::user::interaction * pinterface) override;
      virtual bool mouse_hover_remove(::user::interaction * pinterface) override;


      virtual void _task_transparent_mouse_event();


      virtual void track_mouse_hover();
      virtual void track_mouse_leave();

      virtual void MouseLeaveThreadProcedure();

      virtual void mouse_hover_step(const __status < ::point_i32 > & statusPointCursor);


      virtual bool add_prodevian(::context_object * pobject) override;
      virtual bool remove_prodevian(::context_object * pobject) override;
      inline bool has_prodevian() const noexcept { return m_ptraProdevian.has_element(); }

      virtual void prodevian_stop() override;


      //virtual ::user::interaction * get_owner();
      virtual ::user::primitive * set_owner(::user::primitive * pprimitiveOwner) override;

      virtual bool has_pending_redraw_flags() override;
      virtual bool setWMClass(const char * psz) override;

      virtual ::user::interaction_impl * from_os_data(void * pdata);
      virtual void * get_os_data() const;

      //bool attach(::windowing::window * pwindow_New) override;
      //oswindow detach() override;

      virtual void finalize() override;

      virtual void route_command_message(::message::command * pcommand) override;

      DECL_GEN_SIGNAL(_002OnDraw);

      DECL_GEN_SIGNAL(_001OnKillFocus);
      DECL_GEN_SIGNAL(_001OnSetFocus);
      DECL_GEN_SIGNAL(_001OnShowWindow);
      DECL_GEN_SIGNAL(_001OnApplyVisual);
      DECL_GEN_SIGNAL(_001OnMove);
      DECL_GEN_SIGNAL(_001OnSize);
      DECL_GEN_SIGNAL(_001OnDestroyWindow);
      DECL_GEN_SIGNAL(_001OnRedraw);
      DECL_GEN_SIGNAL(_001OnDoShowWindow);


//#if (WINVER >= 0x0500) && defined(WINDOWS_DESKTOP)
//
//      bool GetWindowInfo(PWINDOWINFO pwi) const;
//      bool GetTitleBarInfo(PTITLEBARINFO pti) const;
//
//#endif   // WINVER >= 0x0500

      // subclassing/unsubclassing functions
      virtual void pre_subclass_window() override;
      //virtual bool subclass_window(::windowing::window * pwindow) override;
      //virtual bool SubclassDlgItem(::u32 nID, ::user::interaction_impl * pParent);
      //virtual oswindow unsubclass_window() override;

      // handling of RT_DLGINIT resource (extension to RT_DIALOG)
      virtual bool ExecuteDlgInit(const char * pszResourceName);

      virtual bool ExecuteDlgInit(void * pResource);





      //using ::user::primitive::create_interaction;
      //using ::user::primitive::create_window_ex;


      // for child windows, views, panes etc
      //virtual bool create_interaction(::user::interaction * pinteraction, ::u32 uExStyle, u32 uStyle, const ::rectangle_i32 & rectangle, ::user::primitive * puiParent, ::create * pcreate = nullptr) override;


      // advanced creation (allows access to extended styles)
      //virtual bool create_window_ex(::user::interaction * pinteraction, __pointer(::user::system) pcs, ::user::primitive * puiParent, id id) override;

      //virtual bool create_interaction() override;


      //virtual bool _native_create_window(::user::interaction * pinteraction, ::windowing::window * pwindow);

      
      //virtual bool _native_create_window_ex(__pointer(::user::system) pusersystem);

      //virtual bool _native_create_window_ex(__pointer(::user::system) pusersystem);

      //virtual bool create_host();

      virtual ::e_status native_create_host();


      virtual bool destroy_impl_only() override;
      virtual bool DestroyWindow() override;
      virtual void destroy_window() override;

      // special pre-creation and interaction_impl rectangle_i32 adjustment hooks
      virtual bool pre_create_window(::user::system * pusersystem) override;

      // Advanced: virtual AdjustWindowRect
//      enum AdjustType { adjustBorder = 0,adjustOutside = 1 };
      //virtual void CalcWindowRect(RECTANGLE_I32 * pClientRect,::u32 nAdjustType = adjustBorder) override;




      virtual bool _is_window() const override;

#if(WINVER >= 0x0500)

      virtual ::user::interaction_impl* GetAncestor(::u32 gaFlags) const;

#endif   // WINVER >= 0x0500

      virtual lresult send_message(const ::id & id, wparam wParam = 0, lparam lParam = 0) override;


#ifdef LINUX

      virtual lresult send_x11_event(void * pevent) override; // XEvent *

#endif


      virtual bool post_message(const ::id & id,wparam wParam = 0,lparam lParam = 0) override;


      //virtual bool SendNotifyMessage(::u32 message,wparam wParam,lparam lParam);

      //virtual bool SendChildNotifyLastMsg(lresult* pResult = nullptr);

      virtual bool DragDetect(const ::point_i32 & point) const;



      // Window Text Functions
      virtual void set_window_text(const char * pszString) override;

      virtual strsize get_window_text(char * pszStringBuf,i32 nMaxCount);

      virtual void get_window_text(string & rString);
      virtual strsize get_window_text_length();


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
//      virtual bool GetWindowPlacement(WINDOWPLACEMENT* pwndpl);
//
//      virtual bool SetWindowPlacement(const WINDOWPLACEMENT* pwndpl);
//
//#endif

      // Coordinate Mapping Functions
      virtual void MapWindowPoints(::user::interaction_impl* pwndTo,POINT_I32 * pPoint,::u32 nCount);

      virtual void MapWindowPoints(::user::interaction_impl* pwndTo,RECTANGLE_I32 * prectangle);


      virtual void Print(::draw2d::graphics_pointer & pgraphics,u32 dwFlags) const;
      virtual void PrintClient(::draw2d::graphics_pointer & pgraphics,u32 dwFlags) const;

      virtual void UpdateWindow() override;
      virtual void SetRedraw(bool bRedraw = true) override;
      virtual bool GetUpdateRect(RECTANGLE_I32 * prectangle,bool bErase = false) override;

      virtual i32 GetUpdateRgn(::draw2d::region* pRgn,bool bErase = false) override;
      virtual void Invalidate(bool bErase = true) override;
      virtual void InvalidateRect(const ::rectangle_i32 & rectangle,bool bErase = true) override;

      virtual void InvalidateRgn(::draw2d::region* pRgn,bool bErase = true) override;
      virtual void ValidateRect(const ::rectangle_i32 & rectangle) override;

      virtual void ValidateRgn(::draw2d::region* pRgn) override;
      //virtual bool display(::e_display edisplay) override;
      //virtual bool _is_window_visible() override;
      virtual void ShowOwnedPopups(bool bShow = true) override;

      //virtual __pointer(::draw2d::graphics) GetDCEx(::draw2d::region* prgnClip,u32 flags);
      virtual bool LockWindowUpdate();
      virtual void UnlockWindowUpdate();

      virtual bool prodevian_update_screen() override;

      virtual void prodevian_redraw(bool bUpdateBuffer) override;

//#ifdef WINDOWS
//
//      virtual bool RedrawWindow(const ::rectangle_i32 & rectUpdate = nullptr, ::draw2d::region* prgnUpdate = nullptr,::u32 flags = RDW_INVALIDATE | RDW_ERASE);
//
//#else

      virtual bool RedrawWindow(const ::rectangle_i32 & rectUpdate = nullptr, ::draw2d::region* prgnUpdate = nullptr,::u32 flags = 0) override;

//#endif


//#ifdef WINDOWS_DESKTOP
//
//      virtual bool EnableScrollBar(i32 nSBFlags,::u32 nArrowFlags = ESB_ENABLE_BOTH);
//
//#else

      virtual bool EnableScrollBar(i32 nSBFlags,::u32 nArrowFlags = 3);

//#endif


      //virtual ::point_i32 get_cursor_pos() const override;

      virtual ::e_status set_cursor(::windowing::cursor * pcursor) override;

      virtual ::e_status set_cursor(enum_cursor ecursor) override;

      virtual bool DrawCaption(::draw2d::graphics_pointer & pgraphics,const rectangle_i32 & prc,::u32 uFlags);


#if(WINVER >= 0x0500)

      virtual bool AnimateWindow(millis millis,u32 dwFlags);

#endif


#if(_WIN32_WINNT >= 0x0501)

      virtual bool PrintWindow(::draw2d::graphics_pointer & pgraphics,::u32 nFlags) const;

#endif


//#if(_WIN32_WINNT >= 0x0500)
//
//      virtual bool SetLayeredWindowAttributes(color32_t crKey,byte bAlpha,u32 dwFlags);
//      virtual bool UpdateLayeredWindow(::draw2d::graphics * pDCDst,POINT_I32 *pptDst,SIZE_I32 *psize,::draw2d::graphics * pDCSrc,POINT_I32 *pptSrc,color32_t crKey,BLENDFUNCTION *pblend,u32 dwFlags);
//
//#endif   // _WIN32_WINNT >= 0x0500

#if(_WIN32_WINNT >= 0x0501)

      virtual bool GetLayeredWindowAttributes(color32_t *pcrKey,byte *pbAlpha,u32 *pdwFlags) const;

#endif   // _WIN32_WINNT >= 0x0501



      //virtual bool is_window_enabled() const override;
      virtual bool enable_window(bool bEnable = true) override;


      


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
      //virtual void SetDlgItemText(i32 nID,const char * pszString);


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


      virtual i32 GetScrollLimit(i32 nBar);

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

      bool FlashWindow(bool bInvert);

      //virtual i32 message_box(const char * pszText,const char * pszCaption = nullptr,::u32 nType = e_message_box_ok);


#if(WINVER >= 0x0500)

      virtual bool FlashWindowEx(u32 dwFlags,::u32  uCount,millis tickTimeout);

#endif   // WINVER >= 0x0500

      //virtual bool ChangeClipboardChain(::windowing::window * pwindow_Next);
      //virtual oswindow SetClipboardViewer();
      //virtual bool OpenClipboard();

      virtual void HideCaret();
      virtual void ShowCaret();

      virtual void DragAcceptFiles(bool bAccept = true);

      virtual bool SetWindowContextHelpId(u32 dwContextHelpId);
      virtual u32 GetWindowContextHelpId() const;


      virtual bool update_data(bool bSaveAndValidate = true) override;


      virtual void UpdateDialogControls(channel* pTarget,bool bDisableIfNoHndler);
      virtual void CenterWindow(::user::interaction * pAlternateOwner = nullptr) override;


      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnPaint);
      DECL_GEN_SIGNAL(_001OnPrint);
      DECL_GEN_SIGNAL(_001OnCaptureChanged);
      DECL_GEN_SIGNAL(_001OnPrioCreate);


#ifdef WINDOWS_DESKTOP

      DECL_GEN_SIGNAL(_001OnWindowPosChanged);

#endif




      virtual void BeginModalState();
      virtual void EndModalState();

      virtual void pre_translate_message(::message::message * pmessage) override;

      virtual void message_handler(::message::message * pusermessage) override;
      //virtual lresult default_window_procedure() override;
      virtual void default_window_procedure(::message::message * pmessage);


      virtual void PostNcDestroy() override;
      virtual bool OnChildNotify(::message::message * pusermessage) override;
      virtual bool ReflectChildNotify(::message::message * pusermessage);
      virtual bool CheckAutoCenter() override;


      virtual bool HandleFloatingSysCommand(::u32 nID,lparam lParam);
      virtual bool IsTopParentActive() override;
      virtual void ActivateTopParent() override;
      virtual void on_final_release();


      //virtual bool _EnableToolTips(bool bEnable,::u32 nFlag);
      //virtual void PrepareForHelp();


      // for creating dialogs and dialog-like windows
      //virtual bool CreateDlg(const char * pszTemplateName, ::user::interaction_impl * puiParent);

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
      virtual iptr get_window_long_ptr(i32 nIndex) const override;
      virtual iptr set_window_long_ptr(i32 nIndex, iptr lValue) override;

      virtual interaction_impl * get_impl() const override;

      virtual void _001UpdateWindow() override;


      virtual bool start_window_visual() override;
      //virtual void sketch_to_design(::draw2d::graphics_pointer& pgraphics, bool & bUpdateBuffer, bool & bUpdateWindow) override;
      virtual void _001UpdateBuffer();
      virtual void _001UpdateScreen();
      //virtual void window_apply_visual(const window_state & windowstate) override;


      virtual void window_show();


      //virtual void update_graphics_resources();


      //virtual void set_handle(::windowing::window * pwindow);
      
      virtual oswindow get_oswindow() const override;

      virtual ::graphics::graphics * get_window_graphics() override;

      virtual bool is_composite() override;


      virtual ::e_status set_finish(::context_object * pcontextobject) override;


      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      virtual void on_start_layout_experience(enum_layout_experience elayoutexperience) override;

      virtual void on_configuration_change(::user::primitive * pprimitiveSource) override;

      //virtual ::user::primitive * get_keyboard_focus() override;
      //virtual ::e_status set_keyboard_focus(::user::primitive * pprimitive) override;
      //virtual ::e_status remove_keyboard_focus(::user::primitive * pprimitive) override;
      //virtual ::e_status clear_keyboard_focus() override;
      //virtual ::e_status impl_set_keyboard_focus(::user::primitive * pprimitive) override;
      //virtual ::e_status impl_remove_keyboard_focus(::user::primitive * pprimitive) override;
      //virtual ::e_status impl_clear_keyboard_focus() override;

      virtual void redraw_add(::context_object * point_i32) override;
      virtual void redraw_remove(::context_object * point_i32) override;
      virtual bool has_redraw() override;
      virtual ::mutex * mutex_redraw();

      virtual void _001OnTriggerMouseInside() override;

      virtual bool has_pending_graphical_update() override;

      virtual void on_after_graphical_update() override;

      virtual bool is_this_visible(enum_layout elayout) override;

      virtual void window_show_change_visibility(::e_display edisplay, ::e_activation eactivation) override;


      virtual bool ShowWindow(const ::e_display & edisplay);

      //virtual bool check_need_layout() override;
//virtual void clear_need_layout() override;
      virtual void set_need_layout() override;

      //virtual bool window_move(i32 x, i32 y) override;

      //virtual bool check_show_flags() override;

      virtual void on_visual_applied();

      //virtual void set_need_redraw(bool bAscendants = true) override;
      virtual void post_redraw(bool bAscendants = true) override;


      virtual void user_interaction_on_hide() override;

      virtual ::e_status show_software_keyboard(::user::primitive * pprimitive, string str, strsize iBeg, strsize iEnd) override;

      virtual ::e_status hide_software_keyboard(::user::primitive * pprimitive) override;


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
      virtual void approximate_occlusion_rects(rect_array& raTest);

      virtual i64 opaque_area();

      /// from top to bottom
      virtual void non_top_most_upper_window_rects(::rect_array& recta);


      virtual ::windowing::window * get_window() const override;


   };


   class CLASS_DECL_AURA guie_message_wnd:
      virtual public interaction_impl
   {
   public:


      ::user::interaction * m_puiForward;


      guie_message_wnd(::layered * pobjectContext);


      virtual void message_handler(::message::message * pusermessage);

   }; // guie_message_wnd


} // namespace user


inline ::user::interaction * __interaction(::windowing::window * pwindow)
{

   if (::is_null(pwindow)) return nullptr;

   auto pimpl = pwindow->m_pimpl;

   if (!pimpl) return nullptr;

   return pimpl->m_puserinteraction;

}



