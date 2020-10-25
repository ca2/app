#pragma once


namespace user
{


   class CLASS_DECL_AURA interaction_child :
      virtual public ::user::primitive_impl
   {
   public:


      // interaction_impl rectangle relative to the parent
      // this rectangle comes before in importance compared to m_rectWindow
      // m_rectWindow should be sychronized and recalculated based
      // on m_rectParentClient values of the interaction_impl and its ascendants.
      size                                m_size;
      bool                                m_bCreate;
      __pointer(::user::interaction)      m_puiMessage;
      interaction *                       m_puiOwner;
      ::mutex                             m_mutexLongPtr;
      int_ptr_to_int_ptr                  m_longptr;
      uptr                                m_uStyle;
      uptr                                m_uExStyle;


      interaction_child();
      virtual ~interaction_child();

      ::user::interaction_child * get_user_interaction_child() override;

      virtual void message_handler(::message::base * pbase) override;

      //using ::user::primitive::set_window_pos;
      //virtual bool set_window_pos(iptr z,i32 x,i32 y,i32 cx,i32 cy,UINT nFlags = SWP_SHOWWINDOW) override;


      // Advanced: virtual AdjustWindowRect
      enum AdjustType { adjustBorder = 0,adjustOutside = 1 };
      virtual void CalcWindowRect(RECT * pClientRect,UINT nAdjustType = adjustBorder) override;

      virtual bool start_window_visual() override;

      virtual bool SetFocus() override;

      virtual bool has_focus() override;
      virtual bool is_active() override;


      virtual bool DestroyWindow() override;

      virtual u32 GetStyle() const override;
      virtual u32 GetExStyle() const override;


      //virtual LRESULT default_window_procedure() override;


#ifdef LINUX

      virtual LRESULT send_x11_event(void * pevent) override; // XEvent *

#endif


      virtual void rects_from_system();


      // as hosting interaction_impl
      virtual void install_message_routing(::channel * pchannel) override;
      // as virtual interaction_impl
      virtual void _002InstallMessageHandling(::channel * pchannel);


      virtual bool create_window(::user::interaction * pinteraction, const ::rect & rect, ::user::interaction * pparent, id id) override;
      virtual bool create_window(::user::interaction * pinteraction, const char * pszClassName, const char * pszWindowName, u32 uStyle, const ::rect & rect, ::user::interaction * puiParent, id id, ::create * pContext = nullptr) override;

      virtual bool create_window_ex(::user::interaction * pinteraction, ::user::create_struct & cs, ::user::interaction * puiParent, id id) override;


      virtual LONG_PTR get_window_long_ptr(i32 nIndex) const override;
      virtual LONG_PTR set_window_long_ptr(i32 nIndex, LONG_PTR lValue) override;


      virtual bool is_this_visible(e_layout elayout) override;

      virtual void window_show_change_visibility(::edisplay edisplay, ::eactivation eactivation) override;

      virtual bool _is_window() const override;

      virtual void VirtualOnSize();



      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnShowWindow);

      void send_message_to_descendants(const ::id & id,WPARAM wParam = 0,lparam lParam = 0,bool bDeep = true,bool bOnlyPerm = 0) override;

      //virtual bool post_message(const ::id & id,WPARAM wparam,lparam lparam) override;

      virtual void set_viewport_org(::draw2d::graphics_pointer & pgraphics) override;

      virtual bool RedrawWindow(const ::rect& rectUpdate,::draw2d::region* prgnUpdate,UINT flags) override;

      virtual ::user::interaction * SetOwner(::user::interaction * pinteraction) override;
      virtual ::user::interaction * GetOwner() const override;

      //bool _get_client_rect(RECT64 * prect) override;
      //bool _get_window_rect(RECT64 * prect) override;

      //virtual point client_screen_top_left() override;

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

      //virtual bool _001ScreenToClient(POINT64 * ppoint) override;


      virtual bool keyboard_focus_OnKillFocus(oswindow oswindowNew) override;


   };


} // namespace user



