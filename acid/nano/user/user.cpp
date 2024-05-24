// Created by camilo on 2022-11-19 03:54 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "user.h"
#include "window.h"
#include "acid/constant/id.h"
#include "acid/handler/topic.h"
#include "acid/platform/node.h"
#include "acid/platform/department.h"


namespace nano
{

namespace user
{


   user::user()
   {
      

   }


   user::~user()
   {

   }


   //pointer< ::sequencer < ::conversation > > user::nano()->message_box(const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox, const ::string& strDetails)
   //{

   //   auto psequencer = node()->nano()->message_box(strMessage, strTitle, emessagebox, strDetails);

   //   return psequencer;

   //}


   //pointer< ::sequencer < ::conversation > > user::nano()->message_console(const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox, const ::string& strDetails)
   //{

   //   auto psequencer = node()->nano()->message_console(strMessage, strTitle, emessagebox, strDetails);

   //   return psequencer;

   //}

   pointer< ::sequencer < ::conversation > > user::message_box(const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox, const ::string& strDetails)
   {

      auto pnode = node();

      auto psequencer = pnode->create_message_box_sequencer(strMessage, strTitle, emessagebox, strDetails);

      return psequencer;

   }


   pointer< ::sequencer < ::conversation > > user::exception_message_box(const ::exception& exception, const ::string& strMessageParam, const ::string& strTitleParam, const ::e_message_box& emessagebox, const ::string& strDetailsParam)
   {

      string strExceptionDetails = exception.get_consolidated_details(this);

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

      auto psequencer = node()->create_message_box_sequencer(
         strMessage,
         strTitle,
         emessagebox,
         strDetails);

      return psequencer;

   }


   pointer< ::sequencer < ::conversation > > user::message_console(const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox, const ::string& strDetails)
   {

      auto psequencer = node()->create_message_sequencer(strMessage, strTitle, emessagebox, strDetails);

      return psequencer;

   }


   pointer< ::sequencer < ::conversation > > user::exception_message_console(const ::exception& exception, const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox, const ::string& strDetails)
   {

      string strExceptionDetails = exception.get_consolidated_details(this);

      auto psequencer = node()->create_message_sequencer(strMessage, strTitle, emessagebox, strDetails + "\n" + strExceptionDetails);

      return psequencer;

   }


   void user::handle(::topic* ptopic, ::context* pcontext)
   {
      
      if (ptopic->m_atom == id_set_application_dark_mode)
      {
         
         for(auto & pnanowindow : m_nanowindowa)
         {
            
            pnanowindow->handle(ptopic, pcontext);
            
         }
         
      }
      
   }


#if defined(WITH_X11)


   void user::x11_sync(const ::procedure & procedure)
   {


   }


   void user::x11_async(const ::procedure & procedure)
   {


   }


#endif


   } // namespace user


} // namespace nano


