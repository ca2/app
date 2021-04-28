#include "framework.h"
#include "core/user/user/_user.h"
#include "aura/update.h"
#include "acme/const/id.h"


namespace user
{


   form_list_view::form_list_view()
   {

   }


   form_list_view::~form_list_view()
   {

   }


   void form_list_view::install_message_routing(::channel * pchannel)
   {

      ::user::form_view::install_message_routing(pchannel);
      ::user::form_list::install_message_routing(pchannel);

   }


   void form_list_view::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

      ::user::form_view::on_subject(psubject, pcontext);

      ::user::list_view::on_subject(psubject, pcontext);

      ////__update(::update)
      {

         if(psubject->id() == id_browse)
         {

            if(!psubject->payload(id_form).is_empty())
            {

               string strMatter = m_pcontext->m_papexcontext->dir().matter(psubject->payload(id_form));

               if(get_document()->on_open_document(strMatter))
               {

                  m_strPath = psubject->payload(id_form);

               }

            }

         }
         else if(psubject->id() == id_get_form_view)
         {

            psubject->payload(id_form) = this;

         }

      }

      if(m_pcallback != nullptr)
      {

         psubject->payload(id_form) = this;

         m_pcallback->process(psubject);

      }

   }


   ::e_status form_list_view::initialize(::object * pobject)
   {

      auto estatus = ::user::form_list::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      estatus = ::user::form_view::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      estatus = ::user::list_view::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   void form_list_view::assert_valid() const
   {

      form_list::assert_valid();
      form_view::assert_valid();
      list_view::assert_valid();

   }


   void form_list_view::dump(dump_context & dumpcontext) const
   {

      form_list::dump(dumpcontext);
      form_view::dump(dumpcontext);
      list_view::dump(dumpcontext);

   }


   bool form_list_view::pre_create_window(::user::system * pusersystem)
   {

      if (!::user::list_view::pre_create_window(pusersystem))
      {

         return false;

      }

      return true;

   }


   void form_list_view::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::list_view::_001OnDraw(pgraphics);

   }


   void form_list_view::route_command_message(::message::command * pcommand)
   {

      ::user::impact::route_command_message(pcommand);

   }


   void form_list_view::on_command(::message::command* pcommand)
   {

      ::user::impact::on_command(pcommand);

   }


   void form_list_view::_001OnTimer(::timer * ptimer)
   {

      ::user::list_view::_001OnTimer(ptimer);

      ::user::form_view::_001OnTimer(ptimer);

   }


   void form_list_view::set_viewport_offset(::draw2d::graphics_pointer & pgraphics, int x, int y)
   {

      ::user::list_view::set_viewport_offset(pgraphics, x, y);

   }


   ::point_i32 form_list_view::get_viewport_offset()
   {

      return ::user::list_view::get_viewport_offset();

   }


   ::size_f64 form_list_view::get_total_size()
   {

      return ::user::list_view::get_total_size();

   }


   void form_list_view::on_control_event(::user::control_event * pevent)
   {

      form_view::on_control_event(pevent);

      list_view::on_control_event(pevent);

   }


   void form_list_view::OnActivateView(bool bActivate, __pointer(::user::impact) pActivateView, __pointer(::user::impact) pviewDeactive)
   {
      //    UNUSED(pActivateView);   // unused in release builds

      if (bActivate && m_pcontrolEdit.is_null())
      {
         //ASSERT(pActivateView == this);

         // take the focus if this frame/::user::impact/pane is now active
         if (IsTopParentActive())
         {

            if(get_wnd()->m_pimpl2)
            {

               __pointer(::user::interaction) puiFocus = get_wnd()->m_pimpl2->m_puserinteractionFocus1;

               if (puiFocus.is_null() || !is_ascendant_of(puiFocus, true))
               {

                  get_wnd()->m_pimpl2->m_puserinteractionFocus1 = this;

               }

            }

         }

      }

   }


   void form_list_view::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::form_list::on_layout(pgraphics);

   }


   index form_list_view::_001GetCurItem()
   {

      if (m_pcontrolEdit.is_set())
      {

         return m_iItem;

      }

      return ::user::list_view::_001GetCurItem();

   }


} // namespace user



