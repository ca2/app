#include "framework.h"


namespace calculator
{


   view::view(::layered * pobjectContext) :
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

      IGUI_MSG_LINK(WM_DESTROY, pchannel, this, &view::_001OnDestroy);
      IGUI_MSG_LINK(WM_SIZE, pchannel, this, &view::_001OnSize);
      IGUI_MSG_LINK(WM_PAINT, pchannel, this, &view::_001OnPaint);
      IGUI_MSG_LINK(WM_CREATE, pchannel, this, &view::_001OnCreate);
      IGUI_MSG_LINK(WM_CONTEXTMENU, pchannel, this, &view::_001OnContextMenu);
      IGUI_MSG_LINK(WM_SETCURSOR, pchannel, this, &view::_001OnSetCursor);


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


   bool view::pre_create_window(::user::create_struct& cs)
   {

      cs.style &= ~WS_EX_CLIENTEDGE;

      return ::user::impact::pre_create_window(cs);

   }


   void view::update(::update * pupdate)
   {

      UNREFERENCED_PARAMETER(pupdate);

   }


   __pointer(::user::interaction) view::BackViewGetWnd()
   {

      return this;

   }


   void view::_001OnDestroy(::message::message * pmessage)
   {

      ::user::impact::_001OnDestroy(pmessage);

   }


   void view::_001OnSize(::message::message * pmessage)
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


   void view::_001OnCreate(::message::message * pmessage)
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

         System.message_box(nullptr, "Playlist");

      }

   }


   void view::_001OnWavePlayerEvent(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      //SCAST_PTR(::message::base, pbase, pmessage);
   }

   void view::_001OnUpdateViewEncoding(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      //SCAST_PTR(::user::command, pcommand, pmessage);
   }
   void view::_001OnViewEncoding(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      //SCAST_PTR(::message::command, pcommand, pmessage);
   }



   void view::_001OnSetCursor(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      pmouse->m_ecursor = cursor_arrow;

   }


   ::user::document * view::get_document()
   {

      return  (::user::impact::get_document());

   }


} // namespace calculator








