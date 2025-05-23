#pragma once


#include "primitive_impl.h"


namespace user
{


   class CLASS_DECL_AURA interaction_child :
      virtual public ::user::primitive_impl
   {
   public:


      // interaction_impl int_rectangle relative to the parent
      // this int_rectangle comes before in importance compared to m_rectangleWindow
      // m_rectangleWindow should be sychronized and recalculated based
      // on m_rectangleParentClient values of the interaction_impl and its ascendants.
      int_size                            m_size;
      bool                                m_bCreate;
      ::pointer<::user::interaction>      m_puserinteractionMessage;
      ::pointer<::user::interaction_base>        m_puserprimitiveOwner;
      ::pointer < ::mutex >               m_pmutexLongPtr;
      //iptr_to_iptr                      m_longptr;
      uptr                                m_uStyle;
      uptr                                m_uExStyle;


      interaction_child();
      virtual ~interaction_child();

      ::user::interaction_child * get_user_interaction_child() override;

      virtual void message_handler(::message::message * pusermessage) override;

      //using ::user::interaction_base::set_window_position;
      //virtual bool set_window_position(iptr z,int x,int y,int cx,int cy,unsigned int nFlags = SWP_SHOWWINDOW) override;


      // Advanced: virtual AdjustWindowRect
      //enum AdjustType { adjustBorder = 0,adjustOutside = 1 };
      //virtual void CalcWindowRect(::int_rectangle * pClientRect,unsigned int nAdjustType = adjustBorder) override;



      //virtual bool is_active() const override;

      void start_destroying_window() override;

      void destroy_window() override;

      //virtual unsigned int GetStyle() const override;
      //virtual unsigned int GetExStyle() const override;


      //virtual lresult default_window_procedure() override;


//#ifdef LINUX
//
//      virtual lresult send_x11_event(void * phappening) override; // XEvent *
//
//#endif


      virtual void rects_from_system();


      // as hosting interaction_impl
      void install_message_routing(::channel * pchannel) override;
      // as virtual interaction_impl
      virtual void _002InstallMessageHandling(::channel * pchannel);


      virtual void __synthesizes_creates_styles(::user::interaction * pinteraction, unsigned int & nExStyle, unsigned int & nStyle);

      //virtual bool create_interaction(::user::interaction * pinteraction, const ::int_rectangle & rectangle, ::user::interaction_base * pparent, atom atom) override;
      //virtual bool create_interaction(::user::interaction * pinteraction, unsigned int uExStyle, unsigned int uStyle, const ::int_rectangle & rectangle, ::user::interaction_base * puiParent, ::request * prequest = nullptr) override;

      
      void create_child(::user::interaction * pinteraction, ::user::interaction_base * pprimitiveParent) override;


      //virtual bool create_window_ex(::user::interaction * pinteraction, ::pointer<::user::system>pcs, ::user::interaction_base * puiParent, atom atom) override;

      //virtual bool create_interaction() override;


      //virtual iptr get_window_long_ptr(int nIndex) const override;
      //virtual void set_window_long_ptr(int nIndex, iptr lValue) override;

      //virtual bool is_this_visible(enum_layout elayout) override;

      //void _window_show_change_visibility_unlocked(::e_display edisplay, const ::user::activation & useractivation) override;
      //void _window_request_presentation_locked() override;
      //void _window_request_presentation_unlocked() override;

      bool _is_window() override;

      virtual void VirtualOnSize();



      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);

      void send_message_to_descendants(const ::atom & atom,const ::wparam & wparam = {},const ::lparam & lparam = {},bool bDeep = true,bool bOnlyPerm = 0) override;

      //virtual bool post_message(::enum_message emessage, ::wparam wparam, ::lparam lparam) override;

      //void _000CallOnDraw(::draw2d::graphics_pointer & pgraphics) override;


      void set_origin(::draw2d::graphics_pointer & pgraphics) override;

      void RedrawWindow(const ::int_rectangle& rectangleUpdate,::draw2d::region* prgnUpdate,unsigned int flags) override;

      ::user::interaction_base * set_owner(::user::interaction_base * pinteraction) override;
      ::user::interaction * get_owner() override;

      //bool _get_client_rect(::long_long_rectangle * prectangle) override;
      //bool _get_window_rect(::long_long_rectangle * prectangle) override;

      //virtual int_point client_screen_top_left() override;

      //virtual bool client_to_screen(::double_rectangle * prectangle) override;

      //virtual bool client_to_screen(::int_rectangle * prectangle) override;

      //virtual bool client_to_screen(::long_long_rectangle * prectangle) override;

      //virtual bool client_to_screen(::double_point * ppoint) override;

      //virtual bool client_to_screen(::int_point * ppoint) override;

      //virtual bool client_to_screen(::long_long_point * ppoint) override;

      //virtual bool screen_to_client(::double_rectangle * prectangle) override;

      //virtual bool screen_to_client(::int_rectangle * prectangle) override;

      //virtual bool screen_to_client(::long_long_rectangle * prectangle) override;

      //virtual bool screen_to_client(::double_point * ppoint) override;

      //virtual bool screen_to_client(::int_point * ppoint) override;

      //virtual bool screen_to_client(::long_long_point * ppoint) override;


      bool keyboard_focus_OnKillFocus(oswindow oswindowNew) override;


   };


} // namespace user



