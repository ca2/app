//
// // Created from acme/user/micro/main_window by 
//      camilo on 2024-10-07 10:21 <3ThomasBorregaardSorensen!!
// 
#include "framework.h"
#include "dialog.h"


namespace micro
{


   dialog::dialog()
   {

      m_bRunningModalLoop = false;
      m_timeDialogTimeout = ::time::infinity();

   }


   dialog::~dialog()
   {


   }


   ::payload dialog::wait_for_dialog_result(const class time & timeTimeout)
   {

      m_manualresethappeningFinished.wait(timeTimeout);

      return get_dialog_result();

   }


   void dialog::set_dialog_result(const ::payload & payloadResult)
   {


   }

   
   ::payload dialog::get_dialog_result()
   {

      return {};

   }


   bool dialog::is_waiting_for_dialog_result()
   {

      return !m_manualresethappeningFinished.lock(0_s);

   }


   void dialog::on_dialog_result_set()
   {

      m_manualresethappeningFinished.set_happening();

      hide();

      destroy_window();
      
      on_sequence();

   }


   void dialog::run()
   {

      main_post([this]()
      {

         create_window();

         show();

      });

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

      if (m_bRunningModalLoop)
      {

         set_dialog_result(e_dialog_result_cancel);

      }

   }

   
   //void dialog::set_dialog_result(const ::payload & payloadResult)
   //{

   //}


   //void dialog::realize(::particle_pointer pparticle)
   //{




   //}


} // namespace micro



