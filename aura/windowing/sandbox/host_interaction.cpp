//
//  host_interaction.cpp
//  aura
//
//  Copied from node/ios by Camilo Sasuke Thomas Borregaard Sørensen on 20/06/05.
//  (with refactorization: ui_interaction -> host_interaction to
//  match OPERATING_SYSTEM_NAMESPACE::create_*host*_window() naming.)
//
#include "framework.h"
#include "_sandbox.h"


namespace sandbox_windowing
{


   host_interaction::host_interaction()
   {

      

   }


   host_interaction::~host_interaction()
   {


   }


   ::sandbox_windowing::windowing* host_interaction::windowing()
   {

      auto pwindowing = ::user::interaction::windowing();

      auto pwindowingHere = dynamic_cast <::sandbox_windowing::windowing*>(pwindowing);

      return pwindowingHere;

   }



   void host_interaction::install_message_routing(::channel* pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &host_interaction::on_message_create);

   }


   void host_interaction::_001DrawThis(::draw2d::graphics_pointer & pgraphics)
   {


   }


   void host_interaction::_001DrawChildren(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction::_001DrawChildren(pgraphics);

   }


   void host_interaction::_000OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction::_000OnDraw(pgraphics);

   }


   void host_interaction::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {


   }


   void host_interaction::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction::_001OnDraw(pgraphics);

   }


   void host_interaction::post_redraw(bool bAscendants)
   {

      ::user::interaction::post_redraw(bAscendants);

   }


   void host_interaction::on_message_create(::message::message* pmessage)
   {

      pmessage->previous();

      auto pwindowing = windowing();

      auto pwindow = window();

      pwindowing->m_pwindowApplicationHost = pwindow;

   }


   void host_interaction::on_layout(::draw2d::graphics_pointer& pgraphics)
   {

      ::rectangle_i32 r;

      client_rectangle(r);

      if (r.is_empty())
      {

         return;

      }

      ::pointer<::user::interaction>pinteraction;
      
      get_child(pinteraction);

      if (::is_null(pinteraction))
      {

         return;

      }

      pinteraction->place(r);

   }


} // namespace sandbox_windowing



