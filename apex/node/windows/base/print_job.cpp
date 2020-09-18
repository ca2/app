#include "framework.h" 
#include "apex/user/print_job.h"
#include "_windows.h"


namespace windows
{


   print_job::print_job()
   {

   }


   print_job::~print_job()
   {

   }

   //void print_job::construct_print_job(::layered * pobjectContext)
   //{

   //   construct_user_job(pobjectContext);

   //}

   ::estatus     print_job::run()
   {

      if (!m_phprinter->is_opened())
      {
         // TODO:
         // m_printer.open(&callback_form);
         __throw(::exception::exception("printer not opened"));
      }

      if (m_puserinteraction == nullptr)
      {
         __throw(::exception::exception("a view should collaborate"));
      }

      ::draw2d::graphics_pointer & pgraphics = m_phprinter->create_graphics();

      // xxx
      ::image_pointer pimage;


      DOCINFOW docinfo;
      __memset(&docinfo, 0, sizeof(docinfo));
      docinfo.cbSize = sizeof(docinfo);
      pgraphics->StartDocW(&docinfo);

      i32 iPageCount = m_puserinteraction->get_total_page_count(this);
      i32 iPageEnd = -1;
      if (m_iPageStart < 0)
         m_iPageStart = 0;
      if (m_iPageCount >= 0)
      {
         iPageEnd = min(m_iPageStart + m_iPageCount - 1, iPageCount - 1);
      }
      else
      {
         iPageEnd = iPageCount - 1;
      }

      pgraphics->m_pjob = this;
      for (m_iPrintingPage = m_iPageStart; m_iPrintingPage <= iPageEnd; m_iPrintingPage++)
      {
         pgraphics->StartPage();
         if (m_bCancel)
         {
            pgraphics->AbortDoc();

            m_result.add(error_failed);

            return error_cancelled;
         }
         m_puserinteraction->_001OnDraw(pgraphics);
         if (m_bCancel)
         {
            pgraphics->AbortDoc();

            m_result.add(error_failed);

            return error_cancelled;

         }
         pgraphics->EndPage();
         if (m_bCancel)
         {

            pgraphics->AbortDoc();

            m_result.add(error_failed);

            return error_cancelled;

         }

      }

      pgraphics->EndDoc();

      return ::success;

   }


} // namespace windows





