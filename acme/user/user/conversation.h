// Recreated by camilo on 2022-01-12 23:15 <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/platform/sequence1.h"


class CLASS_DECL_ACME conversation :
   virtual public sequence < conversation >
{
public:


   //pointer< ::sequence < ::conversation > >           m_psequence;
   //::atom                                             m_atomResult;


   virtual void initialize_conversation(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox, const ::string & strDetails);
   virtual void do_conversation(const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox, const ::string & strDetails);


   virtual ::string get_conversation_message();
   virtual ::string get_conversation_title();
   virtual ::e_message_box get_conversation_flags();
   virtual ::string get_conversation_details();
   
   
   ::payload do_synchronously(const class ::wait & wait = ::wait::infinite()) override;
   void do_asynchronously() override;


};



