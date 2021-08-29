#include "framework.h"


namespace calculator
{


   impact::impact(::object * pobject) :
      ::object(pobject),
      ::user::interaction(pobject)
   {

   }


   impact::~impact()
   {

   }


   void impact::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_destroy, pchannel, this, &impact::on_message_destroy);
      MESSAGE_LINK(e_message_size, pchannel, this, &impact::on_message_size);
      MESSAGE_LINK(e_message_paint, pchannel, this, &impact::_001OnPaint);
      MESSAGE_LINK(e_message_create, pchannel, this, &impact::on_message_create);
      MESSAGE_LINK(e_message_context_menu, pchannel, this, &impact::on_message_context_menu);
      //MESSAGE_LINK(e_message_set_cursor, pchannel, this, &impact::on_message_set_cursor);


   }


   void impact::assert_valid() const
   {
      ::user::impact::assert_valid();
   }

   void impact::dump(dump_context & dumpcontext) const
   {
      ::user::impact::dump(dumpcontext);
   }


   /////////////////////////////////////////////////////////////////////////////
   // impact message handlers

   // vmpLightView.cpp : implementation of the impact class
   //


   /////////////////////////////////////////////////////////////////////////////
   // impact


   bool impact::pre_create_window(::user::system * pusersystem)
   {



      return ::user::impact::pre_create_window(pusersystem);

   }


   void impact::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

      UNREFERENCED_PARAMETER(psubject);

   }


   __pointer(::user::interaction) impact::BackViewGetWnd()
   {

      return this;

   }


   void impact::on_message_destroy(::message::message * pmessage)
   {

      ::user::impact::on_message_destroy(pmessage);

   }


   void impact::on_message_size(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }


   void impact::_001OnPaint(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }


   void impact:: _001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      UNREFERENCED_PARAMETER(pgraphics);

   }


   void impact::on_message_create(::message::message * pmessage)
   {

      if (pmessage->previous())
      {

         return;

      }


   }


   void impact::on_message_context_menu(::message::message * pmessage)
   {

   }


   void impact::_001OnTabClick(i32 iTab)
   {

      if(iTab == 1)
      {

         message_box(nullptr, "Playlist");

      }

   }


   void impact::_001OnWavePlayerEvent(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      //__pointer(::user::message) pusermessage(pmessage);
   }

   void impact::_001OnUpdateViewEncoding(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      //__pointer(::message::command) pcommand(pmessage);
   }
   void impact::_001OnViewEncoding(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      //__pointer(::message::command) pcommand(pmessage);
   }



   // void impact::on_message_set_cursor(::message::message * pmessage)
   // {

   //    auto pmouse = pmessage->m_pmouse;

   //    pmouse->m_ecursor = cursor_arrow;

   // }


   ::user::document * impact::get_document()
   {

      return  (::user::impact::get_document());

   }


} // namespace calculator








