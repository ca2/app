#pragma once


#include "apex/user/menu/menu.h"
#include "aura/user/menu/track_popup.h"
#include "aura/user/user/interaction.h"


namespace user
{


   class CLASS_DECL_BASE menu :
      virtual public ::user::interaction,
      virtual public ::menu::menu
   {
   public:

      
      ::pointer<::user::menu>                m_pmenuParent;
      ::pointer<::menu::item>                m_pmenuitem;
      ::size_i32                             m_sizeMinimum;
      ::pointer<::menu::item>                m_pmenuitemShowSubMenu2;
      bool                                   m_bHideSubMenu2;
      ///::pointer<::user::interaction>        m_puserinteractionParent;
      ::pointer<::channel>                   m_pchannelNotify;
      bool                                   m_bCloseParentOnClose;
      ::pointer < ::menu::track_popup >      m_ptrackpopup;
//#ifdef WINDOWS_DESKTOP
//      HMENU                                  m_hmenu;
//#endif
      bool                                   m_bOwnItem;
      ::size_i32                             m_size;
      double                                 m_dCheckBoxSize;
      bool                                   m_bAutoDelete;
      double                                 m_dHeaderHeight;
      ::pointer<::menu::item>                m_pitemClose;
      //atom                                 m_atomSubMenu;
      //::pointer<::menu::item>              m_pitemSubMenu;
      i32                                    m_iHoverSubMenu;
      u32                                    m_dwOut;
      ::pointer<menu>                        m_pmenuSubMenu;
      //atom                                 m_atomTimerMenu;
      point_i32                              m_pointTrack;
      bool                                   m_bScreenHint;
      rectangle_i32                          m_rectangleScreenHint;
      //int                                  m_iFlags;
      ::menu::e_track_popup                  m_etrackpopup;
      bool                                   m_bCursorHint;
      ::point_i32                            m_pointCursorHint;
      bool                                   m_bInline;
      bool                                   m_bMenuOk;
      ::pointer<::menu::item>                m_pmenuitemSub;
      ::i32_array                            m_iaColumnWidth;
      ::i32_array                            m_iaColumnHeight;
      bool                                   m_bCloseButton;


      menu();
      menu(::menu::item * pitem);
      ~menu() override;

      //virtual void nextstyle(::user::style_context * pcontext) override;
      ::size_i32 get_window_minimum_size() override;

      bool is_menu() const override;

      virtual i64 increment_reference_count() override;
      //{

      //   return ::object::increment_reference_count();

      //}

      virtual i64 decrement_reference_count() override;
      //{

      //   return ::object::decrement_reference_count();

      //}

      virtual ::channel * get_notify_channel();

      ::menu::item * GetSubMenu(i32 i);

      virtual void defer_initialize_user_menu();
      virtual void initialize_user_menu();
      
      
      virtual void set_minimum_width(::i32 iWidth);

      //virtual void layout_menu(::draw2d::graphics_pointer& pgraphics);

      virtual bool contains_menu_item(::menu::item * pitem, bool bRecursive = true) const;

      virtual void update_track_flags(const ::menu::e_track_popup & etrackpopup);
      virtual void update_track_cursor(const ::point_i32 & pointCursorHint);
      virtual void update_track_rectangle(const ::rectangle_i32 & rectangleScreenHint);
      virtual void track_hints(::menu::track_popup * ptrackpopup);

      virtual bool create_menu(::channel * pchannelNotify = nullptr, ::user::interaction * puiParent = nullptr);
      virtual bool create_inline_menu(::channel* pchannelNotify = nullptr, ::user::interaction * puiParent = nullptr);
      ///virtual bool track_popup_menu(::channel* pchannelNotify = nullptr, ::user::interaction * puiParent = nullptr);
      virtual bool track_popup_menu(::menu::track_popup * ptrackpopup);

      void _001OnTimer(::timer * ptimer) override;

      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


      virtual void show_sub_menu(::menu::item * pmenuitem);
      virtual void hide_sub_menu();


      virtual void show_sub_menu_delayed(::menu::item * pmenuitem);
      virtual void hide_sub_menu_delayed();


      virtual void detach_sub_menu();


      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      DECLARE_MESSAGE_HANDLER(_001OnNcActivate);
      DECLARE_MESSAGE_HANDLER(on_message_non_client_calculate_size);
      DECLARE_MESSAGE_HANDLER(_001OnEnable);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);
      DECLARE_MESSAGE_HANDLER(on_message_close);
      DECLARE_MESSAGE_HANDLER(_001OnMouseActivate);
      DECLARE_MESSAGE_HANDLER(_001OnActivate);
      DECLARE_MESSAGE_HANDLER(_001OnNcCreate);


      void handle(::topic * ptopic, ::context * pcontext) override;

      bool on_click(::item * pitem) override;

      bool pre_create_window(::user::system * pusersystem) override;

      void install_message_routing(::channel * pchannel) override;

      ::pointer<::menu::item>get_menu_item();

      //::pointer<::menu::item>get_menu_item(::user::interaction * pinteraction);

      //bool has_pending_graphical_update() override;

      virtual bool create_menu(const string_array & straCommand, const string_array & straCommandTitle);

      void destroy() override;

      virtual bool add_menu(::xml::node * pnode);

      virtual bool load_xml_menu(const ::payload & payload);

      //virtual bool add_xml_menu(const ::payload & varXml);

      virtual void update_command(::menu::item * pitemParent);

      void calc_size(::menu::item * pitem, ::draw2d::graphics_pointer & pgraphics, i32 & iMaxWidth, i32 & iMaxHeight);
      void layout_buttons(::menu::item * pitem, i32 iMaxWidth, ::rectangle_i32 * prectangle, const ::rectangle_i32 & lpcrectBound);



      virtual void defer_close();

      virtual ::pointer<::user::menu_interaction>create_menu_button(::draw2d::graphics_pointer & pgraphics, ::menu::item * pitem);

      void route_command(::message::command* pcommand, bool bRouteToKeyDescendant) override;

      //// <3ThomasBorregaardSorensen__!!
      void handle_command(const ::atom& atom) override;


      void on_perform_top_down_layout(::draw2d::graphics_pointer & pgraphics) override;

//      virtual bool create_buttons(::draw2d::graphics_pointer & pgraphics);

   };


} // namespace user



