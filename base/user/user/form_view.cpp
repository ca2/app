#include "framework.h"
#include "base/user/user/_user.h"
#include "aura/update.h"
#include "acme/constant/id.h"


namespace user
{


   form_view::form_view()
   {

   }


   form_view::~form_view()
   {

   }


   void form_view::handle(::subject * psubject, ::context * pcontext)
   {

      //::user::impact::handle(psubject, pcontext);

      form_window::handle(psubject, pcontext);

      if (psubject->m_id == ::e_subject_form_initialize && psubject->user_interaction() == this)
      {

         if (get_document())
         {

            //call_sync(get_document()->m_mapMethod["load"]);
            get_document()->call_routines_with_id("load");

         }

      }
      else if (psubject->id() == id_browse)
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

         m_pcallback->handle(psubject, pcontext);

      }

   }


   bool form_view::Navigate(const ::string & pszUrl)
   {

      __UNREFERENCED_PARAMETER(pszUrl);

      return false;

   }


   void form_view::open_document(const ::payload & payloadFile)
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

      bool bHtml = psystem->m_phtml->defer_get_html(strHtml, pathHtml, this, payloadFile);

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

               m_pform->start_destroying_window();

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

//         __pointer(::user::form_view) pview = pformOld;

         //if (pview)
         //{

         //   pview->set_finish();

         //   //get_document()->erase_view(pview);

         //}

         //pformOld->destroy_window();

         //pformOld.release();

         pformOld->set_finish();

      }

      if (bOk)
      {

         set_need_layout();

         set_need_redraw();

         post_redraw();

      }

      return bOk;

   }


   void form_view::open_html(const ::string & str)
   {

      synchronous_lock synchronouslock(mutex());

      auto pformOld = m_pform;

      void     estatus = error_failed;

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

      if (m_pform && m_pform != this)
      {

         auto rectangleClient = get_client_rect();

         m_pform->place(rectangleClient);

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


   //void form_view::handle(::subject * psubject, ::context * pcontext)
   //{

   //   form_window::handle(psubject, pcontext);

   //   if (psubject->m_id == ::e_subject_form_initialize && psubject->user_interaction() == this)
   //   {

   //      if (get_document())
   //      {

   //         //call_sync(get_document()->m_mapMethod["load"]);
   //         get_document()->call_routine("load");

   //      }

   //   }

   //}


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


   ::form_document * form_view::get_document()
   {
      
      return dynamic_cast < ::form_document * >(::user::impact::get_document());
      
   }


} // namespace user



