#include "framework.h"
#include "form_list_impact.h"
#include "base/user/form/document.h"
#include "aura/user/user/interaction_impl.h"


namespace user
{


   form_list_impact::form_list_impact()
   {

   }


   form_list_impact::~form_list_impact()
   {

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

         if(ptopic->m_atom == id_browse)
         {

            if(!ptopic->payload(id_form).is_empty())
            {

               string strMatter = m_pcontext->m_papexcontext->dir().matter(ptopic->payload(id_form));

               if(get_document()->on_open_document(strMatter))
               {

                  m_strPath = ptopic->payload(id_form);

               }

            }

         }
         else if(ptopic->m_atom == id_get_form_impact)
         {

            ptopic->payload(id_form) = this;

         }

      }

      if(m_pcallback != nullptr)
      {

         ptopic->payload(id_form) = this;

         m_pcallback->handle(ptopic, pcontext);

      }

   }


   void form_list_impact::initialize(::object * pobject)
   {

      //auto estatus = 
      
      ::user::form_list::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus =
      
      ::user::form_impact::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 
      
      ::user::list_impact::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void form_list_impact::assert_ok() const
   {

      form_list::assert_ok();
      form_impact::assert_ok();
      list_impact::assert_ok();

   }


   void form_list_impact::dump(dump_context & dumpcontext) const
   {

      form_list::dump(dumpcontext);
      form_impact::dump(dumpcontext);
      list_impact::dump(dumpcontext);

   }


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


   void form_list_impact::set_context_offset(::draw2d::graphics_pointer & pgraphics, int x, int y)
   {

      ::user::list_impact::set_context_offset(pgraphics, x, y);

   }


   ::point_i32 form_list_impact::get_context_offset()
   {

      return ::user::list_impact::get_context_offset();

   }


   ::size_f64 form_list_impact::get_total_size()
   {

      return ::user::list_impact::get_total_size();

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

            if(get_wnd()->m_pinteractionimpl)
            {

               ::pointer<::user::interaction>puiFocus = get_wnd()->m_pinteractionimpl->m_puserinteractionKeyboardFocus;

               if (puiFocus.is_null() || !is_ascendant_of(puiFocus, true))
               {

                  get_wnd()->m_pinteractionimpl->m_puserinteractionKeyboardFocus = this;

               }

            }

         }

      }

   }


   void form_list_impact::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::form_list::on_layout(pgraphics);

   }


   index form_list_impact::_001GetCurItem()
   {

      if (m_pcontrolEdit.is_set())
      {

         return m_iItem;

      }

      return ::user::list_impact::_001GetCurItem();

   }


} // namespace user



