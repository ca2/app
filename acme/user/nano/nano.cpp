// Created by camilo on 2022-11-19 03:54 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "nano.h"
#include "acme/platform/node.h"
#include "acme/platform/department.h"


namespace nano
{


   nano::nano()
   {

   }


   nano::~nano()
   {

   }


   //pointer< ::sequencer < ::conversation > > nano::nano()->message_box_sequencer(const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox, const ::string& strDetails)
   //{

   //   auto psequencer = acmenode()->nano()->message_box_sequencer(strMessage, strTitle, emessagebox, strDetails);

   //   return psequencer;

   //}


   //pointer< ::sequencer < ::conversation > > nano::nano()->message_sequencer(const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox, const ::string& strDetails)
   //{

   //   auto psequencer = acmenode()->nano()->message_sequencer(strMessage, strTitle, emessagebox, strDetails);

   //   return psequencer;

   //}

   pointer< ::sequencer < ::conversation > > nano::message_box_sequencer(const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox, const ::string& strDetails)
   {

      auto pnode = acmenode();

      auto psequencer = pnode->create_message_box_sequencer(strMessage, strTitle, emessagebox, strDetails);

      return psequencer;

   }


   pointer< ::sequencer < ::conversation > > nano::exception_message_box_sequencer(const ::exception& exception, const ::string& strMessageParam, const ::string& strTitleParam, const ::e_message_box& emessagebox, const ::string& strDetailsParam)
   {

      string strExceptionDetails = exception.get_consolidated_details();

      string strMessage(strMessageParam);

      if (strMessage.is_empty())
      {

         strMessage = exception.get_message();

      }

      string strTitle(strTitleParam);

      if (strTitle.is_empty())
      {

         strTitle = exception.get_title();

      }

      string strDetails(strDetailsParam);

      if (strExceptionDetails.has_char())
      {

         if (strDetails.has_char())
         {

            strDetails += "\n";

         }

         strDetails += strExceptionDetails;

      }

      auto psequencer = acmenode()->create_message_box_sequencer(
         strMessage,
         strTitle,
         emessagebox,
         strDetails);

      return psequencer;

   }


   pointer< ::sequencer < ::conversation > > nano::message_sequencer(const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox, const ::string& strDetails)
   {

      auto psequencer = acmenode()->create_message_sequencer(strMessage, strTitle, emessagebox, strDetails);

      return psequencer;

   }


   pointer< ::sequencer < ::conversation > > nano::exception_message_sequencer(const ::exception& exception, const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox, const ::string& strDetails)
   {

      string strExceptionDetails = exception.get_consolidated_details();

      auto psequencer = acmenode()->create_message_sequencer(strMessage, strTitle, emessagebox, strDetails + "\n" + strExceptionDetails);

      return psequencer;

   }



} // namespace nano



