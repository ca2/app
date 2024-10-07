//
// Created by camilo on 31/01/2022 23:04 <3ThomasBorregaardSorensen!!
// //
// #include "framework.h"
// #include "display.h"
// #include "window_implementation.h"
// #include "window.h"
// #include "button.h"
// #include "acme/nano/nano.h"
// #include "user.h"
// #include "acme/platform/node.h"
// #include "acme/constant/id.h"
// #include "acme/handler/topic.h"
// #include "acme/nano/nano.h"
// #include "acme/nano/user/user.h"
// #include "acme/platform/node.h"
// #include "acme/parallelization/manual_reset_event.h"
// #include "acme/platform/sequencer.h"
// #include "acme/platform/system.h"
//
//
// #include <stdio.h>
//
//
// namespace nano
// {
//
// namespace user
// {
//
//
// static thread_local ::pointer_array < window_implementation > t_nanowindowimplementationa;
//
//
//
// ::pointer_array < window_implementation > & window_implementation::nanowindowimplementationa()
// {
//
//    return t_nanowindowimplementationa;
//
// }
//
//
// window_implementation::window_implementation()
// {
//
//
// }
//
//
// window_implementation::~window_implementation()
// {
//
//    output_debug_string("window_implementation::~window_implementation()");
//
// }
//
//
// display * window_implementation::get_display()
// {
//
//    return nullptr;
//
// }
//
//
// void window_implementation::draw(device * pnanodevice)
// {
//
//    m_pinterface->draw(pnanodevice);
//
// }
//
//
// bool window_implementation::get_dark_mode()
// {
//
//    return m_pinterface->get_dark_mode();
//
// }
//
//
// bool window_implementation::is_active()
// {
//
//    return m_pinterface->is_active();
//
// }
//
//
// void window_implementation::nano_window_on_create()
// {
//
//    //node()->fetch_user_color();
//
//    //system()->add_signal_handler({ use_t{}, this }, id_operating_system_user_color_change);
//
//    create_drawing_objects();
//
//    on_create();
//
// }
//
//
// void window_implementation::nano_window_on_destroy()
// {
//
//    system()->erase_signal_handler(this);
//
// }
//
//
// void window_implementation::on_create()
// {
//
//    return m_pinterface->on_create();
//
// }
//
//
// void window_implementation::_console_create()
// {
//
//    ::collection::index i = 0;
//
//    for (auto & pnanobutton : m_pinterface->m_nanobuttona)
//    {
//
//       char ch = pnanobutton->m_chLetter;
//
//       m_console.m_mapCharIndex[character_tolower(ch)] = i;
//
//       if (i == m_pinterface->m_iDefaultButton)
//       {
//
//          m_console.m_cha1.insert_at(0, character_toupper(ch));
//
//          m_console.m_stra.insert_at(0, pnanobutton->m_strText);
//
//       }
//       else
//       {
//
//          m_console.m_cha1.add(character_tolower(ch));
//
//          m_console.m_stra.add(pnanobutton->m_strText);
//
//       }
//
//       i++;
//
//    }
//
// }
//
//
// void window_implementation::_display_console()
// {
//
//    ::collection::index iButton;
//
//    while (true)
//    {
//
//       printf("%s", m_pinterface->m_strTitle.c_str());
//
//       ::string str;
//
//       str = m_console.m_stra.implode(",");
//
//       printf(" %s", str.c_str());
//
//       printf(" (");
//
//       printf("%c", m_console.m_cha1[0]);
//
//       for (::collection::index i = 1; i < m_console.m_cha1.get_count(); i++)
//       {
//
//          printf("/%c", m_console.m_cha1[i]);
//
//       }
//
//       printf("):");
//
//       char ch;
//
//       auto iReturnCount = scanf("%c", &ch);
//
//       if(iReturnCount >= 1)
//       {
//
//          ch = character_tolower(ch);
//
//       }
//       else
//       {
//
//          ch = '\0';
//
//       }
//
//
//       iButton = -1;
//
//       if (m_console.m_mapCharIndex.lookup(ch, iButton))
//       {
//
//          break;
//
//       }
//
//    }
//
//    if (iButton >= 0)
//    {
//
//       auto pnanobutton = m_pinterface->m_nanobuttona[iButton];
//
//       m_pinterface->on_click(pnanobutton->m_edialogresult1, nullptr);
//
//    }
//
// }
//
//
//
// ::point_i32 window_implementation::try_absolute_mouse_position(const ::point_i32 & point)
// {
//
//    return window_interface::try_absolute_mouse_position(point);
//
// }
//
//
// void window_implementation::handle(::topic * ptopic, ::context * pcontext)
// {
//
//    if(ptopic->m_atom == id_operating_system_user_color_change)
//    {
//
//       update_drawing_objects();
//
//       redraw();
//
//    }
//    else if(ptopic->m_atom == id_set_application_dark_mode)
//    {
//
//       update_drawing_objects();
//
//       redraw();
//
//    }
//    else if(ptopic->m_atom == id_application_dark_mode_change)
//    {
//
//       update_drawing_objects();
//
//       redraw();
//
//    }
//
// }
//
//
// ::size_i32 window_implementation::get_main_screen_size()
// {
//
//    auto pdisplay = get_display();
//
//    if(::is_null(pdisplay))
//    {
//
//       return {800, 600};
//
//    }
//
//    return pdisplay->get_main_screen_size();
//
// }
//
//
// ::payload window_implementation::do_synchronously(const class time & timeWait)
// {
//
//    create();
//
//    m_pinterface->show_window();
//
//    message_loop();
//
//    auto pmanualresetevent = ::place(new manual_reset_event());
//
//    m_pinterface->m_psequencer->then([ pmanualresetevent](auto psequencer)
//    {
//
//       pmanualresetevent->SetEvent();
//
//    });
//
//    auto pinterface = m_pinterface;
//
//    if(pinterface->m_payloadResult.is_new())
//    {
//
//       pmanualresetevent->wait();
//
//    }
//
//    //   auto pmessagebox = pparticle->__create_new < message_box >();
//    //
//    //   atom idResult;
//    //
//    //   manual_reset_event event;
//    //
//    //   pmessagebox->display(pszMessage, pszTitle, emessagebox, pszDetails);
//    //
//    //   pmessagebox->m_functionClose = [&idResult, &event](micro::interchange * pwindow)
//    //   {
//    //
//    //      idResult = pwindow->m_atomResult;
//    //
//    //      event.SetEvent();
//    //
//    //   };
//    //
//    //   if(is_single_main_user_thread() && is_main_thread())
//    //   {
//    //
//    //      pmessagebox->_run_modal_loop();
//    //
//    //   }
//    //   else
//    //   {
//    //      event.wait();
//    //
//    //   }
//    //
//    //   //auto idResult = pmessagebox->get_result();
//    //
//    //   return idResult;
//
//    return pinterface->m_payloadResult;
//
// }
//
// //::atom message_box::do_synchronously()
// //{
// //
// //   //main_synchronous(1_min, [this]()
// //   //{
// //
// //
// //   //main_asynchronous([this]()
// //      //{
// //
// //   create();
// //
// //   micro::interchange::display();
// //
// //  aaa_message_loop();
// //
// //   //});
// //
// //   //display(m_strMessage, m_strTitle, m_emessagebox, m_strDetails);
// //
// ////});
// //
// //   return m_atomResult;
// //
// //}
//
//
// void window_implementation::do_asynchronously()
// {
//
//    ::pointer < window_implementation > pnanowindowimplementation = this;
//
//    auto procedure = [pnanowindowimplementation]()
//       {
//
//          pnanowindowimplementation->create();
//
//          pnanowindowimplementation->m_pinterface->::micro::interchange::show_window();
//
//          //if (!is_main_thread())
//          //{
//
//          //   aaa_message_loop();
//
//          //}
//
//       };
//
//    if (is_main_thread())
//    {
//
//       procedure();
//
//    }
//    else
//    {
//
//       user_post(procedure);
//
//    }
//
//    //display(m_strMessage, m_strTitle, m_emessagebox, m_strDetails);
//
// //});
//
//    //return m_atomResult;
//
// }
//
//
// void window_implementation::defer_show_system_menu(::user::mouse * pmouse)
// {
//
//
// }
//
//
// //::atom message_box::do_synchronously()
// //{
// //
// //   //main_synchronous(1_min, [this]()
// //   //{
// //
// //
// //   //main_asynchronous([this]()
// //      //{
// //
// //   create();
// //
// //   micro::interchange::display();
// //
// //   aaa_message_loop();
// //
// //   //});
// //
// //   //display(m_strMessage, m_strTitle, m_emessagebox, m_strDetails);
// //
// ////});
// //
// //   return m_atomResult;
// //
// //}
//
//
// //void message_box::do_asynchronously()
// //{
// //
// //   m_functionClose = [this](micro::interchange * pwindow)
// //   {
// //
// //      m_psequence->on_sequence();
// //
// //   };
// //
// //   main_asynchronous([this]()
// //      {
// //
// //         create();
// //
// //         micro::interchange::display();
// //
// //         aaa_message_loop();
// //
// //      });
// //
// //   //display(m_strMessage, m_strTitle, m_emessagebox, m_strDetails);
// //
// ////});
// //
// //   //return m_atomResult;
// //
// //}
// //
// //
//
//
//    } // namespace user
//
//
// } // namespace nano
//
//
