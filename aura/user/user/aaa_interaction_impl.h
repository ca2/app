#pragma once


#include "primitive_impl.h"
#include "interaction_array.h"
#include "interaction.h"
#include "redraw.h"
#include "acme/prototype/collection/list.h"
#include "acme/prototype/geometry2d/_collection.h"


#ifdef __DEBUG

#define PRODEVIAN_QUIT_TIMEOUT_SECONDS 180

#else //__DEBUG

#define PRODEVIAN_QUIT_TIMEOUT_SECONDS 5

#endif //!__DEBUG


#if defined UNIVERSAL_WINDOWS && defined(__cplusplus_winrt)


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



   class graphics_thread;
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
      //bool                                      m_bOfflineRender;

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
      ::int_rectangle                           m_rectangleWindowScreen;
      ::int_rectangle                           m_rectangleXScreen;
      int                                       m_iState1;
      unsigned int                                     m_uCodePage;
      int                                       m_iLangId;
      class ::time                              m_timeLastExposureAddUp;
      ::pointer<::user::graphics_thread>        m_pgraphicsthread;
      ::pointer<::user::thread>                 m_puserthread;
      pointer_array < ::graphics::output_purpose > m_graphicaloutputpurposea;
      string                                    m_strBitmapSource;
      ::pointer<::windowing::windowing>         m_pwindowing;
      ::frequency                               m_frequencyProdevianFramesPerSecond;
      ::frequency                               m_frequencyNominalFramesPerSecond;
      ::frequency                               m_frequencyOutputFramesPerSecond;
      int_point                                 m_pointMouseMove;
      //::int_size                              m_sizeDrawnAAA;
      ::int_size                                m_sizeSetWindowSizeRequest;
      particle_array                            m_particleaRedraw;

      //::int_rectangle                           m_rectangleUpdateBuffer;
      ::thread_pointer                          m_pthreadMouseLeave;

      ::list < ::pointer<::message::message >> m_messagelist;

      ::int_point                               m_pointInside;
      //::user::interaction_base *                       m_pprimitiveFocus;
      ::pointer<::user::element>               m_pelementSoftwareKeyboard;

      ::pointer<::windowing::window>           m_pwindow;

      int_point                                 m_point;
      int_size                                  m_size;

      //native_window *                         m_pwindow;

      ::pointer<::graphics::graphics>           m_pgraphicsgraphics;
      ::pointer<::draw2d::graphics>             m_pdraw2dgraphics;

      ::pointer < ::mutex >                     m_pmutexDraw;
      ::pointer < ::mutex >                     m_pmutexRedraw;

      ::user::interaction_ptra                  m_userinteractionaMouseHover;

      unsigned int                                     m_uiMessage;
      wparam                                    m_wparam;
      lparam                                    m_lparam;
      lparam                                    m_lparamLastMouseMove;

      bool                                      m_bUpdateBufferPending;

      ::pointer<::user::interaction>            m_puserinteractionMouseCapture;
      ::pointer<::user::interaction>            m_puserinteractionKeyboardFocus;
      ::pointer<::user::interaction>            m_puserinteractionKeyboardFocusRequest;
      /// message handling helper besides (possibly duplicate of) m_puserinteractionKeyboardFocusRequest
      ::pointer<::user::interaction>            m_puserinteractionKeyboardGainingFocusIfAny;
      ::pointer<::user::interaction>            m_puserinteractionToKillKeyboardFocus;

      class ::time                              m_timeLastRedraw;
      ::user::interaction_array                 m_userinteractionaHideOnConfigurationChange;
      
      class ::time                              m_timeDeviceDrawBeg;
      class ::time                              m_timeDeviceDrawEnd;
      class ::time                              m_timeLastDeviceDraw;

      ::int_size                                m_sizeDrawnBuffer;

//      ::int_rectangle_array                     m_rectangleaNeedRedraw;
      ::pointer_array < redraw_item >           m_redrawitema;

      ::pointer < ::user::interaction >         m_puiLastLButtonDown;
      ::item_pointer                            m_pitemLButtonDown;

      bool                                      m_bDoingGraphics;


      ::int_size                                m_sizeLastBuffer;


      interaction_impl();
      ~interaction_impl() override;


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      //virtual void sketch_to_layout(::graphics::buffer_item * pbufferitem);


      virtual void set_prodevian_frames_per_second(::frequency frequencyProdevianFramesPerSecond);
      virtual void set_nominal_frames_per_second(::frequency frequencyNominalFramesPerSecond);
      virtual void set_per_second(::frequency frequencyFramesPerSecond);
      virtual ::frequency get_prodevian_frames_per_second();
      virtual ::frequency get_nominal_frames_per_second();
      virtual ::frequency get_output_per_second();

      void user_common_construct();

      void on_initialize_particle() override;

      virtual bool __windows_message_bypass(::windowing::window * pwindow, unsigned int message, wparam wparam, lparam lparam, lresult & lresult);

      void install_message_routing(::channel * pchannel) override;

      void default_message_handler(::message::message * pusermessage) override;

      virtual void on_tsf_activate(bool bActivate);

      virtual ::pointer< ::mutex > draw_mutex();

      ::windowing::window * get_user_interaction_impl() override;

      void post_message(::message::message* pusermessage) override;


      void set_bitmap_source(const string& strBitmapSource) override;
      void clear_bitmap_source() override;


      virtual void update_graphics_resources();



      void queue_message_handler(::message::message * pmessage) override;


      void process_message();


      //bool is_there_graphics_output_interest() const override;


      void set_tool_window(bool bSet) override;


      //void create_host(::user::interaction * pinteraction, enum_parallelization eparallelization) override;

      void create_host(::user::interaction * pinteraction) override;

      virtual ::color::color screen_pixel(int x, int y) const;
      void interaction_post(const ::procedure & procedure) override;

      //virtual void user_call(const ::procedure & procedure);

      // call these from window
      //virtual void set_keyboard_focus();
      virtual void set_mouse_capture(::user::interaction * puserinteraction);
      virtual bool defer_release_mouse_capture(::user::interaction * puserinteraction);
      //virtual void set_active_window();
      //virtual void set_foreground_window();


      virtual bool on_keyboard_focus(::user::interaction_base* pfocus);
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

      //virtual unsigned int GetStyle() const override;
      //virtual unsigned int GetExStyle() const override;
      //virtual bool ModifyStyle(unsigned int dwRemove,unsigned int dwAdd,unsigned int nFlags = 0) override;
      //virtual bool ModifyStyleEx(unsigned int dwRemove,unsigned int dwAdd,unsigned int nFlags = 0) override;


      virtual void set_icon(::windowing::icon* picon);
      virtual ::pointer<::windowing::icon>get_icon() const;


      void mouse_hover_add(::user::interaction * pinterface) override;
      bool mouse_hover_erase(::user::interaction * pinterface) override;


      void _task_transparent_mouse_event() override;


      virtual void track_mouse_hover() override;
      virtual void track_mouse_leave() override;

      virtual void _on_mouse_move_step(const ::int_point & pointCursor, bool bMouseLeave = false);

      //virtual void mouse_hover_step(const __status < ::int_point > & statusPointCursor);

      void add(::graphics::output_purpose * pgraphicaloutputpurpose) override;
      void erase(::graphics::output_purpose * pgraphicaloutputpurpose) override;
      void add_graphical_output_purpose(::particle * pparticle, ::graphics::enum_output_purpose epurpose) override;
      void erase_graphical_output_purpose(::particle * pparticle) override;
      bool does_particle_has_fps_purpose(const ::particle * pparticle) const override;
      //::graphics::enum_output_purpose most_demanding_graphical_output_purpose() const override;
      bool has_screen_output_purpose() const override;
      bool has_graphical_output_purpose() const override;
      bool has_fps_output_purpose() const override;

      //void fps_interest_stop() override;


      //virtual ::user::interaction * get_owner();
      ::user::interaction_base * set_owner(::user::interaction_base * pprimitiveOwner) override;

      bool has_pending_redraw_flags() override;

      virtual ::windowing::window * from_os_data(void * pdata);
      virtual void * get_os_data() const;

      //bool attach(::windowing::window * pwindow_New) override;
      //oswindow detach() override;

      virtual void destroy() override;

      void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;

      DECLARE_MESSAGE_HANDLER(_002OnDraw);

      DECLARE_MESSAGE_HANDLER(on_message_kill_focus);
      DECLARE_MESSAGE_HANDLER(on_prio_message_set_focus);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);
      //DECLARE_MESSAGE_HANDLER(_001OnApplyVisual);


      void on_configure(const ::int_rectangle & rectangle) override;
      virtual void _on_configure(const ::int_rectangle & rectangle);


      DECLARE_MESSAGE_HANDLER(on_message_reposition);
      DECLARE_MESSAGE_HANDLER(on_message_size);
      DECLARE_MESSAGE_HANDLER(_001OnDestroyWindow);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      //DECLARE_MESSAGE_HANDLER(_001OnRedraw);
      //DECLARE_MESSAGE_HANDLER(_001OnDoShowWindow);


//#if (WINVER >= 0x0500) && defined(WINDOWS_DESKTOP)
//
//      bool GetWindowInfo(PWINDOWINFO pwi) const;
//      bool GetTitleBarInfo(PTITLEBARINFO pti) const;
//
//#endif   // WINVER >= 0x0500

      // subclassing/unsubclassing functions
      void pre_subclass_window() override;
      //virtual bool subclass_window(::windowing::window * pwindow) override;
      //virtual bool SubclassDlgItem(unsigned int nID, ::windowing::window * pParent);
      //virtual oswindow unsubclass_window() override;

      // handling of RT_DLGINIT resource (extension to RT_DIALOG)
      //virtual bool ExecuteDlgInit(const ::string & pszResourceName);

      //virtual bool ExecuteDlgInit(void * pResource);





      //using ::user::interaction_base::create_interaction;
      //using ::user::interaction_base::create_window_ex;


      // for child windows, views, panes etc
      //virtual bool create_interaction(::user::interaction * pinteraction, unsigned int uExStyle, unsigned int uStyle, const ::int_rectangle & rectangle, ::user::interaction_base * puiParent, ::request * prequest = nullptr) override;


      // advanced creation (allows access to extended styles)
      //virtual bool create_window_ex(::user::interaction * pinteraction, ::pointer<::user::system>pcs, ::user::interaction_base * puiParent, atom atom) override;

      //virtual bool create_interaction() override;


      //virtual bool _native_create_window(::user::interaction * pinteraction, ::windowing::window * pwindow);

      
      //virtual bool _native_create_window_ex(::pointer<::user::system>pusersystem);

      //virtual bool _native_create_window_ex(::pointer<::user::system>pusersystem);

      //virtual bool create_host();

      //virtual void operating_system_create_host(::enum_parallelization eparrallelization);

      virtual void operating_system_create_host();

      //virtual void _create_window(::enum_parallelization eparrallelization);
      virtual void _create_window();

      virtual void native_create_host_alternate();


      void destroy_impl_only() override;
      void start_destroying_window() override;
      void destroy_window() override;

      // special pre-creation and interaction_impl int_rectangle adjustment hooks
      virtual bool pre_create_window(::user::system * pusersystem);

      // Advanced: virtual AdjustWindowRect
//      enum AdjustType { adjustBorder = 0,adjustOutside = 1 };
      //virtual void CalcWindowRect(::int_rectangle * pClientRect,unsigned int nAdjustType = adjustBorder) override;

      inline ::windowing::window * window() const { return m_pwindow; }
      inline ::windowing::windowing * windowing() const { return m_pwindowing; }



      bool _is_window() override;

#if(WINVER >= 0x0500)

      virtual ::windowing::window* GetAncestor(unsigned int gaFlags) const;

#endif   // WINVER >= 0x0500

      lresult send_message(const ::atom& atom, ::wparam wParam = 0, ::lparam lParam = 0, const ::int_point & point = {}) override;

      lresult send_message(::message::message * pmessage) override;


//#ifdef LINUX
//
//      virtual lresult send_x11_event(void * phappening) override; // XEvent *
//
//#endif


      void post_message(const ::atom & atom,wparam wParam = 0,lparam lParam = 0) override;


      //virtual bool SendNotifyMessage(unsigned int message,wparam wParam,lparam lParam);

      //virtual bool SendChildNotifyLastMsg(lresult* pResult = nullptr);

      //virtual bool DragDetect(const ::int_point & point) const;



      // Window Text Functions
      //virtual void set_window_text(const ::string & pszString) override;

      void on_set_window_text() override;

      //character_count get_window_text(char * pszStringBuf, character_count nMaxCount) override;

      //void get_window_text(string & rString) override;
      //character_count get_window_text_length() override;


      // Window int_size and position Functions
      virtual bool window_is_iconic();
      virtual bool window_is_zoomed();
      //virtual int SetWindowRgn(HRGN hRgn,bool bRedraw);
      //virtual int GetWindowRgn(HRGN hRgn);

      //using ::user::interaction_base::set_window_position;
      //virtual bool set_window_position(class zorder zorder, int x, int y, int cx,int cy, unsigned int nFlags = SWP_SHOWWINDOW) override;
      virtual unsigned int ArrangeIconicWindows() override;
      //virtual bool BringWindowToTop() override;

//#ifdef WINDOWS_DESKTOP
//      virtual bool GetWindowPlacement(WINDOWPLACEMENT* puserinteractionpl);
//
//      virtual bool SetWindowPlacement(const WINDOWPLACEMENT* puserinteractionpl);
//
//#endif

      // Coordinate Mapping Functions
      virtual void MapWindowPoints(::windowing::window* puserinteractionTo,::int_point * pPoint,unsigned int nCount);

      virtual void MapWindowPoints(::windowing::window* puserinteractionTo,::int_rectangle * prectangle);


      virtual void Print(::draw2d::graphics_pointer & pgraphics,unsigned int dwFlags) const;
      virtual void PrintClient(::draw2d::graphics_pointer & pgraphics,unsigned int dwFlags) const;

      //void UpdateWindow() override;
      //void SetRedraw(bool bRedraw = true) override;
      ////virtual bool GetUpdateRect(::int_rectangle * prectangle,bool bErase = false) override;

      ////int GetUpdateRgn(::draw2d::region* pRgn,bool bErase = false) override;
      //virtual void Invalidate(bool bErase = true) override;
      //void InvalidateRect(const ::int_rectangle & rectangle,bool bErase = true) override;

      //void InvalidateRgn(::draw2d::region* pRgn,bool bErase = true) override;
      //void ValidateRect(const ::int_rectangle & rectangle) override;

      //void ValidateRgn(::draw2d::region* pRgn) override;
      ////virtual bool display(::e_display edisplay) override;
      ////virtual bool _is_window_visible() override;
      //void ShowOwnedPopups(bool bShow = true) override;

      //virtual ::pointer<::draw2d::graphics>GetDCEx(::draw2d::region* prgnClip,unsigned int flags);
      virtual void LockWindowUpdate();
      virtual void UnlockWindowUpdate();


      // try calling prodevian things from prodevian... he is not much called...
      //void graphics_thread_update_screen() override;

      // try calling prodevian things from prodevian... is he ever called...
      //void graphics_thread_redraw(bool bUpdateBuffer) override;

//#ifdef WINDOWS
//
//      virtual bool RedrawWindow(const ::int_rectangle & rectangleUpdate = nullptr, ::draw2d::region* prgnUpdate = nullptr,unsigned int flags = RDW_INVALIDATE | RDW_ERASE);
//
//#else

      void RedrawWindow(const ::int_rectangle & rectangleUpdate = {}, ::draw2d::region* prgnUpdate = nullptr,unsigned int flags = 0) override;

//#endif


//#ifdef WINDOWS_DESKTOP
//
//      virtual bool EnableScrollBar(int nSBFlags,unsigned int nArrowFlags = ESB_ENABLE_BOTH);
//
//#else

      //virtual void EnableScrollBar(int nSBFlags,unsigned int nArrowFlags = 3);

//#endif


      //virtual ::int_point get_cursor_position() const override;

      void set_mouse_cursor(::windowing::cursor * pcursor) override;

      //virtual void set_cursor(enum_cursor ecursor) override;

      //virtual bool DrawCaption(::draw2d::graphics_pointer & pgraphics,const int_rectangle & prc,unsigned int uFlags);


//#if(WINVER >= 0x0500)
//
//      virtual bool AnimateWindow(const class time & time,unsigned int dwFlags);
//
//#endif


//#if(_WIN32_WINNT >= 0x0501)
//
//      virtual bool PrintWindow(::draw2d::graphics_pointer & pgraphics,unsigned int nFlags) const;
//
//#endif


//#if(_WIN32_WINNT >= 0x0500)
//
//      virtual bool SetLayeredWindowAttributes(::color::color crKey,unsigned char bAlpha,unsigned int dwFlags);
//      virtual bool UpdateLayeredWindow(::draw2d::graphics * pDCDst,::int_point *pptDst,::int_size *psize,::draw2d::graphics * pDCSrc,::int_point *pptSrc,::color::color crKey,BLENDFUNCTION *pblend,unsigned int dwFlags);
//
//#endif   // _WIN32_WINNT >= 0x0500

//#if(_WIN32_WINNT >= 0x0501)
//
//      virtual bool GetLayeredWindowAttributes(::color::color *pcrKey,unsigned char *pbAlpha,unsigned int *pdwFlags) const;
//
//#endif   // _WIN32_WINNT >= 0x0501
//


      //virtual bool is_window_enabled() const override;
      void enable_window(bool bEnable = true) override;


      


      //virtual void CheckDlgButton(int nIDButton,unsigned int nCheck);
      //virtual void CheckRadioButton(int nIDFirstButton,int nIDLastButton,
      //                              int nIDCheckButton);
      //virtual int GetCheckedRadioButton(int nIDFirstButton,int nIDLastButton);
      //virtual int DlgDirList(char * pPathSpec,int nIDListBox,

      //                       int nIDStaticPath,unsigned int nFileType);
      //virtual int DlgDirListComboBox(char * pPathSpec,int nIDComboBox,

      //                               int nIDStaticPath,unsigned int nFileType);
      //virtual bool DlgDirSelect(char * pString,int nSize,int nIDListBox);

      //virtual bool DlgDirSelectComboBox(char * pString,int nSize,int nIDComboBox);


      //virtual unsigned int GetChildByIdInt(int nID,bool* pTrans = nullptr,bool bSigned = true) const;

      //virtual int GetChildByIdText(int nID,char * pStr,int nMaxCount) const;

      //virtual int GetChildByIdText(int nID,string & rString) const;
      //virtual ::windowing::window * GetNextDlgGroupItem(::windowing::window * pWndCtl,bool bPrevious = false) const;
      //virtual ::windowing::window * GetNextDlgTabItem(::windowing::window * pWndCtl,bool bPrevious = false) const;
      //virtual unsigned int IsDlgButtonChecked(int nIDButton) const;
      //virtual lresult SendDlgItemMessage(int nID,unsigned int message,wparam wParam = 0,lparam lParam = 0);
      //virtual void SetDlgItemInt(int nID,unsigned int nValue,bool bSigned = true);
      //virtual void SetDlgItemText(int nID, const ::string & pszString);


      //virtual int GetScrollPos(int nBar) const;
      //virtual void GetScrollRange(int nBar, int * pMinPos, int * lpMaxPos) const;
      //virtual void ScrollWindow(int xAmount,int yAmount,
      //   const ::int_rectangle * rectangle = nullptr,
      //   const ::int_rectangle * pClipRect = nullptr);

      //virtual int SetScrollPos(int nBar,int nPos,bool bRedraw = true);
      //virtual void SetScrollRange(int nBar, int nMinPos, int nMaxPos, bool bRedraw = true);
      //virtual void ShowScrollBar(unsigned int nBar,bool bShow = true);
      //virtual void EnableScrollBarCtrl(int nBar,bool bEnable = true);

      //virtual int ScrollWindowEx(int Δx,int Δy, const ::int_rectangle * prectScroll, const ::int_rectangle * lprectClip, ::draw2d::region* prgnUpdate, ::int_rectangle * prectUpdate, unsigned int flags);


//#ifdef WINDOWS_DESKTOP
//
//      virtual bool SetScrollInfo(int nBar, LPSCROLLINFO pScrollInfo, bool bRedraw = true);
//      virtual bool GetScrollInfo(int nBar, LPSCROLLINFO pScrollInfo, unsigned int nMask = SIF_ALL);
//
//#endif


      //virtual int GetScrollLimit(int nBar);

//#if (WINVER >= 0x0500) && defined(WINDOWS_DESKTOP)
//
//      virtual bool GetScrollBarInfo(int idObject,PSCROLLBARINFO psbi) const;
//
//#endif   // WINVER >= 0x0500

      virtual ::user::interaction * ChildWindowFromPoint(const ::int_point & point) override;
      virtual ::user::interaction * ChildWindowFromPoint(const ::int_point & point,unsigned int nFlags) override;

//#ifdef WINDOWS_DESKTOP
  //    virtual ::user::interaction * get_next_window(unsigned int nFlag = GW_HWNDNEXT);
//#else
//      virtual ::user::interaction * get_next_window(unsigned int nFlag = 0) override;
//#endif



      virtual ::user::interaction * GetTopWindow();

      virtual ::user::interaction * GetLastActivePopup() override;

      //bool FlashWindow(bool bInvert);

      //virtual int message_box(const ::string & pszText, const ::string & pszCaption = nullptr,unsigned int nType = e_message_box_ok);


//#if(WINVER >= 0x0500)
//
//      // virtual bool FlashWindowEx(unsigned int dwFlags, unsigned int  uCount, class ::time tickTimeout);
//
//#endif   // WINVER >= 0x0500

      //virtual bool ChangeClipboardChain(::windowing::window * pwindow_Next);
      //virtual oswindow SetClipboardImpacter();
      //virtual bool OpenClipboard();

      virtual void HideCaret();
      virtual void ShowCaret();

      virtual void DragAcceptFiles(bool bAccept = true);

      //virtual bool SetWindowContextHelpId(unsigned int dwContextHelpId);
      //virtual unsigned int GetWindowContextHelpId() const;


      void update_data(bool bSaveAndValidate = true) override;


      void UpdateDialogControls(channel* pTarget,bool bDisableIfNoHndler);
      void CenterWindow(::user::interaction * pAlternateOwner = nullptr) override;


      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_pos_create);
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


      virtual bool HandleFloatingSysCommand(unsigned int nID,lparam lParam);
      bool IsTopParentActive() override;
      void ActivateTopParent() override;
      virtual void on_final_release();


      //virtual bool _EnableToolTips(bool bEnable,unsigned int nFlag);
      //virtual void PrepareForHelp();


      // for creating dialogs and dialog-like windows
      //virtual bool CreateDlg(const ::string & pszTemplateName, ::windowing::window * puiParent);

      //virtual bool CreateDlgIndirect(LPCDLGTEMPLATE pDialogTemplate, ::windowing::window * puiParent,

      // HINSTANCE hInst);



      //// standard message implementation
      //lresult OnNTCtlColor(wparam wParam,lparam lParam);
      //lresult OnDisplayChange(wparam,lparam);
      //lresult OnDragList(wparam,lparam);

      virtual void _001DeferPaintLayeredWindowBackground(::image::image *pimage);

      virtual void _001OnDeferPaintLayeredWindowBackground(::image::image *pimage);

      //virtual int get_window_long(int nIndex) const override;
      //virtual int set_window_long(int nIndex,int lValue) override;
      //virtual iptr get_window_long_ptr(int nIndex) const override;
      //virtual iptr set_window_long_ptr(int nIndex, iptr lValue) override;

      virtual interaction_impl * get_impl() const;

      virtual void _001UpdateWindow() override;


      // deprecated schedule window visual
      //virtual void start_window_visual() override;
      //virtual void sketch_to_design(::draw2d::graphics_pointer& pgraphics, bool & bUpdateBuffer, bool & bUpdateWindow) override;
      virtual void do_graphics();
      void _001OnNcClip(::draw2d::graphics_pointer & pgraphics) override;
      void defer_do_graphics(::draw2d::graphics_pointer & pgraphics) override;
      //void _000CallOnDraw(::draw2d::graphics_pointer & pgraphics) override;
      // call window window_update_screen_buffer
      //virtual void _001UpdateScreen();
      //virtual void window_apply_visual(const window_state & windowstate) override;


      //virtual void update_graphics_resources();


      //virtual void set_handle(::windowing::window * pwindow);
      
      
      ::oswindow oswindow() const;


      ::graphics::graphics * get_window_graphics() override;

      
      bool is_composite() override;


      virtual void set_finish(::particle * pparticle);


      void top_down_prefix() override;

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      virtual void on_start_layout_experience(enum_layout_experience elayoutexperience) override;

      virtual void on_configuration_change(::user::interaction_base * pprimitiveSource) override;

      ::user::element * get_keyboard_focus() override;
      //virtual void set_keyboard_focus(::user::interaction_base * pprimitive) override;
      //virtual void erase_keyboard_focus(::user::interaction_base * pprimitive) override;
      void clear_keyboard_focus(::user::primitive_impl* pprimitiveimplGainingFocusIfAny = nullptr) override;
      //virtual void impl_set_keyboard_focus(::user::interaction_base * pprimitive) override;
      //virtual void impl_erase_keyboard_focus(::user::interaction_base * pprimitive) override;
      //virtual void impl_clear_keyboard_focus() override;

      virtual void redraw_add(::particle * pparticle) override;
      virtual void redraw_erase(::particle * pparticle) override;
      virtual bool has_redraw() override;
      virtual ::particle * mutex_redraw();

      //virtual void _001OnTriggerMouseInside() override;

      bool has_pending_graphical_update() override;

      virtual void on_after_graphical_update() override;

      //virtual bool is_this_visible(enum_layout elayout) override;

      //void _window_show_change_visibility_unlocked(::e_display edisplay, const ::user::activation & useractivation) override;
      
      //void _window_request_presentation_locked() override;
      //void _window_request_presentation_unlocked() override;




      virtual void ShowWindow(const ::e_display & edisplay);

      //virtual bool check_need_layout() override;
//virtual void clear_need_layout() override;
      virtual void set_need_layout() override;

      //virtual bool window_move(int x, int y) override;

      //virtual bool check_show_flags() override;

      //virtual void on_visual_applied();

      void set_need_redraw(const ::int_rectangle_array & rectangleaHostNeedRedraw = {}, function<void()> function = nullptr,  bool bAscendants = true) override;
      //virtual bool needs_to_draw(const ::int_rectangle& rectangleHostNeedsToDraw, ::draw2d::graphics_pointer & pgraphics);
      void post_redraw(bool bAscendants = true) override;


      virtual void user_interaction_on_hide() override;

      void show_software_keyboard(::user::element * pelement) override;

      void hide_software_keyboard(::user::element * pelement) override;


      // Occlusion and Translucency
      virtual bool is_occluded();
      virtual huge_integer approximate_occlusion_area();
      virtual double approximate_occlusion_rate();
      virtual huge_integer approximate_occlusion_area_except_self_transparent();
      virtual double approximate_occlusion_rate_except_self_transparent();
      virtual huge_integer _001GetTopLeftWeightedOccludedOpaqueArea();
      virtual double _001GetTopLeftWeightedOccludedOpaqueRate() override;
      virtual huge_integer _001GetTopLeftWeightedArea();
      virtual huge_integer _001GetRectTopLeftWeightedArea(const ::int_rectangle &rect);

      virtual huge_integer opaque_area(const ::int_rectangle &rect);
      virtual void approximate_occlusion_rects(int_rectangle_array& raTest);

      virtual huge_integer opaque_area();

      /// from top to bottom
      virtual void non_top_most_upper_window_rects(::int_rectangle_array& recta);


      virtual void android_fill_plasma(const void * pixels, int width, int height, int stride, huge_integer time_ms);

      void set_opacity(double dOpacity) override;




   };


   class CLASS_DECL_AURA guie_message_wnd:
      virtual public interaction_impl
   {
   public:


      ::user::interaction * m_puiForward;


      guie_message_wnd(::property_object * pparticle);


      virtual void message_handler(::message::message * pmessage);


   }; // guie_message_wnd


   class device_draw_life_time
   {
   public:


      ::windowing::window * m_pimpl;

      
      device_draw_life_time(::windowing::window * pimpl) :
         m_pimpl(pimpl)
      {

         m_pimpl->m_timeDeviceDrawBeg.Now();

      }

      
      ~device_draw_life_time()
      {

         m_pimpl->m_timeDeviceDrawEnd.Now();

      }


   };


} // namespace user


CLASS_DECL_AURA ::user::interaction * __interaction(::windowing::window * pwindow);



