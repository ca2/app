//
// Created by camilo on 31/01/2022 23:04 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "_nano.h"
#include "acme/id.h"
#include "display.h"


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

   m_psystem->node()->fetch_user_color();

   m_psystem->add_signal_handler(this, id_operating_system_user_color_change);
   
   create_drawing_objects();

   on_create();

}


void nano_window_implementation::on_create()
{

   return m_pinterface->on_create();

}


void nano_window_implementation::handle(::topic * ptopic, ::context * pcontext)
{

   if(ptopic->m_atom == id_operating_system_user_color_change)
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


::atom nano_window_implementation::do_synchronously(const class ::wait & wait)
{


   create();

   m_pinterface->nano_window::display();

   message_loop();

   ////auto pmanualresetevent = __new(manual_reset_event);

   ////atom atomResult;

   ////m_pinterface->m_psequence->then([ pmanualresetevent, &atomResult ](auto psequence)
   ////{

   ////   atomResult = psequence->m_atomResult;

   ////   pmanualresetevent->SetEvent();
   ////   
   ////});

   ////pmanualresetevent->wait();

   //////   auto pmessagebox = pobject->__create_new < nano_message_box >();
   //////
   //////   atom idResult;
   //////
   //////   manual_reset_event event;
   //////
   //////   pmessagebox->display(pszMessage, pszTitle, emessagebox, pszDetails);
   //////
   //////   pmessagebox->m_functionClose = [&idResult, &event](nano_window * pwindow)
   //////   {
   //////
   //////      idResult = pwindow->m_atomResult;
   //////
   //////      event.SetEvent();
   //////
   //////   };
   //////
   //////   if(is_single_main_user_thread() && is_main_thread())
   //////   {
   //////
   //////      pmessagebox->_run_modal_loop();
   //////
   //////   }
   //////   else
   //////   {
   //////      event.wait();
   //////
   //////   }
   //////
   //////   //auto idResult = pmessagebox->get_result();
   //////
   //////   return idResult;

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

   /*m_pinterface->m_functionClose = [this](nano_window * pwindow)
   {

      m_pinterface->m_psequence->on_sequence();

   };*/

   main_asynchronous([this]()
      {

         create();

         m_pinterface->nano_window::display();

         message_loop();

      });

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
