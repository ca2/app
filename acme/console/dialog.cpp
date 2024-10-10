// Created by camilo on 2024-08-09 14:34 <3ThomasBorregaardSorensen!!
// From operating_system/console_message_box
// to console dialog by camilo on 2024-10-08 04:08 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "dialog.h"


namespace console
{


   dialog::dialog(::particle * pparticle) :
      m_pparticle(pparticle)
   {


   }


   dialog::~dialog()
   {


   }


   void dialog::run()
   {

      {

         auto pmessagebox = m_pparticle.cast < ::message_box >();

         if (pmessagebox)
         {

            m_payloadResult = run_message_box(pmessagebox);

            return;

         }

      }

   }


   //void dialog::complete_step(::sequencer & sequencer)
   //{

   //   sequencer.add_result(m_payloadResult);

   //}


} // namespace console



