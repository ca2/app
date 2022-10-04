//
//  conversation_message.hpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 01/Oct/22. 00:59
//  Copyright © 2022 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//

#pragma once


class CLASS_DECL_ACME conversation_message :
   virtual public ::conversation
{
public:
   
   
   string                                 m_strMessage;
   string                                 m_strTitle;
   e_message_box                          m_emessagebox;
   string                                 m_strDetails;

   
   ::string get_conversation_message() override;
   ::string get_conversation_title() override;
   ::e_message_box get_conversation_flags() override;
   ::string get_conversation_details() override;

   
   void initialize_conversation(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox, const ::string & strDetails = nullptr) override;

   
   ::payload do_synchronously(const class ::wait & wait) override;
   void do_asynchronously() override;

   
};
