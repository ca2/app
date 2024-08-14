//
// Created by camilo on 2023-12-19 04:12 <3ThomasBorregaardSorensen!!
// From https://github.com/ca2/motif_labs
//
#pragma once


#include "acme/platform/conversation_message.h"


namespace operating_system
{


   class message_box :
virtual public ::conversation_message
   {
   public:


      //virtual void do_modal(const char * pszMsg, bool bError);

//      virtual ::atom initialize_conversation(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox, const ::scoped_string & scopedstrDetails = {});

      //virtual ::atom do_modal();
      
      ::payload do_synchronously(const class time & timeWait) override;

      
      static ::pointer< ::sequencer < ::conversation > > create_sequencer(::particle * pparticle, const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox, const ::string & strDetails);

      
   };

} // operating_system




