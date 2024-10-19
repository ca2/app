#include "framework.h"
#include "form_list_impact.h"
#include "acme/constant/id.h"
#include "acme/handler/item.h"
#include "acme/handler/topic.h"
#include "acme/platform/application.h"
#include "acme/platform/context.h"
#include "acme/platform/session.h"
#include "acme/platform/system.h"
#include "acme/filesystem/filesystem/dir_context.h"
#include "aura/windowing/window.h"
#include "base/user/form/document.h"


namespace user
{


   form_list_impact::form_list_impact()
   {

   }


   form_list_impact::~form_list_impact()
   {

   }


   ::core::application* form_list_impact::get_app()
   {

      auto papplication = application();

      return ::is_set(papplication) ? papplication->m_pcoreapplication : nullptr;

   }


   ::core::session* form_list_impact::get_session()
   {

      auto pacmesession = session();

      return ::is_set(pacmesession) ? pacmesession->m_pcoresession : nullptr;

   }


   ::core::system* form_list_impact::get_system()
   {

      auto pacmesystem = system();

      return ::is_set(pacmesystem) ? pacmesystem->m_pcoresystem : nullptr;

   }


   ::base::user * form_list_impact::baseuser()
   {

      return ::user::impact::baseuser();

   }


   void form_list_impact::install_message_routing(::channel * pchannel)
   {

      ::user::form_impact::install_message_routing(pchannel);
      ::user::form_list::install_message_routing(pchannel);

   }


   void form_list_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      ::user::form_impact::handle(ptopic, pcontext);

      ::user::list_impact::handle(ptopic, pcontext);

      ////__update(::update)
      {

         if(ptopic->m_atom == ID_BROWSE)
         {

            if(!ptopic->payload(ID_FORM).is_empty())
            {

               string strMatter = dir()->matter(ptopic->payload(ID_FORM));

               if(get_document()->on_open_document(strMatter))
               {

                  m_strPath = ptopic->payload(ID_FORM);

               }

            }

         }
         else if(ptopic->m_atom == id_get_form_impact)
         {

            ptopic->payload(ID_FORM) = this;

         }

      }

      if(m_pcallback != nullptr)
      {

         ptopic->payload(ID_FORM) = this;

         m_pcallback->handle(ptopic, pcontext);

      }

   }


   void form_list_impact::initialize(::particle * pparticle)
   {

      //auto estatus = 
      
      ::user::form_list::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus =
      
      ::user::form_impact::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 
      
      ::user::list_impact::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void form_list_impact::destroy()
   {

      ::user::form_list::destroy();
      ::user::form_impact::destroy();
      ::user::list_impact::destroy();


   }


   //void form_list_impact::assert_ok() const
   //{

   //   form_list::assert_ok();
   //   form_impact::assert_ok();
   //   list_impact::assert_ok();

   //}


   //void form_list_impact::dump(dump_context & dumpcontext) const
   //{

   //   form_list::dump(dumpcontext);
   //   form_impact::dump(dumpcontext);
   //   list_impact::dump(dumpcontext);

   //}


   bool form_list_impact::pre_create_window(::user::system * pusersystem)
   {

      if (!::user::list_impact::pre_create_window(pusersystem))
      {

         return false;

      }

      return true;

   }


   void form_list_impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::list_impact::_001OnDraw(pgraphics);

   }


   void form_list_impact::_001CallOnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::list_impact::_001CallOnDraw(pgraphics);

   }


   void form_list_impact::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)
   {

      ::user::impact::route_command(pcommand);

   }


   void form_list_impact::on_command(::message::command* pcommand)
   {

      ::user::impact::on_command(pcommand);

   }


   void form_list_impact::_001OnTimer(::timer * ptimer)
   {

      ::user::list_impact::_001OnTimer(ptimer);

      ::user::form_impact::_001OnTimer(ptimer);

   }


   ::data::data * form_list_impact::_get_data(const ::atom & atom)
   {

      return ::user::list_impact::_get_data(atom);

   }


   //void form_list_impact::set_context_offset(::draw2d::graphics_pointer & pgraphics, int x, int y)
   //{

   //   ::user::list_impact::set_context_offset(pgraphics, x, y);

   //}

   void form_list_impact::set_context_offset(const ::point_f64 & point, ::user::enum_layout elayout)
   {

      ::user::list_impact::set_context_offset(point, elayout);

   }


   ::point_f64 form_list_impact::get_context_offset(::user::enum_layout elayout)
   {

      return ::user::list_impact::get_context_offset(elayout);

   }


   ::size_f64 form_list_impact::get_total_size(::user::enum_layout elayout)
   {

      return ::user::list_impact::get_total_size(elayout);

   }


   //void form_list_impact::handle(::topic * ptopic, ::context * pcontext)
   //{

   //   form_impact::handle(ptopic, pcontext);

   //   list_impact::handle(ptopic, pcontext);

   //}


   void form_list_impact::OnActivateImpact(bool bActivate, ::pointer<::user::impact>pActivateImpact, ::pointer<::user::impact>viewDeactive)
   {
      //    UNUSED(pActivateImpact);   // unused in release builds

      if (bActivate && m_pcontrolEdit.is_null())
      {
         //ASSERT(pActivateImpact == this);

         // take the focus if this frame/::user::impact/pane is now active
         if (IsTopParentActive())
         {

            if(get_wnd()->windowing_window())
            {

               ::pointer<::user::interaction>puiFocus = get_wnd()->windowing_window()->m_puserinteractionKeyboardFocus;

               if (puiFocus.is_null() || !is_ascendant_of(puiFocus, true))
               {

                  get_wnd()->windowing_window()->m_puserinteractionKeyboardFocus = this;

               }

            }

         }

      }

   }


   void form_list_impact::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::form_list::on_layout(pgraphics);

   }


   ::collection::index form_list_impact::_001GetCurItem()
   {

      if (m_pcontrolEdit.is_set())
      {

         return m_item.m_iItem;

      }

      return ::user::list_impact::_001GetCurItem();

   }


} // namespace user



