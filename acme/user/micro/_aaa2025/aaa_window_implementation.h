// //
// // Created by camilo on 31/01/2022 23:04 <3ThomasBorregaardSorensen!!
// //
// #pragma once
//
//
// #include "window_interface.h"
// #include "acme/user/user/element.h"
//
//
// namespace nano
// {
//
//
//    namespace user
//    {
//
//
//       class CLASS_DECL_ACME window_implementation :
//          virtual public ::user::element
//       {
//       public:
//
//
//          struct console
//          {
//
//             map < char, ::collection::index >         m_mapCharIndex;
//             ::array < char >              m_cha1;
//             ::string_array_base                m_stra;
//
//          } m_console;
//
//          ::pointer < ::operating_system::a_system_menu >       m_psystemmenu;
//
//
//          ::pointer < ::micro::elemental >         m_pinterface;
//
//          ::pointer < ::acme::windowing::display >         m_pnanouserdisplay;
//
//
//          window_implementation();
//          ~window_implementation() override;
//
//
//          virtual ::acme::windowing::display * get_display();
//
//
//          //void draw(::nano::graphics::device * pnanodevice) override;
//
//          static ::pointer_array < ::micro::window_implementation > & nanowindowimplementationa();
//
//
//
//          //bool get_dark_mode() override;
//          //bool is_active() override;
//
//          virtual void nano_window_on_create();
//
//          virtual void on_create();
//
//          virtual void nano_window_on_destroy();
//
//          virtual void _console_create();
//
//          virtual void _display_console();
//
//
//          virtual ::int_point try_absolute_mouse_position(const ::int_point & point);
//
//
//          void handle(::topic * ptopic, ::handler_context * phandlercontext) override;
//
//
//          virtual ::int_size get_main_screen_size();
//
//
//          virtual ::payload do_synchronously(const class time & timeWait = ::time::infinity()) override;
//          virtual void do_asynchronously() override;
//
//
//          virtual void defer_show_system_menu(::user::mouse * pmouse);
//
//
//       };
//
//
//    } // namespace user
//
//
// } // namespace nano
//
//
//
