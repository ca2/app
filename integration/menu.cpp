// From impact.cpp on 2023-01-15 09:24 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "menu.h"
#include "application.h"
//#include "render.h"
#include "document.h"
#include "acme/constant/id.h"
#include "acme/constant/user_message.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/message/user.h"
#include "aura/user/user/button.h"
#include "berg/user/user/impact_system.h"
#include "berg/user/user/split_impact.h"
#include "berg/user/user/single_document_template.h"


namespace app_integration
{


   menu::menu()
   {

      m_flagNonClient.erase(e_non_client_background);

      m_flagNonClient.erase(e_non_client_focus_rect);

   }


   menu::~menu()
   {

   }


//   void menu::assert_ok() const
//   {
//
//      user::box::assert_ok();
//
//   }
//
//
//   void menu::dump(dump_context & dumpcontext) const
//   {
//
//      user::box::dump(dumpcontext);
//
//   }


#ifdef _DEBUG


   long long menu::increment_reference_count()
   {

      return  ::user::impact::increment_reference_count();

   }


   long long menu::decrement_reference_count()
   {

      return  ::user::impact::decrement_reference_count();

   }


#endif


   void menu::install_message_routing(::channel * psender)
   {

      ::user::impact::install_message_routing(psender);

      MESSAGE_LINK(::user::e_message_create,psender,this,&menu::on_message_create);
      MESSAGE_LINK(::user::e_message_destroy, psender, this, &menu::on_message_destroy);

   }


   void menu::on_message_create(::message::message * pmessage)
   {

      payload(FONTSEL_IMPACT) = true;

      ::pointer<::message::create> pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

      {

         auto pbutton = øcreate_new < ::user::button >();
         pbutton->create_control(this, "openssl");
         pbutton->add_handler(this);
         pbutton->set_position({ 100, 100 });
         pbutton->set_size({ 200, 50 });
         pbutton->set_window_text("OpenSSL");
         pbutton->display();

      }

      {

         auto pbutton = øcreate_new < ::user::button >();
         pbutton->create_control(this, "ffmpeg");
         pbutton->add_handler(this);
         pbutton->set_position({ 100, 200 });
         pbutton->set_size({ 200, 50 });
         pbutton->set_window_text("FFMPEG");
         pbutton->display();

      }

      //{

      //   auto psignal = get_app()->get_signal("simple_checkbox");

      //   psignal->add_handler(this);

      //}

      //{

      //   auto psignal = get_app()->get_signal("no_client_frame");

      //   psignal->add_handler(this);

      //}

      ////auto estatus = 
      //
      //øconstruct_new(m_prender);

      //if(!estatus)
      //{

      //   pcreate->set_fail();

      //   return;

      //}

      //m_prender->m_pimpact = this;

      auto pdocument = get_document();

      auto pimpactsystem = pdocument->m_pimpactsystem;

      string strId = pimpactsystem->id();

      string strText;

      if(get_typed_parent<::user::split_impact>() != nullptr)
      {

         if(get_typed_parent<::user::split_impact>()->get_child_by_id("top_edit_impact") != nullptr)
         {

            auto pinteraction = get_typed_parent<::user::split_impact>()->get_child_by_id("top_edit_impact");

            pinteraction->set_text(strText,::e_source_initialize);

         }

      }

   }


   void menu::on_message_destroy(::message::message * pmessage)
   {

   }


   void menu::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      ::pointer < ::user::interaction > puserinteraction = ptopic->m_puserelement;

      if (puserinteraction)
      {

         auto atom = puserinteraction->id();

         if (ptopic->id() == id_click)
         {

            if (atom == "openssl")
            {

               auto pdocument = m_papp->m_ptemplateOpenSSL->open_document_file(m_papp, nullptr, true);

               pdocument->update_all_impacts(nullptr, "openssl");

            }
            else if (atom == "ffmpeg")
            {

               auto pdocument = m_papp->m_ptemplateFFMPEG->open_document_file(m_papp, nullptr, true);

               pdocument->update_all_impacts(nullptr, "ffmpeg");

            }

         }

      }

      ::user::impact::handle(ptopic, phandlercontext);
   }


   ::user::document * menu::get_document()
   {

      return ::user::impact::get_document();

   }


   //void menu::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   //{

   //   if (get_app()->application_properties().m_echeckNoClientFrame != ::e_check_checked)
   //   {

   //      ::int_rectangle rectangle = this->rectangle();

   //      for (::collection::index i = 0; i < 11; i++)
   //      {

   //         pgraphics->draw_inset_rectangle(rectangle, argb(180, 80, 80, 80));

   //         rectangle.deflate(1, 1);

   //      }

   //   }

   //   m_prender->_001OnDraw(pgraphics);

   //}


   void menu::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleX = this->rectangle();

      if(rectangleX.is_empty())
      {

         return;

      }

      //m_prender->m_rectangle = rectangleX;

   }


} // namespace simple_drawing



