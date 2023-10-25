//
// Created by camilo on 31/01/2022 23:04 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "display.h"
#include "window_implementation.h"
#include "window.h"
#include "button.h"
#include "acme/constant/id.h"
#include "acme/handler/topic.h"
#include "acme/platform/node.h"
#include "acme/parallelization/manual_reset_event.h"
#include "acme/platform/sequencer.h"
#include "acme/platform/system.h"


nano_window_implementation::nano_window_implementation()
{


}


nano_window_implementation::~nano_window_implementation()
{


}


::nano::display * nano_window_implementation::get_display()
{

   return nullptr;

}


void nano_window_implementation::draw(nano_device * pnanodevice)
{

   m_pinterface->draw(pnanodevice);

}


bool nano_window_implementation::get_dark_mode()
{

   return m_pinterface->get_dark_mode();

}


bool nano_window_implementation::is_active()
{

   return m_pinterface->is_active();

}


void nano_window_implementation::nano_window_on_create()
{

   acmenode()->fetch_user_color();

   acmesystem()->add_signal_handler({ e_use, this }, id_operating_system_user_color_change);
   
   create_drawing_objects();

   on_create();

}


void nano_window_implementation::on_create()
{

   return m_pinterface->on_create();

}


void nano_window_implementation::_console_create()
{

   ::index i = 0;

   for (auto & pnanobutton : m_pinterface->m_nanobuttona)
   {

      char ch = pnanobutton->m_chLetter;

      m_console.m_mapCharIndex[character_tolower(ch)] = i;

      if (i == m_pinterface->m_iDefaultButton)
      {

         m_console.m_cha1.insert_at(0, character_toupper(ch));

         m_console.m_stra.insert_at(0, pnanobutton->m_strText);

      }
      else
      {

         m_console.m_cha1.add(character_tolower(ch));

         m_console.m_stra.add(pnanobutton->m_strText);

      }

      i++;

   }

}


void nano_window_implementation::_display_console()
{

   ::index iButton;

   while (true)
   {

      printf("%s", m_pinterface->m_strTitle.c_str());

      ::string str;

      str = m_console.m_stra.implode(",");

      printf(" %s", str.c_str());

      printf(" (");

      printf("%c", m_console.m_cha1[0]);

      for (::index i = 1; i < m_console.m_cha1.get_count(); i++)
      {

         printf("/%c", m_console.m_cha1[i]);

      }

      printf("):");

      char ch;

      auto iReturnCount = scanf("%c", &ch);

      if(iReturnCount >= 1)
      {

         ch = character_tolower(ch);

      }
      else
      {

         ch = '\0';

      }


      iButton = -1;

      if (m_console.m_mapCharIndex.lookup(ch, iButton))
      {

         break;

      }

   }

   if (iButton >= 0)
   {

      auto pnanobutton = m_pinterface->m_nanobuttona[iButton];

      m_pinterface->on_click(pnanobutton->m_edialogresult1, nullptr);

   }

}



::point_i32 nano_window_implementation::try_absolute_mouse_position(const ::point_i32 & point)
{

   return nano_window_interface::try_absolute_mouse_position(point);

}


void nano_window_implementation::handle(::topic * ptopic, ::context * pcontext)
{

   if(ptopic->m_atom == id_operating_system_user_color_change)
   {

      update_drawing_objects();

      redraw();

   }
   else if(ptopic->m_atom == id_set_dark_mode)
   {
      
      update_drawing_objects();

      redraw();
      
   }

}


::size_i32 nano_window_implementation::get_main_screen_size()
{

   auto pdisplay = get_display();

   if(::is_null(pdisplay))
   {

      return {800, 600};

   }

   return pdisplay->get_main_screen_size();

}


::payload nano_window_implementation::do_synchronously(const class time & timeWait)
{

   create();

   m_pinterface->nano_window::display();

   message_loop();

   auto pmanualresetevent = __new(manual_reset_event);

   m_pinterface->m_psequencer->then([ pmanualresetevent](auto psequencer)
   {

      pmanualresetevent->SetEvent();

   });

   if(m_pinterface->m_payloadResult.is_new())
   {
      
      pmanualresetevent->wait();
      
   }

   //   auto pmessagebox = pparticle->__create_new < nano_message_box >();
   //
   //   atom idResult;
   //
   //   manual_reset_event event;
   //
   //   pmessagebox->display(pszMessage, pszTitle, emessagebox, pszDetails);
   //
   //   pmessagebox->m_functionClose = [&idResult, &event](nano_window * pwindow)
   //   {
   //
   //      idResult = pwindow->m_atomResult;
   //
   //      event.SetEvent();
   //
   //   };
   //
   //   if(is_single_main_user_thread() && is_main_thread())
   //   {
   //
   //      pmessagebox->_run_modal_loop();
   //
   //   }
   //   else
   //   {
   //      event.wait();
   //
   //   }
   //
   //   //auto idResult = pmessagebox->get_result();
   //
   //   return idResult;

   return m_pinterface->m_payloadResult;

}

//::atom nano_message_box::do_synchronously()
//{
//
//   //main_synchronous(1_min, [this]()
//   //{
//
//
//   //main_asynchronous([this]()
//      //{
//
//   create();
//
//   nano_window::display();
//
//   message_loop();
//
//   //});
//
//   //display(m_strMessage, m_strTitle, m_emessagebox, m_strDetails);
//
////});
//
//   return m_atomResult;
//
//}


void nano_window_implementation::do_asynchronously()
{

   auto procedure = [this]()
      {

         create();

         m_pinterface->nano_window::display();

         //if (!is_main_thread())
         //{

         //   message_loop();

         //}

      };

   if (is_main_thread())
   {

      procedure();

   }
   else
   {

      user_post(procedure);

   }

   //display(m_strMessage, m_strTitle, m_emessagebox, m_strDetails);

//});

   //return m_atomResult;

}




//::atom nano_message_box::do_synchronously()
//{
//
//   //main_synchronous(1_min, [this]()
//   //{
//
//
//   //main_asynchronous([this]()
//      //{
//
//   create();
//
//   nano_window::display();
//
//   message_loop();
//
//   //});
//
//   //display(m_strMessage, m_strTitle, m_emessagebox, m_strDetails);
//
////});
//
//   return m_atomResult;
//
//}


//void nano_message_box::do_asynchronously()
//{
//
//   m_functionClose = [this](nano_window * pwindow)
//   {
//
//      m_psequence->on_sequence();
//
//   };
//
//   main_asynchronous([this]()
//      {
//
//         create();
//
//         nano_window::display();
//
//         message_loop();
//
//      });
//
//   //display(m_strMessage, m_strTitle, m_emessagebox, m_strDetails);
//
////});
//
//   //return m_atomResult;
//
//}
//
//

