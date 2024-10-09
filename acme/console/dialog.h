// Created by camilo on 2024-08-09 14:34 <3ThomasBorregaardSorensen!!
// From operating_system/console_message_box
// to console dialog by camilo on 2024-10-08 04:02 <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/platform/message_box.h"


namespace console
{


   class CLASS_DECL_ACME dialog :
      virtual public ::particle
   {
   public:


      ::particle_pointer      m_pparticle;
      ::payload               m_payloadResult;


      dialog(::particle * pparticle);
      ~dialog() override;


      void run() override;
      void complete_step(::sequencer & sequencer) override;

      
      ::enum_dialog_result run_message_box(::message_box * pmessage);


   };


} // namespace console



