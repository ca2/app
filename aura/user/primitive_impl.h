#pragma once


namespace user
{


   class CLASS_DECL_AURA primitive_impl :
      virtual public ::user::primitive
   {
   public:


      ::user::interaction_impl *                m_pinteractionimpl;
      ::user::interaction_child *               m_pinteractionchild;


      iptr_to_iptr                              m_iptrmap;

      bool                                      m_bDrawFlagsReady;
      bool                                      m_bDestroyImplOnly;
      bool                                      m_bDestroying;
      int                                       m_iPendingRectMatch;
      __pointer(::user::interaction)            m_puserinteraction;
      __pointer(::user::box)                    m_puserbox;
      bool                                      m_bIgnoreSizeEvent;
      bool                                      m_bIgnoreMoveEvent;
      ap(critical_section)                      m_pcsDisplay;

      __composite(::apex::timer_array)          m_ptimerarray;

      const char *                              m_pszInteractionImplBaseDebug;

      bool                                      m_bPendingRedraw;
      u32                                       m_uiLastRedraw;
      bool                                      m_bUpdatingBuffer;

      ::rectangle_i32                                    m_rectangle;



      primitive_impl();
      virtual ~primitive_impl();

      inline critical_section * cs_display() { return m_pcsDisplay; }
      virtual ::user::interaction_impl * get_user_interaction_impl();
      virtual ::user::interaction_child * get_user_interaction_child();


      virtual void prio_install_message_routing(::channel * pchannel);
      virtual void last_install_message_routing(::channel * pchannel);


      virtual void queue_message_handler(::message::message * pmessage);


      virtual bool enable_window(bool bEnable = true) override;




      virtual bool create_host(::user::interaction * puserinteraction);
      virtual bool create_child(::user::interaction * puserinteraction, ::user::primitive * puserprimitiveParent);


      //virtual bool check_need_layout();
      //virtual void clear_need_layout();
      virtual void set_need_layout();
      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;
      virtual void on_reposition() override;
      virtual void on_show_window() override;

      virtual void finalize() override;

      virtual void window_show_change_visibility(::e_display edisplay, ::e_activation eactivation);


      virtual bool start_window_visual();

      virtual bool create_message_queue(::user::interaction * pinteraction, const char * lpszName);
      
      virtual bool prodevian_update_screen();

      virtual void RepositionBars(::u32 nIDFirst, ::u32 nIDLast, ::id nIdLeftOver, ::u32 nFlag = reposDefault, RECTANGLE_I32 * prectParam = nullptr, const ::rectangle_i32 & rectClient = nullptr, bool bStretch = true) override;

      virtual bool window_move(i32 x, i32 y);


      virtual bool RedrawWindow(const ::rectangle_i32& rectUpdate = nullptr,::draw2d::region* prgnUpdate = nullptr,::u32 flags = 0) override;

      virtual void _001Print(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _000OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001DrawThis(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001DrawChildren(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void draw_control_background(::draw2d::graphics_pointer & pgraphics) override;


      virtual ::user::interaction * get_wnd() const override;


      virtual void set_viewport_org(::draw2d::graphics_pointer & pgraphics) override;

      virtual void viewport_screen_to_client(POINT_I32 * ppt) override;
      virtual void viewport_client_to_screen(POINT_I32 * ppt) override;
      virtual void viewport_client_to_screen(RECTANGLE_I32 * ppt) override;
      virtual void viewport_screen_to_client(RECTANGLE_I32 * ppt) override;




      //virtual u32 GetStyle() const override;
      //virtual u32 GetExStyle() const override;
      //virtual bool ModifyStyle(u32 dwRemove,u32 dwAdd,::u32 nFlags = 0) override;
      //virtual bool ModifyStyleEx(u32 dwRemove,u32 dwAdd,::u32 nFlags = 0) override;

      //virtual ::i32 get_window_long(i32 nIndex) const override;
      //virtual ::i32 set_window_long(i32 nIndex,::i32 lValue) override;

      //virtual iptr get_window_long_ptr(i32 nIndex) const override;
      //virtual ::e_status set_window_long_ptr(i32 nIndex, iptr lValue) override;

      virtual id GetDlgCtrlId() const override;
      virtual id SetDlgCtrlId(::id id) override;

      virtual ::user::interaction * first_child() override;
      virtual ::user::interaction * top_child() override;
      virtual ::user::interaction * under_sibling() override;
      virtual ::user::interaction * above_sibling() override;

      virtual ::user::interaction * above_sibling(::user::interaction * pinteraction) override;
      virtual ::user::interaction * under_sibling(::user::interaction * pinteraction) override;


      virtual ::u32 ArrangeIconicWindows();
      //virtual void BringToTop(edisplay edisplay) override;
      //virtual bool BringWindowToTop() override;


      virtual bool is_ascendant(const ::user::primitive * puiIsAscendant, bool bIncludeSelf) const override;
      virtual bool is_parent(const ::user::primitive * puiIsParent) const override;
      virtual bool is_child(const ::user::primitive * puiIsChild) const override;
      virtual bool is_descendant(const ::user::primitive * puiIsDescendant, bool bIncludeSelf) const override;


//      virtual ::user::interaction * get_wnd() const;
      virtual ::user::interaction * get_wnd(::u32 nCmd) const override;


      virtual ::user::frame * frame() const override;
      virtual ::user::frame * top_level_frame() const override;


      //virtual ::user::interaction * GetTopWindow() const override;
      virtual ::user::interaction * get_parent() const override;
      virtual ::user::interaction * get_top_level() const override;
      //virtual ::user::interaction * GetParentTopLevel() const override;
      //virtual ::user::interaction * EnsureTopLevel() override;
      //virtual ::user::interaction * EnsureParentTopLevel() override;
      virtual ::user::interaction * get_owner() const override;
      virtual ::user::interaction * get_parent_owner() const override;
      virtual ::user::interaction * get_parent_or_owner() const override;
      virtual ::user::interaction * get_top_level_owner() const override;
      virtual ::user::frame * get_parent_frame() const override;
      //virtual ::user::frame * GetParentTopLevelFrame() const override;
      //virtual ::user::frame * EnsureParentFrame() override;


      virtual lresult message_call(const ::id & id, wparam wparam, lparam lparam) override;
      virtual lresult message_call(::message::message * pmessage) override;



      virtual void send_message_to_descendants(const ::id & id, wparam wParam = 0,lparam lParam = 0,bool bDeep = true,bool bOnlyPerm = false) override;



      virtual void pre_translate_message(::message::message * pmessage) override;


      //virtual bool is_active() const override;

      //virtual bool has_capture() const override;
      //virtual bool set_capture(::user::interaction * pinteraction = nullptr) override;
      //virtual ::user::interaction * get_capture() const override;

      //virtual bool has_keyboard_focus() const override;
      //virtual bool set_keyboard_focus(::user::interaction * pinteraction = nullptr) override;
      //virtual ::user::interaction * get_keyboard_focus() const override;




      virtual bool get_rect_normal(RECTANGLE_I32 * prectangle);


      virtual bool SetTimer(uptr uEvent, ::millis millisElapse, PFN_TIMER pfnTimer = nullptr) override;
      virtual bool KillTimer(uptr uEvent) override;

      virtual void _001OnTimer(::timer * ptimer) override;

      virtual bool destroy_impl_only();
      virtual bool DestroyWindow() override;


      //virtual void defer_start_prodevian();
      //virtual void _defer_start_prodevian();


      void mouse_hover_add(::user::interaction * pinterface) override;
      bool mouse_hover_remove(::user::interaction * pinterface) override;


      virtual void register_drop_target();


      virtual ::user::primitive * get_keyboard_focus();
      virtual ::e_status set_keyboard_focus(::user::primitive * pprimitive);
      virtual ::e_status remove_keyboard_focus(::user::primitive * pprimitive);
      virtual ::e_status clear_keyboard_focus() override;
      virtual ::e_status impl_set_keyboard_focus(::user::primitive * pprimitive);
      virtual ::e_status impl_remove_keyboard_focus(::user::primitive * pprimitive);
      virtual ::e_status impl_clear_keyboard_focus();


      virtual bool post_message(const ::id & id, wparam wparam = 0, lparam lparam = 0) override;

      virtual void PostNcDestroy() override;

      //virtual bool display(::display edisplay) override;

      DECL_GEN_SIGNAL(_001OnPrioCreate);
      DECL_GEN_SIGNAL(_001OnShowWindow);
      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnNcDestroy);

      virtual void show_task(bool bShow);

      virtual void redraw_add(::context_object * point_i32);
      virtual void redraw_remove(::context_object * point_i32);
      virtual bool has_redraw();

      virtual ::e_status show_software_keyboard(::user::primitive * pprimitive, string str, strsize iBeg, strsize iEnd) override;
      virtual ::e_status hide_software_keyboard(::user::primitive * pprimitive) override;

      virtual void user_interaction_on_hide();


   };


} // namespace user



















