// Created by camilo on 2022-11-19 03:54 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "graphics.h"
#include "acme/windowing/window.h"
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


        //::pointer < ::subparticle > graphics::nano()->message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box& emessagebox, const ::scoped_string & scopedstrDetails)
        //{

        //   auto psequencer = node()->nano()->message_box(strMessage, strTitle, emessagebox, strDetails);

        //   return psequencer;

        //}


        //::pointer < ::subparticle > graphics::nano()->message_console(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box& emessagebox, const ::scoped_string & scopedstrDetails)
        //{

        //   auto psequencer = node()->nano()->message_console(strMessage, strTitle, emessagebox, strDetails);

        //   return psequencer;

        //}
//
//        ::pointer < ::subparticle > user::message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle,
//                                                               const ::e_message_box& emessagebox,
//                                                               const ::scoped_string & scopedstrDetails, ::nano::graphics::icon * picon)
//        {
//            auto pnode = node();
//
//            auto psequencer = pnode->create_message_box_sequencer(strMessage, strTitle, emessagebox, strDetails, picon);
//
//            return psequencer;
//        }
//
//
//        ::pointer < ::subparticle > user::exception_message_box(
//            const ::exception& exception, const ::scoped_string & scopedstrMessageParam, const ::scoped_string & scopedstrTitleParam,
//            const ::e_message_box& emessagebox, const ::scoped_string & scopedstrDetailsParam, ::nano::graphics::icon * picon)
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
//            if (strExceptionDetails.has_character())
//            {
//                if (strDetails.has_character())
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
//        ::pointer < ::subparticle > user::message_console(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle,
//                                                                   const ::e_message_box& emessagebox,
//                                                                   const ::scoped_string & scopedstrDetails, ::nano::graphics::icon * picon)
//        {
//            auto psequencer = node()->create_message_sequencer(strMessage, strTitle, emessagebox, strDetails, picon);
//
//            return psequencer;
//        }
//
//
//        ::pointer < ::subparticle > user::exception_message_console(
//            const ::exception& exception, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle,
//            const ::e_message_box& emessagebox, const ::scoped_string & scopedstrDetails, ::nano::graphics::icon * picon)
//        {
//            string strExceptionDetails = exception.get_consolidated_details(this);
//
//            auto psequencer = node()->create_message_sequencer(strMessage, strTitle, emessagebox,
//                                                               strDetails + "\n" + strExceptionDetails, picon);
//
//            return psequencer;
//        }
//

        void graphics::handle(::topic * ptopic, ::handler_context * phandlercontext)
        {
////            if (ptopic->id() == id_set_application_dark_mode)
////            {
////                for (auto& pinterchange : m_interchangea)
////                {
////                    pinterchange->handle(ptopic, phandlercontext);
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
