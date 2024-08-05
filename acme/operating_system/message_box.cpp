//
// Created by camilo on 2023-12-19 04:12 <3ThomasBorregaardSorensen!!
// From https://github.com/ca2/motif_labs
//
#include "framework.h"
#include "message_box.h"
#include "acme/platform/sequencer.h"


namespace operating_system
{


   ::payload message_box::do_synchronously(const class time & timeWait)
   {

      return {};

   }


::pointer< ::sequencer < ::conversation > > message_box::create_sequencer(::particle * pparticle, const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox, const ::string & strDetails)
{

   auto psequencer = pparticle->__create_new < ::sequencer < ::conversation > >();

   auto pmessagebox = pparticle->__create < ::operating_system::message_box >();
   
   psequencer->m_psequence = pmessagebox;

   pmessagebox->m_psequencer = psequencer;

   pmessagebox->initialize_conversation(strMessage, strTitle, emessagebox, strDetails);

   return psequencer;

}



} // operating_system



