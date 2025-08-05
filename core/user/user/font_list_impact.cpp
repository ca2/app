// Created by camilo on 2023-08-28 00:49 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "font_list_impact.h"
//#include "acme/constant/id.h"
//#include "acme/handler/item.h"
//#include "acme/platform/application.h"
//#include "acme/platform/application.h"
//#include "acme/platform/session.h"
//#include "acme/platform/system.h"
//#include "acme/filesystem/filesystem/directory_context.h"
#include "aura/graphics/write_text/font_list.h"
//#include "berg/user/form/document.h"


namespace user
{


   font_list_impact::font_list_impact()
   {

   }


   font_list_impact::~font_list_impact()
   {

   }


   //::core::application * font_list_impact::get_app()
   //{

   //   auto papplication = application();

   //   return ::is_set(papplication) ? papplication : nullptr;

   //}


   //::core::session * font_list_impact::get_session()
   //{

   //   auto pacmesession = session();

   //   return ::is_set(pacmesession) ? pacmesession : nullptr;

   //}


   //::core::system * font_list_impact::get_system()
   //{

   //   auto pacmesystem = system();

   //   return ::is_set(pacmesystem) ? pacmesystem : nullptr;

   //}


   //::base::user * font_list_impact::user()
   //{

   //   return ::user::impact::user();

   //}


   void font_list_impact::install_message_routing(::channel * pchannel)
   {

      ::user::show < font_list >::install_message_routing(pchannel);
      //::user::font_list::install_message_routing(pchannel);

   }


   void font_list_impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      ::user::show < font_list > ::handle(ptopic, phandlercontext);

      //::user::list_impact::handle(ptopic, phandlercontext);

      //////__update(::update)
      //{

      //   if (ptopic->id() == id_browse)
      //   {

      //      if (!ptopic->payload(id_form).is_empty())
      //      {

      //         string strMatter = directory()->matter(ptopic->payload(id_form));

      //         if (get_document()->on_open_document(strMatter))
      //         {

      //            m_strPath = ptopic->payload(id_form);

      //         }

      //      }

      //   }
      //   else if (ptopic->id() == id_get_form_impact)
      //   {

      //      ptopic->payload(id_form) = this;

      //   }

      //}

      //if (m_pcallback != nullptr)
      //{

      //   ptopic->payload(id_form) = this;

      //   m_pcallback->handle(ptopic, phandlercontext);

      //}

   }


   void font_list_impact::initialize(::particle * pparticle)
   {

      //auto estatus = 

      ::user::show < font_list >::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus =

      //::user::form_impact::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 

      //::user::list_impact::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   //void font_list_impact::assert_ok() const
   //{

   //   form_list::assert_ok();
   //   form_impact::assert_ok();
   //   list_impact::assert_ok();

   //}


   //void font_list_impact::dump(dump_context & dumpcontext) const
   //{

   //   form_list::dump(dumpcontext);
   //   form_impact::dump(dumpcontext);
   //   list_impact::dump(dumpcontext);

   //}


   //bool font_list_impact::pre_create_window(::user::system * pusersystem)
   //{

   //   if (!::user::list_impact::pre_create_window(pusersystem))
   //   {

   //      return false;

   //   }

   //   return true;

   //}

   void font_list_impact::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::show < font_list >::_001OnNcDraw(pgraphics);

   }


   void font_list_impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::show < font_list >::_001OnDraw(pgraphics);

   }


   //void font_list_impact::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)
   //{

   //   ::user::impact::route_command(pcommand);

   //}


   //void font_list_impact::on_command(::message::command * pcommand)
   //{

   //   ::user::impact::on_command(pcommand);

   //}


   void font_list_impact::on_timer(::timer * ptimer)
   {

      ::user::show < font_list >::on_timer(ptimer);

   //   ::user::form_impact::on_timer(ptimer);

   }


   //void font_list_impact::set_context_offset(::draw2d::graphics_pointer & pgraphics, int x, int y)
   //{

   //   ::user::list_impact::set_context_offset(pgraphics, x, y);

   //}


   //::int_point font_list_impact::get_context_offset()
   //{

   //   return ::user::list_impact::get_context_offset();

   //}


   //::double_size font_list_impact::get_total_size()
   //{

   //   return ::user::list_impact::get_total_size();

   //}


   //void font_list_impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
   //{

   //   form_impact::handle(ptopic, phandlercontext);

   //   list_impact::handle(ptopic, phandlercontext);

   //}


   //void font_list_impact::OnActivateImpact(bool bActivate, ::pointer<::user::impact>pActivateImpact, ::pointer<::user::impact>viewDeactive)
   //{
   //   //    UNUSED(pActivateImpact);   // unused in release builds

   //   if (bActivate && m_pcontrolEdit.is_null())
   //   {
   //      //ASSERT(pActivateImpact == this);

   //      // take the focus if this frame/::user::impact/pane is now active
   //      if (IsTopParentActive())
   //      {

   //         if (get_wnd()->m_pinteractionimpl)
   //         {

   //            ::pointer<::user::interaction>puiFocus = get_wnd()->m_pinteractionimpl->aaa_m_pacmeuserinteractionKeyboardFocus;

   //            if (puiFocus.is_null() || !is_ascendant_of(puiFocus, true))
   //            {

   //               get_wnd()->m_pinteractionimpl->aaa_m_pacmeuserinteractionKeyboardFocus = this;

   //            }

   //         }

   //      }

   //   }

   //}


   void font_list_impact::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::show < font_list >::on_layout(pgraphics);

   }


   //index font_list_impact::_001GetCurItem()
   //{

   //   if (m_pcontrolEdit.is_set())
   //   {

   //      return m_item.m_iItem;

   //   }

   //   return ::user::list_impact::_001GetCurItem();

   //}


} // namespace user



