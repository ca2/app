//
// Created by camilo on 2025-09-02 04:08 <3ThomasBorregaardSorensen!!
//
#pragma once


//#include "jni_object.h"
#include "acme/platform/message.h"


class CLASS_DECL_ACME message_sink :
   virtual public ::particle
{
public:

   
   ::pointer_array_base<::platform::message> m_messagea;


   message_sink();
   ~message_sink() override;


   void on_initialize_particle() override;


   virtual ::pointer < ::platform::message > create_message(::enum_message emessage, long long llWparam = 0, long long llLparam = 0);

   virtual void post_simple_message(::enum_message emessage);
   virtual void post_message(::platform::message * pmessage);
   virtual void post_data_block_message(::enum_message emessage, ::data::block * pdatablock);


   ::pointer < platform::message > pick_message_to_post();


   virtual void dispatch_posted_messages();
   virtual void dispatch_message(::platform::message * pmessage);


};



