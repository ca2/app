#pragma once


#include "apex/user/primitive.h"
#include "acme/primitive/collection/int_map.h"
#include "acme/platform/auto_pointer.h"


namespace user
{


   class CLASS_DECL_AURA primitive_impl :
      virtual public ::channel,
      virtual public ::source,
      virtual public ::manager
   {
   public:


      ::user::interaction_impl *                m_pinteractionimpl;
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
      u32                                       m_uiLastRedraw;
      bool                                      m_bUpdatingBuffer;

      ::rectangle_i32                           m_rectangle;



      primitive_impl();
      ~primitive_impl() override;


      inline critical_section * cs_display() { return m_pcsDisplay; }
      virtual ::user::interaction_impl * get_user_interaction_impl();
      virtual ::user::interaction_child * get_user_interaction_child();

      
      ::aura::application* get_app();
      ::aura::session* get_session();
      //::aura::system* acmesystem();



      virtual void prio_install_message_routing(::channel * pchannel);
      virtual void last_install_message_routing(::channel * pchannel);

      virtual void default_message_handler(::message::message* pusermessage);

      virtual void queue_message_handler(::message::message * pmessage);


      virtual ::pointer<::message::message>get_message(const ::atom & atom, wparam wparam, lparam lparam, ::message::enum_prototype eprototype = ::message::e_prototype_none) override;


      virtual void enable_window(bool bEnable = true);




      virtual void create_host(::user::interaction * puserinteraction);
      virtual void create_child(::user::interaction * puserinteraction, ::user::primitive * puserprimitiveParent);


      //virtual bool check_need_layout();
      //virtual void clear_need_layout();
      virtual void set_need_layout();
      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);
      virtual void on_reposition();
      virtual void on_show_window();


      virtual oswindow detach_window();

      void destroy() override;

      virtual void window_show_change_visibility(::e_display edisplay, ::e_activation eactivation);


      virtual void start_window_visual();

      virtual void create_message_queue(::user::interaction * pinteraction, const ::string & lpszName);
      
      virtual void prodevian_update_screen();

      //virtual void RepositionBars(::u32 nIDFirst, ::u32 nIDLast, ::atom nIdLeftOver, ::u32 nFlag = reposDefault, ::rectangle_i32 * prectParam = nullptr, const ::rectangle_i32 & rectangleClient = nullptr, bool bStretch = true);

      virtual void window_move(i32 x, i32 y);


      virtual void post(::message::message* pusermessage);

      virtual void set_bitmap_source(const string& strBitmapSource);
      virtual void clear_bitmap_source();

      virtual void set_tool_window(bool bSet);

      virtual void interaction_post(const ::procedure& procedure);

      virtual void _000OnMouseLeave(::message::message* pmessage);

      virtual void track_mouse_hover();
      virtual void track_mouse_leave();


      virtual void add_prodevian(::matter* pmatter);
      virtual void erase_prodevian(::matter* pmatter);
      virtual bool is_prodevian(const ::matter* pmatter) const;


      virtual void prodevian_stop();


      virtual ::user::primitive* set_owner(::user::primitive* pprimitiveOwner);


      virtual bool has_pending_redraw_flags();


      virtual void pre_subclass_window();


      virtual void destroy_impl_only();
      virtual void start_destroying_window();
      virtual void destroy_window();


      virtual bool _is_window();

      
      virtual ::lresult send_message(const ::atom& atom, ::wparam wParam = 0, ::lparam lParam = 0, const ::point_i32& point = nullptr);


      virtual void post_message(const ::atom& atom, wparam wParam = 0, ::lparam lParam = 0);


      //virtual void set_window_text(const ::string& pszString);

      virtual void on_set_window_text();


      //virtual strsize get_window_text(char* pszStringBuf, strsize nMaxCount);


      //virtual void get_window_text(string& rString);


      //virtual strsize get_window_text_length();


      virtual void UpdateWindow();
      virtual void SetRedraw(bool bRedraw = true);


      virtual void prodevian_redraw(bool bUpdateBuffer);


      virtual void set_mouse_cursor(::windowing::cursor* pcursor);


      virtual ::user::interaction* ChildWindowFromPoint(const ::point_i32& point);
      virtual ::user::interaction* ChildWindowFromPoint(const ::point_i32& point, ::u32 nFlags);


      virtual ::user::interaction* GetLastActivePopup();


      virtual void update_data(bool bSaveAndValidate = true);


      virtual void CenterWindow(::user::interaction* pAlternateOwner = nullptr);


      virtual bool OnChildNotify(::message::message* pusermessage);


      virtual void ActivateTopParent();


      virtual void _001UpdateWindow();


      virtual void on_start_layout_experience(enum_layout_experience elayoutexperience);
      virtual void on_end_layout_experience(enum_layout_experience elayoutexperience);


      virtual void on_configuration_change(::user::primitive* pprimitiveSource);


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

      
      virtual ::user::interaction* get_child_by_id(const ::atom& atom, ::index iItem = -1, i32 iLevel = -1);


      virtual void set_need_redraw(const ::rectangle_i32& rectangleNeedRedraw = {}, bool bAscendants = true);


      virtual void RedrawWindow(const ::rectangle_i32& rectangleUpdate = nullptr,::draw2d::region* prgnUpdate = nullptr,::u32 flags = 0);


      virtual i32 GetUpdateRgn(::draw2d::region* pRgn, bool bErase = false);
      virtual void Invalidate(bool bErase = true);
      virtual void InvalidateRect(const ::rectangle_i32& rectangle, bool bErase = true);

      virtual void InvalidateRgn(::draw2d::region* pRgn, bool bErase = true);
      virtual void ValidateRect(const ::rectangle_i32& rectangle);

      virtual void ValidateRgn(::draw2d::region* pRgn);
      virtual void ShowOwnedPopups(bool bShow = true);


      virtual ::graphics::graphics* get_window_graphics();
      virtual bool is_composite();


      virtual void _task_transparent_mouse_event();


      virtual void on_graphics(::draw2d::graphics_pointer & pgraphics);
      virtual void _000OnDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _001DrawThis(::draw2d::graphics_pointer & pgraphics);
      virtual void _001DrawChildren(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void draw_control_background(::draw2d::graphics_pointer & pgraphics);


      virtual ::user::interaction * get_wnd();


      virtual void set_origin(::draw2d::graphics_pointer & pgraphics);


      virtual void viewport_screen_to_client(::point_i32 & point);
      virtual void viewport_client_to_screen(::point_i32 & point);
      virtual void viewport_client_to_screen(::rectangle_i32 & rectangle);
      virtual void viewport_screen_to_client(::rectangle_i32 & rectangle);


      //virtual u32 GetStyle() const;
      //virtual u32 GetExStyle() const;
      //virtual void ModifyStyle(u32 dwRemove,u32 dwAdd,::u32 nFlags = 0);
      //virtual void ModifyStyleEx(u32 dwRemove,u32 dwAdd,::u32 nFlags = 0);

      //virtual ::i32 get_window_long(i32 nIndex) const;
      //virtual ::i32 set_window_long(i32 nIndex,::i32 lValue);

      //virtual iptr get_window_long_ptr(i32 nIndex) const;
      //virtual void set_window_long_ptr(i32 nIndex, iptr lValue);

      virtual atom GetDlgCtrlId() const;
      virtual atom SetDlgCtrlId(::atom atom);

      virtual ::user::interaction * first_child();
      virtual ::user::interaction * top_child();
      virtual ::user::interaction * under_sibling();
      virtual ::user::interaction * above_sibling();

      virtual ::user::interaction * above_sibling(::user::interaction * pinteraction);
      virtual ::user::interaction * under_sibling(::user::interaction * pinteraction);


      virtual ::u32 ArrangeIconicWindows();
      //virtual void BringToTop(::e_display edisplay);
      //virtual bool BringWindowToTop();


      virtual bool is_ascendant(::user::element * puiIsAscendant, bool bIncludeSelf);
      virtual bool is_parent(::user::element * puiIsParent);
      virtual bool is_child(::user::element * puiIsChild);
      virtual bool is_descendant(::user::element * puiIsDescendant, bool bIncludeSelf);


//      virtual ::user::interaction * get_wnd();
      virtual ::user::interaction * get_wnd(::u32 nCmd);


      virtual ::user::frame * frame();
      virtual ::user::frame * top_level_frame();


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
      inline ::user::frame * parent_frame();
      //virtual ::user::frame * GetParentTopLevelFrame() const;
      //virtual ::user::frame * EnsureParentFrame();


      virtual lresult message_call(const ::atom & atom, wparam wparam, lparam lparam, const ::point_i32& point = nullptr);
      virtual lresult message_call(::message::message * pmessage);



      virtual void send_message_to_descendants(const ::atom & atom, wparam wParam = 0,lparam lParam = 0,bool bDeep = true,bool bOnlyPerm = false);



      virtual void pre_translate_message(::message::message * pmessage);


      //virtual bool is_active() const;

      //virtual bool has_capture() const;
      //virtual bool set_capture(::user::interaction * pinteraction = nullptr);
      //virtual ::user::interaction * get_capture() const;

      //virtual bool has_keyboard_focus() const;
      //virtual bool set_keyboard_focus(::user::interaction * pinteraction = nullptr) ;
      //virtual ::user::interaction * get_keyboard_focus() const ;




      virtual void get_rect_normal(::rectangle_i32 * prectangle);


      virtual void SetTimer(uptr uEvent, const class ::time & millisElapse, PFN_TIMER pfnTimer = nullptr, bool bPeriodic = true, void * pdata = nullptr);
      virtual void KillTimer(uptr uEvent);



      void _001OnTimer(::timer * ptimer);

      virtual bool IsTopParentActive();

      //virtual void destroy_impl_only();
      //void start_destroying_window();


      //virtual void defer_start_prodevian();
      //virtual void _defer_start_prodevian();


      virtual void mouse_hover_add(::user::interaction * pinterface);
      virtual bool mouse_hover_erase(::user::interaction * pinterface);


      virtual void register_drop_target();


      ::windowing::window* window();


      virtual ::user::element * get_keyboard_focus();
      virtual void set_keyboard_focus(::user::primitive_impl * pprimitiveimpl);
      virtual void erase_keyboard_focus(::user::primitive_impl* pprimitiveimpl);
      virtual void clear_keyboard_focus(::user::primitive_impl* pprimitiveimplGainingFocusIfAny = nullptr);
      virtual void impl_set_keyboard_focus(::user::primitive_impl* pprimitiveimpl);
      virtual void impl_erase_keyboard_focus(::user::primitive_impl * pprimitiveimpl);
      virtual void impl_clear_keyboard_focus();


      //virtual void post_message(const ::atom & atom, ::wparam wparam = 0, lparam lparam = 0);

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


      virtual lresult send_x11_event(void * pevent);


#endif


      virtual void _raw_client_to_screen(::point_i32 & point);


   };


} // namespace user



