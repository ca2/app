#include "framework.h"
//#include "base/user/user/_user.h"
#include "aura/update.h"
#include "acme/id.h"


namespace user
{


   form_view::form_view()
   {

   }


   form_view::~form_view()
   {

   }


   void form_view::handle(::topic * ptopic, ::context * pcontext)
   {

      //::user::impact::handle(ptopic, pcontext);

      form_window::handle(ptopic, pcontext);

      if (ptopic->m_atom == ::id_form_initialize && ptopic->user_interaction() == this)
      {

         if (get_document())
         {

            //call_sync(get_document()->m_mapMethod["load"]);
            get_document()->call_routines_with_id("load");

         }

      }
      else if (ptopic->m_atom == id_browse)
      {

         if (!ptopic->payload(id_form).is_empty())
         {

            if (get_document()->on_open_document(ptopic->payload(id_form)))
            {

               m_strPath = ptopic->payload(id_form);

            }

         }

      }
      else if (ptopic->m_atom == id_get_form_view)
      {

         ptopic->payload(id_form) = this;

      }
      else if (ptopic->m_atom == id_new_document)
      {

         auto strOpenOnCreate = m_strOpenOnCreate;

         m_strOpenOnCreate.Empty();

         if (strOpenOnCreate.has_char())
         {

            get_document()->on_open_document(strOpenOnCreate);

         }

      }

      if(m_pcallback != nullptr)
      {

         ptopic->payload(id_form) = this;

         m_pcallback->handle(ptopic, pcontext);

      }

   }


   bool form_view::Navigate(const ::string & pszUrl)
   {

      __UNREFERENCED_PARAMETER(pszUrl);

      return false;

   }


   bool form_view::open_document(const ::payload & payloadFile)
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

            if (m_pcallback)
            {

               m_pform->set_form_callback(m_pcallback);

            }

            if (strHtml.has_char())
            {

               m_pform->open_html(strHtml);
               //if ()
               {

                  bOk = true;

               }

            }
            else
            {

               try
               {

                  m_pform->open_document(pathHtml);

                  bOk = true;

               }
               catch (...)
               {

                  m_pform->start_destroying_window();

                  m_pform.release();

               }

            }

         }

      }
      else
      {

         m_pform.release();

      }

      if(pformOld)
      {

//         __pointer(::user::form_view) pimpact = pformOld;

         //if (pimpact)
         //{

         //   pimpact->set_finish();

         //   //get_document()->erase_view(pimpact);

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


   bool form_view::open_html(const ::string & str)
   {

      synchronous_lock synchronouslock(mutex());

      auto pformOld = m_pform;

      bool bOk = true;

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

      return bOk;

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


   //void form_view::handle(::topic * ptopic, ::context * pcontext)
   //{

   //   form_window::handle(ptopic, pcontext);

   //   if (ptopic->m_atom == ::id_form_initialize && ptopic->user_interaction() == this)
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



