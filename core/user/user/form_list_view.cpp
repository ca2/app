#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/user/_user.h"
#endif
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


   void form_list_view::update(::update * pupdate)
   {

      ::user::form_view::update(pupdate);

      ::user::list_view::update(pupdate);

      ////__update(::update)
      {

         if(pupdate->m_id == id_browse)
         {

            if(!pupdate->value(id_form).is_empty())
            {

               string strMatter = Context.dir().matter(pupdate->value(id_form));

               if(get_document()->on_open_document(strMatter))
               {

                  m_strPath = pupdate->value(id_form);

               }

            }

         }
         else if(pupdate->m_id == id_get_form_view)
         {

            pupdate->value(id_form) = this;

         }

      }

      if(m_pcallback != nullptr)
      {

         pupdate->value(id_form) = this;

         m_pcallback->update(pupdate);

      }

   }


   ::estatus form_list_view::initialize(::layered * pobjectContext)
   {

      auto estatus = ::user::form_list::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }
         
      estatus = ::user::form_view::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      estatus = ::user::list_view::initialize(pobjectContext);

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


   bool form_list_view::pre_create_window(::user::create_struct & createstruct)
   {

      if (!::user::list_view::pre_create_window(createstruct))
      {

         return false;

      }

      return true;

   }


   void form_list_view::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::list_view::_001OnDraw(pgraphics);

   }


   void form_list_view::route_command_message(::user::command * pcommand)
   {

      ::user::impact::route_command_message(pcommand);

   }


   void form_list_view::on_command(::user::command* pcommand)
   {

      ::user::impact::on_command(pcommand);

   }


   void form_list_view::_001OnTimer(::timer * ptimer)
   {

      ::user::list_view::_001OnTimer(ptimer);

      ::user::form_view::_001OnTimer(ptimer);

   }

   void form_list_view::set_viewport_offset(int x, int y)
   {

      ::user::list_view::set_viewport_offset(x, y);

   }


   ::point form_list_view::get_viewport_offset()
   {

      return ::user::list_view::get_viewport_offset();

   }


   ::sized form_list_view::get_total_size()
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

               __pointer(::user::interaction) puiFocus = get_wnd()->m_pimpl2->m_pprimitiveFocus;

               if (puiFocus.is_null() || !is_ascendant_of(puiFocus, true))
               {

                  get_wnd()->m_pimpl2->m_pprimitiveFocus = this;

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

         return m_iEditItem;

      }

      return ::user::list_view::_001GetCurItem();

   }


} // namespace user



