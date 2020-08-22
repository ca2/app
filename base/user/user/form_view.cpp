#include "framework.h"
#include "aura/update.h"
#include "aura/const/id.h"
//#include "core/user/userex/_userex.h"


namespace user
{


   form_view::form_view()
   {
      
   }


   form_view::~form_view()
   {

   }


   void form_view::update(::update * pupdate)
   {

      ::user::impact::update(pupdate);

      if (pupdate->m_id == id_browse)
      {

         if (!pupdate->value(id_form).is_empty())
         {

            if (get_document()->on_open_document(pupdate->value(id_form)))
            {

               m_strPath = pupdate->value(id_form);

            }

         }

      }
      else if (pupdate->m_id == id_get_form_view)
      {

         pupdate->value(id_form) = this;

      }

      if(m_pcallback != nullptr)
      {

         pupdate->value(id_form) = this;

         m_pcallback->call_update(pupdate);

      }

   }


   bool form_view::Navigate(const char * pszUrl)
   {

      UNREFERENCED_PARAMETER(pszUrl);

      return false;

   }


   bool form_view::open_document(const var & varFile)
   {
      
      auto pformOld = m_pformChild;
      
      ::file::path path = varFile.get_file_path();
      
      bool bHtml = path.ends_ci(".html") || path.ends_ci(".htm") || path.ends_ci(".xhtml");
      
      bool bOk = true;

      if(bHtml)
      {
         
         bOk = false;
      
         m_pformChild = create_view(Session.user()->get_html_view_type());
         
         if(m_pformChild)
         {
         
            m_pformChild->set_parent_form(this);

            m_pformChild->set_form_callback(m_pcallback);

            if(m_pformChild->open_document(varFile))
            {
               
               bOk = true;
               
            }
            else
            {
             
               m_pformChild->DestroyWindow();
               
               m_pformChild.release();
               
            }
            
         }
         
      }
      else
      {
         
         m_pformChild.release();
         
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

   
   ::estatus     form_view::open_html(const string & str)
   {
      
      sync_lock sl(mutex());
      
      auto pformOld = m_pformChild;
      
      ::estatus     estatus = error_failed;
      
      //__pointer(::user::form_view) pformChild = create_view(Session.userex()->get_html_view_type());
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
      //      m_pformChild = pformChild;
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

      if (m_pformChild)
      {

         auto rectClient = get_client_rect();

         m_pformChild->place(rectClient);

         m_pformChild->display();

         m_pformChild->set_reposition();

         m_pformChild->set_need_layout();

         m_pformChild->set_need_redraw();

      }


   }
   
   
   void form_view::soft_reload()
   {
      
      if(m_pformChild)
      {
      
         m_pformChild->soft_reload();
         
      }
      
   }


   void form_view::on_control_event(::user::control_event * pevent)
   {

      form_window::on_control_event(pevent);

      if (pevent->m_eevent == ::user::event_form_initialize && pevent->m_puie == this)
      {

         if (get_document())
         {

            call_sync(get_document()->m_mapRunnablea["load"]);

         }

      }

   }


   void form_view::set_need_load_form_data()
   {

      if (m_pformChild)
      {

         m_pformChild->set_need_load_form_data();

      }
      else
      {

         ::user::form_window::set_need_load_form_data();

      }

   }


} // namespace user



