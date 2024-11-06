//
//  conversation_message.hpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 01/Oct/22. 00:59
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#pragma once

//
//::particle_pointer particle::realize(::particle * pparticleReificator)
//{
//
//   return pparticleReificator->realize_particle(this);
//
//}
//
//
//// this is reificator/director
//::particle_pointer particle::realize_particle(::particle * pparticleToRealize)
//{
//
//
//}
//
//
////#include "acme/user/user/conversation.h"


#include "acme/prototype/prototype/realizable.h"
#include "acme/handler/sequenceable.h"


class CLASS_DECL_ACME message_box :
   virtual public ::realizable < message_box >
{
public:
   
   
   bool                                   m_bDetails = false;
   string                                 m_strMessage;
   string                                 m_strTitle;
   e_message_box                          m_emessagebox;
   string                                 m_strDetails;
   ::pointer < ::nano::graphics::icon >   m_picon;
   ::payload                              m_payloadResult;

   message_box(const ::string & strMessage, const ::string & strTitle = {}, const ::e_message_box & emessagebox = {}, const ::string & strDetails = nullptr, ::nano::graphics::icon * picon = nullptr);
   message_box(const ::exception & exception, const ::string & strMessage = {}, const ::string & strTitle = {}, const ::e_message_box & emessagebox = {}, const ::string & strDetails = nullptr, ::nano::graphics::icon * picon = nullptr);
   ~message_box() override;

#ifdef DEBUG
   huge_integer increment_reference_count() override;
   huge_integer decrement_reference_count() override;
#endif
   
   //virtual ::string get_conversation_message();
   //virtual ::string get_conversation_title();
   //virtual ::e_message_box get_conversation_flags();
   //virtual ::string get_conversation_details();
   //virtual ::payload get_conversation_result();

   
   ::payload get_result_payload() override;

   
   //::payload do_synchronously(const class time & timeWait) override;
   //void do_asynchronously() override;

   void run() override;
   //void complete_aggregation(sequence * psequence) override;

//

   
};
