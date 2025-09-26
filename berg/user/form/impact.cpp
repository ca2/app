#include "framework.h"
#include "document.h"
#include "impact.h"
#include "acme/constant/happening.h"
#include "acme/constant/id.h"
#include "acme/handler/topic.h"
#include "axis/html/html/html.h"
#include "berg/platform/system.h"
#include "berg/platform/session.h"
#include "berg/user/user/user.h"


namespace user
{


   form_impact::form_impact()
   {

   }


   form_impact::~form_impact()
   {

   }


   void form_impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      //::user::impact::handle(ptopic, phandlercontext);

      form_window::handle(ptopic, phandlercontext);

      if (ptopic->id() == ::id_form_initialize && ptopic->user_interaction() == this)
      {

         //throw ::exception(todo);

         if (get_document())
         {

            //call_sync(get_document()->m_mapMethod["load"]);
            get_document()->call_procedures(e_happening_load);

         }

      }
      else if (ptopic->id() == id_browse)
      {

         if (!ptopic->payload(id_form).is_empty())
         {

            if (get_document()->on_open_document(ptopic->payload(id_form)))
            {

               m_strPath = ptopic->payload(id_form);

            }

         }

      }
      else if (ptopic->id() == id_get_form_impact)
      {

         ptopic->payload(id_form) = this;

      }
      else if (ptopic->id() == id_incoming_document)
      {

         auto strOpenOnCreate = m_strOpenOnCreate;

         m_strOpenOnCreate.empty();

         if (strOpenOnCreate.has_character())
         {

            get_document()->on_open_document(strOpenOnCreate);

         }

      }

      if(m_pcallback != nullptr)
      {

         ptopic->payload(id_form) = this;

         m_pcallback->handle(ptopic, phandlercontext);

      }

   }


   bool form_impact::Navigate(const ::scoped_string & scopedstrUrl)
   {

      __UNREFERENCED_PARAMETER(scopedstrUrl);

      return false;

   }


   bool form_impact::open_document(const ::payload & payloadFile)
   {

      auto psystem = system();

      psystem->defer_create_html();

      ::pointer<::user::form>pformOld;

      ::pointer<::user::form>pformNew;

      if (m_pform != this)
      {

         pformOld = m_pform;

      }

      m_pform.release();

      string strHtml;

      ::file::path pathHtml;

      bool bHtml = psystem->m_phtml->defer_get_html(strHtml, pathHtml, this, payloadFile);

      bool bOk = true;

      if(bHtml)
      {

         bOk = false;

         if (pformOld)
         {

            pformOld->set_finish();

         }

         pformNew = create_impact(user()->get_html_impact_type());

         if(pformNew)
         {

            static int s_iFormSerial = 1;

            pformNew->payload("form_serial") = s_iFormSerial;

            s_iFormSerial++;

            pformNew->set_parent_form(this);

            if (m_pcallback)
            {

               pformNew->set_form_callback(m_pcallback);

            }

            if (strHtml.has_character())
            {

               pformNew->open_html(strHtml);

               bOk = true;

            }
            else
            {

               //try
               //{

                  pformNew->open_document(pathHtml);

                  bOk = true;

               //}
               //catch (...)
               //{

                 // pformNew->start_destroying_window();

                  //pformNew.release();

               //}

            }

         }

         if (bOk)
         {

            m_pform = pformNew;

         }

      }
      else
      {

         m_pform.release();

      }

      if (bOk)
      {

         set_need_layout();

         set_need_redraw();

         post_redraw();

      }

      return bOk;

   }


   bool form_impact::open_html(const ::scoped_string & scopedstr)
   {

      synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      auto pformOld = m_pform;

      bool bOk = true;

      //::pointer<::user::form_impact>pformChild = create_impact(psession->userex()->get_html_impact_type());
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


   void form_impact::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      BASE_VIEW::on_layout(pgraphics);

      if (m_pform && m_pform != this)
      {

         auto rectangleX = this->rectangle();

         m_pform->place(rectangleX);

         m_pform->display();

         m_pform->set_reposition();

         m_pform->set_need_layout();

         m_pform->set_need_redraw();

      }

   }


   void form_impact::soft_reload()
   {

      if(m_pform)
      {

         m_pform->soft_reload();

      }

   }


   //void form_impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
   //{

   //   form_window::handle(ptopic, phandlercontext);

   //   if (ptopic->id() == ::id_form_initialize && ptopic->user_interaction() == this)
   //   {

   //      if (get_document())
   //      {

   //         //call_sync(get_document()->m_mapMethod["load"]);
   //         get_document()->call_routine("load");

   //      }

   //   }

   //}


   void form_impact::set_need_load_form_data()
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


   ::form_document * form_impact::get_document()
   {
      
      return dynamic_cast < ::form_document * >(::user::impact::get_document());
      
   }


} // namespace user



