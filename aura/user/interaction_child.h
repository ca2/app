#pragma once


namespace user
{


   class CLASS_DECL_AURA interaction_child :
      virtual public ::user::primitive_impl
   {
   public:


      // interaction_impl rectangle_i32 relative to the parent
      // this rectangle_i32 comes before in importance compared to m_rectangleWindow
      // m_rectangleWindow should be sychronized and recalculated based
      // on m_rectangleParentClient values of the interaction_impl and its ascendants.
      size_i32                                m_size;
      bool                                m_bCreate;
      __pointer(::user::interaction)      m_puserinteractionMessage;
      __pointer(primitive)                m_puserprimitiveOwner;
      ::mutex                             m_mutexLongPtr;
      //iptr_to_iptr                  m_longptr;
      uptr                                m_uStyle;
      uptr                                m_uExStyle;


      interaction_child();
      virtual ~interaction_child();

      ::user::interaction_child * get_user_interaction_child() override;

      virtual void message_handler(::message::message * pusermessage) override;

      //using ::user::primitive::set_window_position;
      //virtual bool set_window_position(iptr z,i32 x,i32 y,i32 cx,i32 cy,::u32 nFlags = SWP_SHOWWINDOW) override;


      // Advanced: virtual AdjustWindowRect
      //enum AdjustType { adjustBorder = 0,adjustOutside = 1 };
      //virtual void CalcWindowRect(RECTANGLE_I32 * pClientRect,::u32 nAdjustType = adjustBorder) override;

      void start_window_visual() override;

      //virtual bool is_active() const override;

      void start_destroying_window() override;

      void destroy_window() override;

      //virtual u32 GetStyle() const override;
      //virtual u32 GetExStyle() const override;


      //virtual lresult default_window_procedure() override;


//#ifdef LINUX
//
//      virtual lresult send_x11_event(void * pevent) override; // XEvent *
//
//#endif


      virtual void rects_from_system();


      // as hosting interaction_impl
      void install_message_routing(::channel * pchannel) override;
      // as virtual interaction_impl
      virtual void _002InstallMessageHandling(::channel * pchannel);


      virtual void __synthesizes_creates_styles(::user::interaction * pinteraction, ::u32 & nExStyle, ::u32 & nStyle);

      //virtual bool create_interaction(::user::interaction * pinteraction, const ::rectangle_i32 & rectangle, ::user::primitive * pparent, atom atom) override;
      //virtual bool create_interaction(::user::interaction * pinteraction, ::u32 uExStyle, u32 uStyle, const ::rectangle_i32 & rectangle, ::user::primitive * puiParent, ::create * pcreate = nullptr) override;

      
      void create_child(::user::interaction * pinteraction, ::user::primitive * pprimitiveParent) override;


      //virtual bool create_window_ex(::user::interaction * pinteraction, __pointer(::user::system) pcs, ::user::primitive * puiParent, atom atom) override;

      //virtual bool create_interaction() override;


      //virtual iptr get_window_long_ptr(i32 nIndex) const override;
      //virtual void set_window_long_ptr(i32 nIndex, iptr lValue) override;

      virtual bool is_this_visible(enum_layout elayout) override;

      virtual void window_show_change_visibility(::e_display edisplay, ::e_activation eactivation) override;

      virtual bool _is_window() const override;

      virtual void VirtualOnSize();



      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);

      void send_message_to_descendants(const ::atom & atom,wparam wParam = 0,lparam lParam = 0,bool bDeep = true,bool bOnlyPerm = 0) override;

      //virtual bool post_message(const ::atom & atom,wparam wparam,lparam lparam) override;

      void set_viewport_org(::draw2d::graphics_pointer & pgraphics) override;

      void RedrawWindow(const ::rectangle_i32& rectangleUpdate,::draw2d::region* prgnUpdate,::u32 flags) override;

      ::user::primitive * set_owner(::user::primitive * pinteraction) override;
      virtual ::user::interaction * get_owner() const override;

      //bool _get_client_rect(RECTANGLE_I64 * prectangle) override;
      //bool _get_window_rect(RECTANGLE_I64 * prectangle) override;

      //virtual point_i32 client_screen_top_left() override;

      //virtual bool client_to_screen(RECTANGLE_F64 * prectangle) override;

      //virtual bool client_to_screen(RECTANGLE_I32 * prectangle) override;

      //virtual bool client_to_screen(RECTANGLE_I64 * prectangle) override;

      //virtual bool client_to_screen(POINT_F64 * ppoint) override;

      //virtual bool client_to_screen(POINT_I32 * ppoint) override;

      //virtual bool client_to_screen(POINT_I64 * ppoint) override;

      //virtual bool screen_to_client(RECTANGLE_F64 * prectangle) override;

      //virtual bool screen_to_client(RECTANGLE_I32 * prectangle) override;

      //virtual bool screen_to_client(RECTANGLE_I64 * prectangle) override;

      //virtual bool screen_to_client(POINT_F64 * ppoint) override;

      //virtual bool screen_to_client(POINT_I32 * ppoint) override;

      //virtual bool screen_to_client(POINT_I64 * ppoint) override;


      virtual bool keyboard_focus_OnKillFocus(oswindow oswindowNew) override;


   };


} // namespace user



