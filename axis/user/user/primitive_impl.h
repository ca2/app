#pragma once


namespace user
{


   class CLASS_DECL_AURA primitive_impl :
      virtual public ::user::primitive
   {
   public:


      ::user::interaction_impl *          m_pinteractionimpl;
      ::user::interaction_child *         m_pinteractionchild;
      __reference(::thread)               m_pthreadUserImpl;

      bool                                m_bDrawFlagsReady;
      bool                                m_bDestroyImplOnly;
      bool                                m_bDestroying;
      int                                 m_iPendingRectMatch;
      __pointer(::user::interaction)      m_puserinteraction;
      bool                                m_bIgnoreSizeEvent;
      bool                                m_bIgnoreMoveEvent;
      ap(critical_section)                m_pcsDisplay;

      __pointer(::aura::timer_array)      m_ptimerarray;

      ::mutex                             m_mutexLongPtr;
      int_ptr_to_int_ptr                  m_longptr;
      uptr                                m_uStyle;
      uptr                                m_uExStyle;
      const char *                        m_pszInteractionImplBaseDebug;

      bool                                m_bPendingRedraw;
      u32                                 m_uiLastRedraw;
      bool                                m_bUpdatingBuffer;



      primitive_impl();
      virtual ~primitive_impl();

      inline critical_section * cs_display() { return m_pcsDisplay; }
      virtual ::user::interaction_impl * get_user_interaction_impl();
      virtual ::user::interaction_child * get_user_interaction_child();


      virtual void prio_install_message_routing(::channel * pchannel);
      virtual void last_install_message_routing(::channel * pchannel);


      virtual void queue_message_handler(::message::base * pbase);


      virtual bool enable_window(bool bEnable = true) override;


      virtual bool has_focus() override;
      virtual bool is_active() override;
      virtual bool is_this_enabled() const override;

      //virtual bool check_need_layout();
      //virtual void clear_need_layout();
      virtual void set_need_layout();
      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;
      virtual void on_reposition() override;
      virtual void on_show_window() override;

      //virtual void set_finish() override;

virtual bool setWMClass(const char * psz);
      virtual void finalize() override;

      virtual void _do_show_window() override;

      //virtual bool check_need_translation();
      //virtual void clear_need_translation();
      //virtual void on_reposition() override;

      //virtual bool check_show_flags();
      //virtual void clear_show_flags();
      //virtual void on_show_window() override;

      //virtual bool check_need_zorder();
      //virtual void clear_need_zorder();
      //virtual void on_zorder();


      //virtual bool has_pending_redraw_flags() override;

      virtual bool start_window_visual();

      virtual void SetWindowDisplayChanged() override;


      virtual bool create_message_queue(::user::interaction * pinteraction, const char * lpszName);
      virtual bool create_window(::user::interaction * pinteraction, const ::rect & rect, ::user::interaction *pparent, id id);
      virtual bool create_window(::user::interaction * pinteraction, const char * pszClassName, const char * pszWindowName, u32 uStyle, const ::rect & rect, ::user::interaction * puiParent, id id, ::create * pcreate = nullptr);

      virtual bool create_window_ex(::user::interaction * pinteraction, ::user::create_struct & cs, ::user::interaction * puiParent = nullptr, id id = ::id());




      virtual bool prodevian_update_screen();

      virtual void RepositionBars(UINT nIDFirst, UINT nIDLast, ::id nIdLeftOver, UINT nFlag = reposDefault, RECT * prectParam = nullptr, const ::rect & rectClient = nullptr, bool bStretch = true) override;

      virtual bool window_move(i32 x, i32 y);

      //virtual bool _get_client_rect(RECT64 * prect) override;
      //virtual bool _get_window_rect(RECT64 * prect) override;

      //virtual bool _001ClientToScreen(RECTD * prect) override;

      //virtual bool _001ClientToScreen(RECT * prect) override;

      //virtual bool _001ClientToScreen(RECT64 * prect) override;

      //virtual bool _001ClientToScreen(POINTD * ppoint) override;

      //virtual bool _001ClientToScreen(LPPOINT ppoint) override;

      //virtual bool _001ClientToScreen(POINT64 * ppoint) override;

      //virtual bool _001ScreenToClient(RECTD * prect) override;

      //virtual bool _001ScreenToClient(RECT * prect) override;

      //virtual bool _001ScreenToClient(RECT64 * prect) override;

      //virtual bool _001ScreenToClient(POINTD * ppoint) override;

      //virtual bool _001ScreenToClient(LPPOINT ppoint) override;

      //virtual bool _001ScreenToClient(POINT64 * prect) override;

      //svirtual bool SetPlacement(const ::rect & rect,UINT nFlags = SWP_SHOWWINDOW) override;
      //virtual bool place(const ::rect & rect) override;
      //virtual bool RepositionWindow(i32 x,i32 y,i32 cx,i32 cy,UINT nFlags = SWP_SHOWWINDOW) override;
      // virtual bool MoveWindow(i32 x, i32 y, UINT nFlags = SWP_SHOWWINDOW) override;
      //virtual bool move_to(const ::point & point) override;
      //virtual bool SizeWindow(i32 x,i32 y,UINT nFlags = SWP_SHOWWINDOW) override;
      //virtual bool SizeWindow(const size & sz,UINT nFlags = SWP_SHOWWINDOW) override;
      //virtual bool ResizeWindow(i32 cx,i32 cy,UINT nFlags = SWP_SHOWWINDOW) override;
      //virtual bool set_size(const size & sz) override;
      //virtual bool set_window_pos(class zorder zorder, const ::rect & rect, UINT nFlags = SWP_SHOWWINDOW) override;

      //virtual bool set_window_pos(class zorder zorder, i32 x, i32 y, i32 cx, i32 cy, UINT nFlags = SWP_SHOWWINDOW) override;
      //virtual bool set_window_pos(class zorder zorder, const point & point, const size & size, UINT nFlags = SWP_SHOWWINDOW);
      //virtual bool defer_set_window_pos(zorder zorder, const ::rect & rect, UINT nFlags) override; // only set_windows_pos if get_parent()->_001ScreenToClient(get_window_rect) different of rect(x, y, cx, cy)      virtual bool set_placement(RECT * prect);

      //virtual bool defer_set_window_pos(zorder zorder, i32 x,i32 y,i32 cx,i32 cy,UINT nFlags) override; // only set_windows_pos if get_parent()->_001ScreenToClient(get_window_rect) different of rect(x, y, cx, cy)      virtual bool set_placement(RECT * prect);

      //virtual i32 SetWindowRgn(HRGN hRgn,bool bRedraw);
      //virtual i32 GetWindowRgn(HRGN hRgn);


#ifdef WINDOWS

      virtual bool RedrawWindow(const ::rect& rectUpdate = nullptr,::draw2d::region* prgnUpdate = nullptr,UINT flags = RDW_INVALIDATE | RDW_ERASE) override;

#else

      virtual bool RedrawWindow(const ::rect& rectUpdate = nullptr,::draw2d::region* prgnUpdate = nullptr,UINT flags = 0) override;

#endif

      virtual void _001Print(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _000OnDraw1(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001DrawThis(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001DrawChildren(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void draw_control_background(::draw2d::graphics_pointer & pgraphics) override;


      virtual ::user::interaction * get_wnd() const override;


      virtual void set_viewport_org(::draw2d::graphics_pointer & pgraphics) override;

      virtual void viewport_screen_to_client(POINT * ppt) override;
      virtual void viewport_client_to_screen(POINT * ppt) override;
      virtual void viewport_client_to_screen(RECT * ppt) override;
      virtual void viewport_screen_to_client(RECT * ppt) override;




      virtual u32 GetStyle() const override;
      virtual u32 GetExStyle() const override;
      virtual bool ModifyStyle(u32 dwRemove,u32 dwAdd,UINT nFlags = 0) override;
      virtual bool ModifyStyleEx(u32 dwRemove,u32 dwAdd,UINT nFlags = 0) override;

      virtual LONG get_window_long(i32 nIndex) const override;
      virtual LONG set_window_long(i32 nIndex,LONG lValue) override;

      virtual LONG_PTR get_window_long_ptr(i32 nIndex) const override;
      virtual LONG_PTR set_window_long_ptr(i32 nIndex,LONG_PTR lValue) override;

      virtual id GetDlgCtrlId() const override;
      virtual id SetDlgCtrlId(::id id) override;

      virtual ::user::interaction * first_child() override;
      virtual ::user::interaction * top_child() override;
      virtual ::user::interaction * under_sibling() override;
      virtual ::user::interaction * above_sibling() override;

      virtual ::user::interaction * above_sibling(::user::interaction * pinteraction) override;
      virtual ::user::interaction * under_sibling(::user::interaction * pinteraction) override;


      virtual UINT ArrangeIconicWindows();
      //virtual void BringToTop(edisplay edisplay) override;
      //virtual bool BringWindowToTop() override;


      virtual bool is_ascendant(const ::user::primitive * puiIsAscendant) const override;
      virtual bool is_parent(const ::user::primitive * puiIsParent) const override;
      virtual bool is_child(const ::user::primitive * puiIsChild) const override;
      virtual bool is_descendant(const ::user::primitive * puiIsDescendant) const override;


//      virtual ::user::interaction * get_wnd() const;
      virtual ::user::interaction * get_wnd(UINT nCmd) const override;


      virtual ::user::interaction * GetTopWindow() const override;
      virtual ::user::interaction * GetParent() const override;
      virtual ::user::interaction * GetTopLevel() const override;
      virtual ::user::interaction * GetParentTopLevel() const override;
      virtual ::user::interaction * EnsureTopLevel() override;
      virtual ::user::interaction * EnsureParentTopLevel() override;
      virtual ::user::interaction * GetOwner() const override;
      virtual ::user::interaction * GetParentOwner() const override;
      virtual ::user::interaction * GetParentOrOwner() const override;
      virtual ::user::interaction * GetTopLevelOwner() const override;
      virtual ::user::frame * GetFrame() const override;
      virtual ::user::frame * GetParentFrame() const override;
      virtual ::user::frame * GetTopLevelFrame() const override;
      virtual ::user::frame * GetParentTopLevelFrame() const override;
      virtual ::user::frame * EnsureParentFrame() override;


      virtual LRESULT message_call(UINT uiMessage, WPARAM wparam, lparam lparam) override;
      virtual LRESULT message_call(::message::base * pbase) override;



      virtual void send_message_to_descendants(UINT message,WPARAM wParam = 0,lparam lParam = 0,bool bDeep = TRUE,bool bOnlyPerm = FALSE) override;



      virtual void pre_translate_message(::message::message * pmessage) override;


      virtual bool SetCapture(::user::interaction * pinteraction = nullptr) override;
      virtual bool ReleaseCapture() override;
      virtual ::user::interaction * GetCapture() override;


      virtual bool SetFocus() override;


      virtual bool get_rect_normal(RECT * prect);


      virtual bool SetTimer(uptr nIDEvent, UINT nElapse, PFN_TIMER pfnTimer = nullptr) override;
      virtual bool KillTimer(uptr nIDEvent) override;

      virtual void _001OnTimer(::timer * ptimer) override;

      virtual bool destroy_impl_only();
      virtual bool DestroyWindow() override;


      //virtual void defer_start_prodevian();
      //virtual void _defer_start_prodevian();


      void mouse_hover_add(::user::interaction * pinterface) override;
      bool mouse_hover_remove(::user::interaction * pinterface) override;


      virtual void register_drop_target();


      virtual ::user::primitive * get_focus_primitive();
      virtual bool set_focus_primitive(::user::primitive * pprimitive);

      virtual bool post_message(UINT uiMessage, WPARAM wparam = 0, lparam lparam = 0) override;

      virtual void PostNcDestroy() override;

      //virtual bool display(::display edisplay) override;

      DECL_GEN_SIGNAL(_001OnPrioCreate);
      DECL_GEN_SIGNAL(_001OnShowWindow);
      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnNcDestroy);

      virtual void show_task(bool bShow);

      virtual void redraw_add(::context_object * point);
      virtual void redraw_remove(::context_object * point);
      virtual bool has_redraw();

      virtual void show_software_keyboard(bool bShow, string str, strsize iBeg, strsize iEnd) override;

      virtual void user_interaction_on_hide();


   };


} // namespace user



















