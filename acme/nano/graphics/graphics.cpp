// Created by camilo on 2022-11-19 03:54 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "graphics.h"
#include "acme/nano/windowing/window.h"
#include "acme/constant/id.h"
#include "acme/handler/topic.h"
#include "acme/platform/node.h"
#include "acme/platform/department.h"


namespace nano
{
    namespace graphics
    {
        graphics::graphics()
        {
        }


        graphics::~graphics()
        {
        }


        //pointer< ::sequencer < ::conversation > > graphics::nano()->message_box(const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox, const ::string& strDetails)
        //{

        //   auto psequencer = node()->nano()->message_box(strMessage, strTitle, emessagebox, strDetails);

        //   return psequencer;

        //}


        //pointer< ::sequencer < ::conversation > > graphics::nano()->message_console(const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox, const ::string& strDetails)
        //{

        //   auto psequencer = node()->nano()->message_console(strMessage, strTitle, emessagebox, strDetails);

        //   return psequencer;

        //}
//
//        pointer<::sequencer<::conversation>> user::message_box(const ::string& strMessage, const ::string& strTitle,
//                                                               const ::e_message_box& emessagebox,
//                                                               const ::string& strDetails, ::nano::graphics::icon * picon)
//        {
//            auto pnode = node();
//
//            auto psequencer = pnode->create_message_box_sequencer(strMessage, strTitle, emessagebox, strDetails, picon);
//
//            return psequencer;
//        }
//
//
//        pointer<::sequencer<::conversation>> user::exception_message_box(
//            const ::exception& exception, const ::string& strMessageParam, const ::string& strTitleParam,
//            const ::e_message_box& emessagebox, const ::string& strDetailsParam, ::nano::graphics::icon * picon)
//        {
//            string strExceptionDetails = exception.get_consolidated_details(this);
//
//            string strMessage(strMessageParam);
//
//            if (strMessage.is_empty())
//            {
//                strMessage = exception.get_message();
//            }
//
//            string strTitle(strTitleParam);
//
//            if (strTitle.is_empty())
//            {
//                strTitle = exception.get_title();
//            }
//
//            string strDetails(strDetailsParam);
//
//            if (strExceptionDetails.has_char())
//            {
//                if (strDetails.has_char())
//                {
//                    strDetails += "\n";
//                }
//
//                strDetails += strExceptionDetails;
//            }
//
//            auto psequencer = node()->create_message_box_sequencer(
//                strMessage,
//                strTitle,
//                emessagebox,
//                strDetails,
//                picon);
//
//            return psequencer;
//        }
//
//
//        pointer<::sequencer<::conversation>> user::message_console(const ::string& strMessage, const ::string& strTitle,
//                                                                   const ::e_message_box& emessagebox,
//                                                                   const ::string& strDetails, ::nano::graphics::icon * picon)
//        {
//            auto psequencer = node()->create_message_sequencer(strMessage, strTitle, emessagebox, strDetails, picon);
//
//            return psequencer;
//        }
//
//
//        pointer<::sequencer<::conversation>> user::exception_message_console(
//            const ::exception& exception, const ::string& strMessage, const ::string& strTitle,
//            const ::e_message_box& emessagebox, const ::string& strDetails, ::nano::graphics::icon * picon)
//        {
//            string strExceptionDetails = exception.get_consolidated_details(this);
//
//            auto psequencer = node()->create_message_sequencer(strMessage, strTitle, emessagebox,
//                                                               strDetails + "\n" + strExceptionDetails, picon);
//
//            return psequencer;
//        }
//

        void graphics::handle(::topic* ptopic, ::context* pcontext)
        {
////            if (ptopic->m_atom == id_set_application_dark_mode)
////            {
////                for (auto& pinterchange : m_interchangea)
////                {
////                    pinterchange->handle(ptopic, pcontext);
////                }
////            }
        }

//
//        void user::sync(const ::procedure& procedure)
//        {
//        }
//
//
//        void user::async(const ::procedure& procedure)
//        {
//        }
//
//void user::process_messages()
//{
//
//
//}
//
//         bool user::init_threads()
//         {
//
//           return true;
//
//         }
//

    } // namespace user
} // namespace nano
