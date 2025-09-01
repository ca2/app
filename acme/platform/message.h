//
// Created by camilo on 2025-08-31 02:16 <3ThomasBorregaardSorensen!!
//
#pragma once


enum enum_message
{

   ::user::e_message_none = 0,
   ::user::e_message_request_uri = 1,
   ::user::e_message_on_size = 2,
   ::user::e_message_set_editor_selection = 3,
   ::user::e_message_application_started = 4,

};


class CLASS_DECL_ACME message :
   virtual public ::particle
{
public:




   enum_application_message      m_eapplicationmessage;

   long long   m_llWparam;
   long long   m_llLparam;
   ::memory    m_memory;


   application_message();
   ~application_message() override;


   void initialize_application_message(enum_application_message emessage, long long llWpara = 0, long long llLparam = 0, const ::block & block = {});



};



