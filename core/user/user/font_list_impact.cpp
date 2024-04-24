// Created by camilo on 2023-08-28 00:49 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "font_list_impact.h"
//#include "acme/constant/id.h"
//#include "acme/handler/item.h"
//#include "acme/platform/application.h"
//#include "acme/platform/context.h"
//#include "acme/platform/session.h"
//#include "acme/platform/system.h"
//#include "acme/filesystem/filesystem/dir_context.h"
#include "aura/graphics/write_text/font_list.h"
//#include "base/user/form/document.h"


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

   //   return ::is_set(papplication) ? papplication->m_pcoreapplication : nullptr;

   //}


   //::core::session * font_list_impact::get_session()
   //{

   //   auto pacmesession = session();

   //   return ::is_set(pacmesession) ? pacmesession->m_pcoresession : nullptr;

   //}


   //::core::system * font_list_impact::get_system()
   //{

   //   auto pacmesystem = system();

   //   return ::is_set(pacmesystem) ? pacmesystem->m_pcoresystem : nullptr;

   //}


   //::base::user * font_list_impact::baseuser()
   //{

   //   return ::user::impact::baseuser();

   //}


   void font_list_impact::install_message_routing(::channel * pchannel)
   {

      ::user::show < font_list >::install_message_routing(pchannel);
      //::user::font_list::install_message_routing(pchannel);

   }


   void font_list_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      ::user::show < font_list > ::handle(ptopic, pcontext);

      //::user::list_impact::handle(ptopic, pcontext);

      //////__update(::update)
      //{

      //   if (ptopic->m_atom == ID_BROWSE)
      //   {

      //      if (!ptopic->payload(ID_FORM).is_empty())
      //      {

      //         string strMatter = dir()->matter(ptopic->payload(ID_FORM));

      //         if (get_document()->on_open_document(strMatter))
      //         {

      //            m_strPath = ptopic->payload(ID_FORM);

      //         }

      //      }

      //   }
      //   else if (ptopic->m_atom == id_get_form_impact)
      //   {

      //      ptopic->payload(ID_FORM) = this;

      //   }

      //}

      //if (m_pcallback != nullptr)
      //{

      //   ptopic->payload(ID_FORM) = this;

      //   m_pcallback->handle(ptopic, pcontext);

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


   void font_list_impact::_001OnTimer(::timer * ptimer)
   {

      ::user::show < font_list >::_001OnTimer(ptimer);

   //   ::user::form_impact::_001OnTimer(ptimer);

   }


   //void font_list_impact::set_context_offset(::draw2d::graphics_pointer & pgraphics, int x, int y)
   //{

   //   ::user::list_impact::set_context_offset(pgraphics, x, y);

   //}


   //::point_i32 font_list_impact::get_context_offset()
   //{

   //   return ::user::list_impact::get_context_offset();

   //}


   //::size_f64 font_list_impact::get_total_size()
   //{

   //   return ::user::list_impact::get_total_size();

   //}


   //void font_list_impact::handle(::topic * ptopic, ::context * pcontext)
   //{

   //   form_impact::handle(ptopic, pcontext);

   //   list_impact::handle(ptopic, pcontext);

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

   //            ::pointer<::user::interaction>puiFocus = get_wnd()->m_pinteractionimpl->m_puserinteractionKeyboardFocus;

   //            if (puiFocus.is_null() || !is_ascendant_of(puiFocus, true))
   //            {

   //               get_wnd()->m_pinteractionimpl->m_puserinteractionKeyboardFocus = this;

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



