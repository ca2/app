// From app_simple_form/form_001.coo by camilo on 2023-06-28 05:02 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "options.h"
#include "acme/constant/message.h"
#include "aura/message/user.h"
#include "base/platform/application.h"


namespace user
{


   form_options::form_options()
   {

      m_bExtendOnParent = true;

   }


   form_options::~form_options()
   {

   }


#ifdef _DEBUG


   int64_t form_options::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   int64_t form_options::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


#endif


   void form_options::install_message_routing(::channel * psender)
   {

      form::install_message_routing(psender);

      MESSAGE_LINK(MESSAGE_CREATE, psender, this, &form_options::on_message_create);


   }


   void form_options::on_message_create(::message::message * pmessage)
   {

      ::pointer<::message::create> pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

      acmeapplication()->m_pbaseapplication->create_options_form(this);

      set_need_layout();

      set_need_redraw();

      post_redraw();

   }


   void form_options::on_perform_top_down_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction::on_perform_top_down_layout(pgraphics);

   }


   bool form_options::on_perform_layout(::draw2d::graphics_pointer & pgraphics)
   {

      return ::user::form_impact::on_perform_layout(pgraphics);

   }


   void form_options::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::form_impact::on_layout(pgraphics);

   }


   void form_options::handle(::topic * ptopic, ::context * pcontext)
   {

      //if (ptopic->m_atom == ::id_after_change_text)
      //{

      //   //if (ptopic->m_actioncontext.is_user_source())
      //   //{

      //   //   if (ptopic->m_puserelement->m_atom == "edit")
      //   //   {

      //   //      string strText;

      //   //      m_pedit->_001GetText(strText);

      //   //      auto papp = get_app();

      //   //      if (strText == "This is a test. This is a test")
      //   //      {

      //   //         information("");

      //   //      }

      //   //      papp->datastream()->set("last_text", strText);

      //   //   }

      //   //}

      //}
      ////      else if (ptopic->m_atom == ::id_click)
      ////      {
      ////
      ////         if (ptopic->m_puserelement->m_atom == "clear_button")
      ////         {
      ////
      ////            m_pedit->_001SetText("", ::e_source_user);
      ////
      ////         }
      ////         else if (ptopic->m_puserelement->m_atom == "send_button")
      ////         {
      ////
      ////            string strText;
      ////
      ////            m_pedit->_001GetText(strText);
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


   //void form_options::_001OnClearButton(::message::message * pmessage)
   //{

   //   m_pedit->_001SetText("", ::e_source_user);

   //   pmessage->m_bRet = true;

   //}


   //void form_options::_001OnSendButton(::message::message * pmessage)
   //{

   //   string strText;

   //   m_pedit->_001GetText(strText);

   //   output_error_message("send_button clicked\nText: " + strText);

   //   m_pstillReceiver->set_window_text(strText);

   //   m_pstillReceiver->post_redraw();

   //   pmessage->m_bRet = true;

   //}





} // namespace user



