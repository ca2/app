// Created by camilo on 2022-11-19 03:54 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/platform/department.h"


namespace nano
{


   class CLASS_DECL_ACME nano :
      virtual public acme::department
   {
   public:


      nano();
      ~nano() override;


      //pointer< ::sequencer < ::conversation > > nano()->message_box(const ::string& strMessage, const ::string& strTitle = nullptr, const ::e_message_box& emessagebox = e_message_box_ok, const ::string& strDetails = nullptr);


      ////pointer< ::sequence < ::conversation > > message_box(const ::string & strMessage, const ::string & strTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, const ::string & strDetails = nullptr);

      //pointer< ::sequencer < ::conversation > > nano()->message_console(const ::string& strMessage, const ::string& strTitle = nullptr, const ::e_message_box& emessagebox = e_message_box_ok, const ::string& strDetails = nullptr);


      pointer< ::sequencer < ::conversation > > message_box(const ::string& strMessage, const ::string& strTitle = nullptr, const ::e_message_box& emessagebox = e_message_box_ok, const ::string& strDetails = nullptr);

      pointer< ::sequencer < ::conversation > > exception_message_box(const ::exception& exception, const ::string& strMessage = nullptr, const ::string& strTitle = nullptr, const ::e_message_box& emessagebox = e_message_box_ok, const ::string& strDetails = nullptr);

      pointer< ::sequencer < ::conversation > > message_console(const ::string& strMessage = nullptr, const ::string& strTitle = nullptr, const ::e_message_box& emessagebox = e_message_box_ok, const ::string& strDetails = nullptr);

      pointer< ::sequencer < ::conversation > > exception_message_console(const ::exception& exception, const ::string& strMessage = nullptr, const ::string& strTitle = nullptr, const ::e_message_box& emessagebox = e_message_box_ok, const ::string& strDetails = nullptr);



   };


} // namespace nano



