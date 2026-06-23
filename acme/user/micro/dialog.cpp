//
// // Created from acme/user/micro/main_window by 
//      camilo on 2024-10-07 10:21 <3ThomasBorregaardSorensen!!
// 
#include "framework.h"
#include "dialog.h"
#include "acme/windowing/window.h"
#include "acme/windowing/windowing.h"


namespace micro
{


   dialog::dialog()
   {

      //m_bRunningModalLoop = false;
      m_timeDialogTimeout = ::time::infinity();
      m_pdialog = this;

   }


   dialog::~dialog()
   {


   }


   bool dialog::on_window_create(void *pCREATESTRUCT)
   {

      on_initialize_dialog();

      return true;

   }


   ::payload dialog::wait_for_dialog_response(const class time & timeTimeout)
   {

      m_pmanualresethappeningDialogResponse->wait(timeTimeout);

      return get_dialog_response();

   }


   void dialog::set_dialog_response(const ::payload & payloadResult)
   {


   }

   
   ::payload dialog::get_dialog_response()
   {

      return {};

   }


   // bool dialog::is_waiting_for_dialog_response()
   // {
   //
   //    return !m_manualresethappeningFinished.lock(0_s);
   //
   // }


   void dialog::on_dialog_response(const ::payload & payloadResult)
   {

      //m_pmanualresethappeningFinished->set_happening();

      ::user_interface::dialog_implementation::on_dialog_response(payloadResult);


   }


   void dialog::run()
   {
      throw ::interface_only();
      //
      // debug() << "micro::dialog::run";
      //
      // main_send([this]()
      // {
      //
      //    create_window();
      //
      //    display(e_display_center, {});
      //
      // });

      //m_manualresethappeningFinished.wait(m_timeDialogTimeout);

      //pdialogThis->wait_for_dialog_result(m_timeDialogTimeout);

      //pdialogThis->destroy();

   }

   
   //void dialog::complete_step(::sequencer & sequencer)
   //{

   //   sequencer.add_result(get_conversation_result());

   //}

   ::micro::dialog * dialog::micro_dialog()
   {

      return this;

   }


   void dialog::on_window_close()
   {

      if (is_waiting_for_dialog_response())
      {

         set_dialog_response(e_dialog_result_cancel);

      }

   }


   void dialog::on_dialog_finished()
   {

      ::user_interface::dialog_implementation::on_dialog_finished();

      destroy_window();

      //   on_dialog_finished();

      if(system()->acme_windowing()->get_application_host_window())
      {

         system()->acme_windowing()->get_application_host_window()->redraw();

      }

   }


   void dialog::display(::e_display edisplay, const ::user::activation & useractivation)
   {

      ::micro::main_window::display(edisplay, useractivation);

   }


   // void dialog::set_dialog_result(const ::payload & payloadResult)
   //{

   //}


   //void dialog::realize(::particle_pointer pparticle)
   //{




   //}


} // namespace micro



