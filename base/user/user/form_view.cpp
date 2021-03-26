#include "framework.h"
#include "base/user/user/_user.h"
#include "aura/update.h"
#include "acme/const/id.h"


namespace user
{


   form_view::form_view()
   {

   }


   form_view::~form_view()
   {

   }


   void form_view::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

      ::user::impact::on_subject(psubject, pcontext);

      if (psubject->id() == id_browse)
      {

         if (!psubject->payload(id_form).is_empty())
         {

            if (get_document()->on_open_document(psubject->payload(id_form)))
            {

               m_strPath = psubject->payload(id_form);

            }

         }

      }
      else if (psubject->id() == id_get_form_view)
      {

         psubject->payload(id_form) = this;

      }

      if(m_pcallback != nullptr)
      {

         psubject->payload(id_form) = this;

         m_pcallback->process(psubject);

      }

   }


   bool form_view::Navigate(const char * pszUrl)
   {

      UNREFERENCED_PARAMETER(pszUrl);

      return false;

   }


   ::e_status form_view::open_document(const ::payload & varFile)
   {

      auto psystem = m_psystem->m_pbasesystem;

      psystem->defer_create_html();

      __pointer(::user::form) pformOld;

      if (m_pform != this)
      {

         pformOld = m_pform;

      }

      string strHtml;

      ::file::path pathHtml;

      bool bHtml = psystem->m_phtml->defer_get_html(strHtml, pathHtml, this, varFile);

      bool bOk = true;

      if(bHtml)
      {

         bOk = false;

         auto psession = get_session();

         m_pform = create_view(psession->user()->get_html_view_type());

         if(m_pform)
         {

            m_pform->set_parent_form(this);

            m_pform->set_form_callback(m_pcallback);

            if (strHtml.has_char())
            {

               if (m_pform->open_html(strHtml))
               {

                  bOk = true;

               }

            }
            else if (m_pform->open_document(pathHtml))
            {

               bOk = true;

            }
            else
            {

               m_pform->DestroyWindow();

               m_pform.release();

            }

         }

      }
      else
      {

         m_pform.release();

      }

      if(pformOld)
      {

         __pointer(::user::form_view) pview = pformOld;

         if (pview)
         {

            get_document()->remove_view(pview);

         }

         pformOld->DestroyWindow();

         pformOld.release();

      }

      if (bOk)
      {

         set_need_layout();

         set_need_redraw();

         post_redraw();

      }

      return bOk;

   }


   ::e_status form_view::open_html(const string & str)
   {

      synchronization_lock synchronizationlock(mutex());

      auto pformOld = m_pform;

      ::e_status     estatus = error_failed;

      //__pointer(::user::form_view) pformChild = create_view(psession->userex()->get_html_view_type());
      //
      //if(pformChild)
      //{
      //
      //   pformChild->set_form_callback(pformOld->get_form_callback());
      //
      //   if(pformChild->open_html(str))
      //   {
      //
      //      try
      //      {
      //
      //         if(pformOld)
      //         {
      //
      //            pformOld->hide();
      //
      //            pformOld->DestroyWindow();
      //
      //            pformOld.release();
      //
      //         }
      //
      //      }
      //      catch (...)
      //      {
      //
      //      }
      //
      //      m_pform = pformChild;
      //
      //      set_need_layout();

      //      set_need_redraw();

      //      post_redraw();

      //      estatus = success;
      //
      //   }
      //   else
      //   {
      //
      //      pformChild->DestroyWindow();
      //
      //      pformChild.release();
      //
      //   }
      //
      //}

      return estatus;

   }


   void form_view::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      BASE_VIEW::on_layout(pgraphics);

      if (m_pform)
      {

         auto rectClient = get_client_rect();

         m_pform->place(rectClient);

         m_pform->display();

         m_pform->set_reposition();

         m_pform->set_need_layout();

         m_pform->set_need_redraw();

      }

   }


   void form_view::soft_reload()
   {

      if(m_pform)
      {

         m_pform->soft_reload();

      }

   }


   void form_view::on_control_event(::user::control_event * pevent)
   {

      form_window::on_control_event(pevent);

      if (pevent->m_eevent == ::user::e_event_form_initialize && pevent->m_puie == this)
      {

         if (get_document())
         {

            //call_sync(get_document()->m_mapMethod["load"]);
            get_document()->call_routine("load");

         }

      }

   }


   void form_view::set_need_load_form_data()
   {

      if (m_pform)
      {

         m_pform->set_need_load_form_data();

      }
      else
      {

         ::user::form_window::set_need_load_form_data();

      }

   }


} // namespace user



