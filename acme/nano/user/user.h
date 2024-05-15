// Created by camilo on 2022-11-19 03:54 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/platform/department.h"
#include "acme/primitive/collection/comparable_list.h"
#include "_.h"


namespace nano
{

namespace user
{
class CLASS_DECL_ACME user :
virtual public acme::department
{
public:
   
   
   ::pointer_array < ::nano::user::window >         m_nanowindowa;
   
   
   user();
   ~user() override;
   
   
   inline static const char * represented_component_name(){return "nano_user";}

   
   //pointer< ::sequencer < ::conversation > > nano()->message_box(const ::string& strMessage, const ::string& strTitle = nullptr, const ::e_message_box& emessagebox = e_message_box_ok, const ::string& strDetails = nullptr);
   
   
   ////pointer< ::sequence < ::conversation > > message_box(const ::string & strMessage, const ::string & strTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, const ::string & strDetails = nullptr);
   
   //pointer< ::sequencer < ::conversation > > nano()->message_console(const ::string& strMessage, const ::string& strTitle = nullptr, const ::e_message_box& emessagebox = e_message_box_ok, const ::string& strDetails = nullptr);
   
   
   pointer< ::sequencer < ::conversation > > message_box(const ::string& strMessage, const ::string& strTitle = nullptr, const ::e_message_box& emessagebox = e_message_box_ok, const ::string& strDetails = nullptr);
   
   pointer< ::sequencer < ::conversation > > exception_message_box(const ::exception& exception, const ::string& strMessage = nullptr, const ::string& strTitle = nullptr, const ::e_message_box& emessagebox = e_message_box_ok, const ::string& strDetails = nullptr);
   
   pointer< ::sequencer < ::conversation > > message_console(const ::string& strMessage = nullptr, const ::string& strTitle = nullptr, const ::e_message_box& emessagebox = e_message_box_ok, const ::string& strDetails = nullptr);
   
   pointer< ::sequencer < ::conversation > > exception_message_console(const ::exception& exception, const ::string& strMessage = nullptr, const ::string& strTitle = nullptr, const ::e_message_box& emessagebox = e_message_box_ok, const ::string& strDetails = nullptr);
   
   
   void handle(::topic* ptopic, ::context* pcontext) override;
   
   
#if defined(WITH_X11)
   
   
   virtual void x11_sync(const ::procedure & procedure);
   virtual void x11_async(const ::procedure & procedure);
   
   
#endif
   
   
};



   } // namespace user


} // namespace nano





CLASS_DECL_ACME void initialize_nano_user(::factory::factory * pfactory);



