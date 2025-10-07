#pragma once


//#include "apme/handler/source.h"
#include "apex/message/channel.h"
#include "apex/handler/manager.h"
#include "acme/prototype/geometry2d/rectangle_array.h"
#include "acme/prototype/collection/int_map.h"
#include "acme/platform/auto_pointer.h"


namespace user
{


   class CLASS_DECL_AURA primitive_impl :
      virtual public ::channel,
      //virtual public ::source,
      virtual public ::manager
      //, virtual public ::graphics::output_purpose
   {
   public:


      ::windowing::window *                m_pinteractionimpl;
      ::user::interaction_child *               m_pinteractionchild;


      iptr_to_iptr                              m_iptrmap;

      bool                                      m_bUserImplCreated;
      bool                                      m_bDrawFlagsReady;
      bool                                      m_bDestroyImplOnly;
      //bool                                    m_bDestroying;
      int                                       m_iPendingRectMatch;
      ::pointer<::user::interaction>            m_puserinteraction;
      ::pointer<::user::box>                    m_puserbox;
      bool                                      m_bIgnoreSizeEvent;
      bool                                      m_bIgnoreMoveEvent;
      ::auto_pointer < critical_section >       m_pcsDisplay;

      ::pointer<::acme::timer_array>            m_ptimerarray;

      const char *                              m_pszInteractionImplBaseDebug;

      bool                                      m_bPendingRedraw;
      unsigned int                                       m_uiLastRedraw;
      bool                                      m_bUpdatingBuffer;

      ::int_rectangle                           m_rectangle;



      primitive_impl();
      ~primitive_impl() override;


      inline critical_section * cs_display() { return m_pcsDisplay; }
      virtual ::windowing::window * get_user_interaction_impl();
      virtual ::user::interaction_child * get_user_interaction_child();

      
      ::aura::application* get_app();
      ::aura::session* get_session();
      //::aura::system* system();



      virtual void prio_install_message_routing(::channel * pchannel);
      virtual void last_install_message_routing(::channel * pchannel);

      virtual void default_message_handler(::message::message* pusermessage);

      virtual void queue_message_handler(::message::message * pmessage);


      virtual ::pointer<::message::message>get_message(::enum_message emessage, ::wparam wparam, ::lparam lparam, ::message::enum_prototype eprototype = ::message::e_prototype_none) override;


      virtual void enable_window(bool bEnable = true);




      //virtual void create_host(::user::interaction * puserinteraction, enum_parallelization eparallelization);

      virtual void create_host(::user::interaction * puserinteraction);
      virtual void create_child(::user::interaction * puserinteraction, ::user::interaction_base * puserprimitiveParent);


      virtual void defer_do_graphics(::draw2d::graphics_pointer & pgraphics);


      virtual void top_down_prefix();
      //virtual bool check_need_layout();
      //virtual void clear_need_layout();
      virtual void set_need_layout();
      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);
      virtual void on_reposition();
      virtual void on_show_window();


      virtual oswindow detach_window();

      void destroy() override;

      //virtual void _window_show_change_visibility_locked();
      //virtual void _window_show_change_visibility_unlocked(::e_display edisplay, const ::user::activation & useractivation);
      //virtual void _window_request_presentation_locked();
      //virtual void _window_request_presentation_unlocked();

      virtual void create_message_queue(::user::interaction * pinteraction, const ::string & lpszName);
      
      //virtual void graphics_thread_update_screen();

      //virtual void RepositionBars(unsigned int nIDFirst, unsigned int nIDLast, ::atom nIdLeftOver, unsigned int nFlag = reposDefault, ::int_rectangle * prectParam = nullptr, const ::int_rectangle & rectangleX = nullptr, bool bStretch = true);

      virtual void window_move(int x, int y);


      virtual void on_configure(const ::int_rectangle & rectangle);
      //\virtual void on_resize(const ::int_size & size);


      

      virtual void set_bitmap_source(const ::scoped_string & scopedstrBitmapSource);
      virtual void clear_bitmap_source();

      virtual void set_tool_window(bool bSet);

      virtual void interaction_post(const ::procedure& procedure);

      virtual void _000OnMouseLeave(::message::message* pmessage);

      virtual void track_mouse_hover();
      virtual void track_mouse_leave();



      virtual void add(::graphics::output_purpose * poutputpurpose);
      virtual void erase(::graphics::output_purpose * poutputpurpose);
      virtual void add_graphical_output_purpose(::particle * pparticle, ::graphics::enum_output_purpose epurpose);
      virtual void erase_graphical_output_purpose(::particle * pparticle);
      virtual bool does_particle_has_fps_purpose(const ::particle * pparticle) const;
      //virtual ::graphics::enum_output_purpose most_demanding_graphical_output_purpose() const;
      virtual bool has_screen_output_purpose() const;
      virtual bool has_graphical_output_purpose() const;
      virtual bool has_fps_output_purpose() const;

      //virtual void add_fps_interest(::particle* pparticle);
      //virtual void erase_fps_interest(::particle * pparticle);
      //virtual bool is_fps_interest(const ::particle * pparticle) const;


      //virtual void fps_interest_stop();


      virtual ::user::interaction_base* set_owner(::user::interaction_base* pprimitiveOwner);


      virtual bool has_pending_redraw_flags();


//      virtual void add(::graphics::output_purpose * pgraphicaloutputpurpose);
//      virtual void add_graphical_output_interest(::particle * pparticle, ::graphics::enum_output_purpose epurpose);
//      virtual void erase_graphical_output_interest(::particle * pparticle);
//      virtual bool does_particle_has_fps_interest(const ::particle * pparticle) const;
//      virtual ::graphics::enum_output_purpose most_demanding_graphical_output_purpose() const;
//      virtual bool has_screen_graphical_output_purpose() const;
//      virtual bool has_graphical_output_purpose() const;
//      virtual bool has_fps_graphical_output_purpose() const;


      virtual void pre_subclass_window();


      virtual void destroy_impl_only();
      virtual void start_destroying_window();
      virtual void destroy_window();


      virtual bool _is_window();

      
      virtual ::lresult send_message(const ::atom& atom, ::const ::wparam & wparam = {}, ::const ::lparam & lparam = {}, const ::int_point & point = {});

      virtual ::lresult send_message(::message::message * pmessage);

      using ::channel::message_handler;

      virtual void message_handler(::enum_message emessage, ::wparam wparam = {}, ::lparam lparam = {});

     
      virtual void post_message(const ::atom& atom, const ::wparam & wparam = {}, ::const ::lparam & lparam = {});
      
      virtual void post_message(::message::message* pusermessage);

      //virtual void set_window_text(const ::string& pszString);

      virtual void on_set_window_text();


      //virtual character_count get_window_text(char* pszStringBuf, character_count nMaxCount);


      //virtual void get_window_text(string& rString);


      //virtual character_count get_window_text_length();


      //virtual void UpdateWindow();
      //virtual void SetRedraw(bool bRedraw = true);


      //virtual void graphics_thread_redraw(bool bUpdateBuffer);


      virtual void set_mouse_cursor(::windowing::cursor* pcursor);


      virtual ::user::interaction* ChildWindowFromPoint(const ::int_point& point);
      virtual ::user::interaction* ChildWindowFromPoint(const ::int_point& point, unsigned int nFlags);


      virtual ::user::interaction* GetLastActivePopup();


      virtual void update_data(bool bSaveAndValidate = true);


      virtual void CenterWindow(::user::interaction* pAlternateOwner = nullptr);


      virtual bool OnChildNotify(::message::message* pusermessage);


      virtual void ActivateTopParent();


      virtual void _001UpdateWindow();


      virtual void on_start_layout_experience(enum_layout_experience elayoutexperience);
      virtual void on_end_layout_experience(enum_layout_experience elayoutexperience);


      virtual void on_configuration_change(::user::interaction_base* pprimitiveSource);


      //virtual ::user::element* get_keyboard_focus();


      virtual void _001OnAfterExitIconic();
      virtual void _001OnAfterExitNormal();
      virtual void _001OnAfterExitZoomed();
      virtual void _001OnAfterExitFullScreen();


      //virtual void _001OnTriggerMouseInside();


      virtual bool has_pending_graphical_update();


      virtual void on_after_graphical_update();


      virtual bool is_this_visible(enum_layout elayout);


      virtual void post_redraw(bool bAscendants = true);


      virtual double _001GetTopLeftWeightedOccludedOpaqueRate();


      //virtual ::windowing::window* get_window() const;


      virtual bool keyboard_focus_OnKillFocus(oswindow oswindowNew);
      virtual bool keyboard_focus_OnChildKillFocus();


      virtual void edit_on_set_focus(::user::interaction* pinteraction);


      virtual void edit_on_kill_focus(::user::interaction* pinteraction);


      virtual void show_software_keyboard(::user::element * pelement);
      virtual void hide_software_keyboard(::user::element * pelement);

      
      virtual ::user::interaction* get_child_by_id(const ::atom& atom, ::collection::index iItem = -1, int iLevel = -1);


      virtual void set_need_redraw(const ::int_rectangle_array & rectangleaNeedRedraw = {}, function<void()> function =     nullptr, bool bAscendants = true);


      virtual void RedrawWindow(const ::int_rectangle& rectangleUpdate = {},::draw2d::region* prgnUpdate = nullptr,unsigned int flags = 0);


      //virtual int GetUpdateRgn(::draw2d::region* pRgn, bool bErase = false);
      //virtual void Invalidate(bool bErase = true);
      //virtual void InvalidateRect(const ::int_rectangle& rectangle, bool bErase = true);

      //virtual void InvalidateRgn(::draw2d::region* pRgn, bool bErase = true);
      //virtual void ValidateRect(const ::int_rectangle& rectangle);

      //virtual void ValidateRgn(::draw2d::region* pRgn);
      //virtual void ShowOwnedPopups(bool bShow = true);


      virtual ::graphics::graphics* get_window_graphics();
      virtual bool is_composite();


      virtual void _task_transparent_mouse_event();

      virtual void _001OnNcClip(::draw2d::graphics_pointer & pgraphics);
      //virtual void _000CallOnDraw(::draw2d::graphics_pointer & pgraphics);
      //virtual void _000OnDraw(::draw2d::graphics_pointer & pgraphics);
      //virtual void _001DrawThis(::draw2d::graphics_pointer & pgraphics);
      //virtual void _001DrawChildren(::draw2d::graphics_pointer & pgraphics);
      //virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);
      //virtual void draw_control_background(::draw2d::graphics_pointer & pgraphics);


      virtual ::user::interaction * get_wnd();


      virtual void set_origin(::draw2d::graphics_pointer & pgraphics);


      virtual void viewport_screen_to_client(::sequence2_int & sequence);
      virtual void viewport_client_to_screen(::sequence2_int & sequence);
      virtual void viewport_client_to_screen(::int_rectangle & rectangle);
      virtual void viewport_screen_to_client(::int_rectangle & rectangle);


      //virtual unsigned int GetStyle() const;
      //virtual unsigned int GetExStyle() const;
      //virtual void ModifyStyle(unsigned int dwRemove,unsigned int dwAdd,unsigned int nFlags = 0);
      //virtual void ModifyStyleEx(unsigned int dwRemove,unsigned int dwAdd,unsigned int nFlags = 0);

      //virtual int get_window_long(int nIndex) const;
      //virtual int set_window_long(int nIndex,int lValue);

      //virtual iptr get_window_long_ptr(int nIndex) const;
      //virtual void set_window_long_ptr(int nIndex, iptr lValue);

      virtual atom GetDlgCtrlId() const;
      virtual atom SetDlgCtrlId(::atom atom);

      virtual ::user::interaction * first_child();
      virtual ::user::interaction * top_child();
      virtual ::user::interaction * under_sibling();
      virtual ::user::interaction * above_sibling();

      virtual ::user::interaction * above_sibling(::user::interaction * pinteraction);
      virtual ::user::interaction * under_sibling(::user::interaction * pinteraction);


      virtual unsigned int ArrangeIconicWindows();
      //virtual void BringToTop(::e_display edisplay);
      //virtual bool BringWindowToTop();


      virtual bool is_ascendant(::user::element * puiIsAscendant, bool bIncludeSelf);
      virtual bool is_parent(::user::element * puiIsParent);
      virtual bool is_child(::user::element * puiIsChild);
      virtual bool is_descendant(::user::element * puiIsDescendant, bool bIncludeSelf);


//      virtual ::user::interaction * get_wnd();
      virtual ::user::interaction * get_wnd(unsigned int nCmd);


      virtual ::user::frame_interaction * frame();
      virtual ::user::frame_interaction * top_level_frame();


      //virtual ::user::interaction * GetTopWindow() const;
      virtual ::user::interaction * get_parent();
      inline ::user::interaction * top_level();
      //virtual ::user::interaction * GetParentTopLevel() const;
      //virtual ::user::interaction * EnsureTopLevel();
      //virtual ::user::interaction * EnsureParentTopLevel();
      virtual ::user::interaction * get_owner();
      virtual ::user::interaction * get_parent_owner();
      virtual ::user::interaction * get_parent_or_owner();
      virtual ::user::interaction * get_top_level_owner();
      inline ::user::frame_interaction * parent_frame();
      //virtual ::user::frame_interaction * GetParentTopLevelFrame() const;
      //virtual ::user::frame_interaction * EnsureParentFrame();


      virtual lresult message_call(::enum_message emessage, ::wparam wparam, ::lparam lparam, const ::int_point & point = {});
      virtual lresult message_call(::message::message * pmessage);

      virtual void send_message_to_descendants(::enum_message emessage, ::wparam wparam = {}, ::lparam lparam = {},bool bDeep = true,bool bOnlyPerm = false);



      virtual void pre_translate_message(::message::message * pmessage);


      //virtual bool is_active() const;

      //virtual bool has_capture() const;
      //virtual bool set_capture(::user::interaction * pinteraction = nullptr);
      //virtual ::user::interaction * get_capture() const;

      //virtual bool has_keyboard_focus() const;
      //virtual bool set_keyboard_focus(::user::interaction * pinteraction = nullptr) ;
      //virtual ::user::interaction * get_keyboard_focus() const ;




      virtual void get_rect_normal(::int_rectangle * prectangle);


      virtual void set_timer(uptr uEvent, const class ::time & millisElapse, PFN_TIMER pfnTimer = nullptr, bool bPeriodic = true, void * pdata = nullptr);
      virtual void kill_timer(uptr uEvent);



      void on_timer(::timer * ptimer);

      virtual bool IsTopParentActive();

      //virtual void destroy_impl_only();
      //void start_destroying_window();


      //virtual void defer_start_fps_interest();
      //virtual void _defer_start_fps_interest();


      virtual void mouse_hover_add(::user::interaction * pinterface);
      virtual bool mouse_hover_erase(::user::interaction * pinterface);


      virtual void register_drop_target();


      ::windowing::window* window();


      virtual ::user::element * get_keyboard_focus();
      virtual void set_keyboard_focus(::user::primitive_impl * pprimitiveimpl);
      //virtual void erase_keyboard_focus(::user::primitive_impl* pprimitiveimpl);
      virtual void aaa_clear_keyboard_focus(::user::primitive_impl* pprimitiveimplGainingFocusIfAny = nullptr);
      virtual void impl_set_keyboard_focus(::user::primitive_impl* pprimitiveimpl);
      virtual void impl_erase_keyboard_focus(::user::primitive_impl * pprimitiveimpl);
      virtual void aaa_impl_clear_keyboard_focus();


      //virtual void post_message(const ::atom & atom, ::const ::wparam & wparam = {}, const ::lparam & lparam = {});

      virtual void post_non_client_destroy();

      //void display(::display edisplay);

      DECLARE_MESSAGE_HANDLER(_001OnPrioCreate);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      DECLARE_MESSAGE_HANDLER(on_message_non_client_destroy);

      virtual void show_task(bool bShow);

      virtual void redraw_add(::particle * pparticle);
      virtual void redraw_erase(::particle * pparticle);
      virtual bool has_redraw();


      virtual void user_interaction_on_hide();


#ifdef LINUX


      virtual lresult send_x11_event(void * phappening);


#endif


      virtual void _raw_client_to_screen(::int_point & point);
      virtual void _raw_screen_to_client(::int_point& point);


      ::trace_statement & trace_statement_prefix(::trace_statement & statement) const override;


      void user_send(const ::procedure & procedure) override;
      void user_post(const ::procedure & procedure) override;

      void main_send(const ::procedure & procedure) override;
      void main_post(const ::procedure & procedure) override;

      virtual void set_opacity(double dOpacity);


   };


} // namespace user



