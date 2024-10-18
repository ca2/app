// From app_simple_form/form_001.coo by camilo on 2023-06-28 05:02 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "handler_impact.h"
#include "acme/constant/message.h"
#include "aura/message/user.h"
#include "base/platform/application.h"


namespace user
{


   handler_impact::handler_impact()
   {

      m_bExtendOnParent = true;

   }


   handler_impact::~handler_impact()
   {

   }


#ifdef _DEBUG


   int64_t handler_impact::increment_reference_count()
   {

      return ::object::increment_reference_count();

   }


   int64_t handler_impact::decrement_reference_count()
   {

      return ::object::decrement_reference_count();

   }


#endif


   void handler_impact::install_message_routing(::channel * psender)
   {

      ::user::impact::install_message_routing(psender);

      MESSAGE_LINK(MESSAGE_CREATE, psender, this, &handler_impact::on_message_create);


   }


   void handler_impact::on_message_create(::message::message * pmessage)
   {

      ::pointer<::message::create> pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

      //application()->m_pbaseapplication->create_options_form(this);

      //set_need_layout();

      //set_need_redraw();

      //post_redraw();

   }


   void handler_impact::on_perform_top_down_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction::on_perform_top_down_layout(pgraphics);

   }


   bool handler_impact::on_perform_layout(::draw2d::graphics_pointer & pgraphics)
   {

      return ::user::impact::on_perform_layout(pgraphics);

   }


   void handler_impact::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::impact::on_layout(pgraphics);

   }


   void handler_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      //if (ptopic->m_atom == ::id_after_change_text)
      //{

      //   //if (ptopic->m_actioncontext.is_user_source())
      //   //{

      //   //   if (ptopic->user_interaction_id() == "edit")
      //   //   {

      //   //      string strText;

      //   //      m_pedit->get_text(strText);

      //   //      auto papp = get_app();

      //   //      if (strText == "This is a test. This is a test")
      //   //      {

      //   //         informationf("");

      //   //      }

      //   //      papp->datastream()->set("last_text", strText);

      //   //   }

      //   //}

      //}
      ////      else if (ptopic->m_atom == ::id_click)
      ////      {
      ////
      ////         if (ptopic->user_interaction_id() == "clear_button")
      ////         {
      ////
      ////            m_pedit->set_text("", ::e_source_user);
      ////
      ////         }
      ////         else if (ptopic->user_interaction_id() == "send_button")
      ////         {
      ////
      ////            string strText;
      ////
      ////            m_pedit->get_text(strText);
      ////
      ////            //main_async(__routine([this, strText]()
      ////              // {
      ////
      ////                  output_error_message("send_button clicked\nText: " + strText);
      ////
      ////               //}));
      ////
      ////                  m_pstillReceiver->set_window_text(strText);
      ////
      ////                  m_pstillReceiver->post_redraw();
      ////
      ////            ptopic->m_bRet = true;
      ////
      ////         }
      ////
      ////      }

   }


   void handler_impact::call_handler(::function < void(::user::interaction *) > handler)
   {

      destroy_children();

      //if(m_functionHandler)
      {

         lock_sketch_to_design locksketchtodesign(this);

         handler(this);

      }

      set_need_layout();

      set_need_redraw();

      post_redraw();

   }


   //void handler_impact::_001OnClearButton(::message::message * pmessage)
   //{

   //   m_pedit->set_text("", ::e_source_user);

   //   pmessage->m_bRet = true;

   //}


   //void handler_impact::_001OnSendButton(::message::message * pmessage)
   //{

   //   string strText;

   //   m_pedit->get_text(strText);

   //   output_error_message("send_button clicked\nText: " + strText);

   //   m_pstillReceiver->set_window_text(strText);

   //   m_pstillReceiver->post_redraw();

   //   pmessage->m_bRet = true;

   //}





} // namespace user



