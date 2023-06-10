#include "framework.h"


namespace calculator
{


   impact::impact(::particle * pparticle) :
      ::object(pparticle),
      ::user::interaction(pparticle)
   {

   }


   impact::~impact()
   {

   }


   void impact::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

      MESSAGE_LINK(MESSAGE_DESTROY, pchannel, this, &impact::on_message_destroy);
      MESSAGE_LINK(e_message_size, pchannel, this, &impact::on_message_size);
      MESSAGE_LINK(e_message_paint, pchannel, this, &impact::_001OnPaint);
      MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &impact::on_message_create);
      MESSAGE_LINK(e_message_context_menu, pchannel, this, &impact::on_message_context_menu);
      //MESSAGE_LINK(e_message_set_cursor, pchannel, this, &impact::on_message_set_cursor);


   }


   void impact::assert_ok() const
   {
      ::user::impact::assert_ok();
   }

   void impact::dump(dump_context & dumpcontext) const
   {
      ::user::impact::dump(dumpcontext);
   }


   /////////////////////////////////////////////////////////////////////////////
   // impact message handlers

   // vmpLightImpact.cpp : implementation of the impact class
   //


   /////////////////////////////////////////////////////////////////////////////
   // impact


   bool impact::pre_create_window(::user::system * pusersystem)
   {



      return ::user::impact::pre_create_window(pusersystem);

   }


   void impact::handle(::topic * ptopic, ::context * pcontext)
   {

      UNREFERENCED_PARAMETER(ptopic);

   }


   ::pointer<::user::interaction>impact::backimpact_GetWnd()
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
      //::pointer<::user::message>pusermessage(pmessage);
   }

   void impact::_001OnUpdateImpactEncoding(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      //::pointer<::message::command>pcommand(pmessage);
   }
   void impact::_001OnShowEncoding(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      //::pointer<::message::command>pcommand(pmessage);
   }



   // void impact::on_message_set_cursor(::message::message * pmessage)
   // {

   //    auto pmouse = pmessage->m_union.m_pmouse;

   //    pmouse->m_ecursor = cursor_arrow;

   // }


   ::user::document * impact::get_document()
   {

      return  (::user::impact::get_document());

   }


} // namespace calculator








