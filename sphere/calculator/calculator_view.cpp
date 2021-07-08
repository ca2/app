#include "framework.h"


namespace calculator
{


   view::view(::object * pobject) :
      ::object(pobject),
      ::user::interaction(pobject)
   {

   }


   view::~view()
   {

   }


   void view::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_destroy, pchannel, this, &view::on_message_destroy);
      MESSAGE_LINK(e_message_size, pchannel, this, &view::on_message_size);
      MESSAGE_LINK(e_message_paint, pchannel, this, &view::_001OnPaint);
      MESSAGE_LINK(e_message_create, pchannel, this, &view::on_message_create);
      MESSAGE_LINK(e_message_context_menu, pchannel, this, &view::_001OnContextMenu);
      MESSAGE_LINK(e_message_set_cursor, pchannel, this, &view::on_message_set_cursor);


   }


   void view::assert_valid() const
   {
      ::user::impact::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      ::user::impact::dump(dumpcontext);
   }


   /////////////////////////////////////////////////////////////////////////////
   // view message handlers

   // vmpLightView.cpp : implementation of the view class
   //


   /////////////////////////////////////////////////////////////////////////////
   // view


   bool view::pre_create_window(::user::system * pusersystem)
   {



      return ::user::impact::pre_create_window(pusersystem);

   }


   void view::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

      UNREFERENCED_PARAMETER(psubject);

   }


   __pointer(::user::interaction) view::BackViewGetWnd()
   {

      return this;

   }


   void view::on_message_destroy(::message::message * pmessage)
   {

      ::user::impact::on_message_destroy(pmessage);

   }


   void view::on_message_size(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }


   void view::_001OnPaint(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }


   void view:: _001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      UNREFERENCED_PARAMETER(pgraphics);

   }


   void view::on_message_create(::message::message * pmessage)
   {

      if (pmessage->previous())
      {

         return;

      }


   }


   void view::_001OnContextMenu(::message::message * pmessage)
   {

   }


   void view::_001OnTabClick(i32 iTab)
   {

      if(iTab == 1)
      {

         message_box(nullptr, "Playlist");

      }

   }


   void view::_001OnWavePlayerEvent(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      //__pointer(::user::message) pusermessage(pmessage);
   }

   void view::_001OnUpdateViewEncoding(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      //__pointer(::message::command) pcommand(pmessage);
   }
   void view::_001OnViewEncoding(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      //__pointer(::message::command) pcommand(pmessage);
   }



   void view::on_message_set_cursor(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      pmouse->m_ecursor = cursor_arrow;

   }


   ::user::document * view::get_document()
   {

      return  (::user::impact::get_document());

   }


} // namespace calculator








