#include "framework.h"
#include "aura/user/_user.h"


namespace user
{


   void frame::_001OnSysCommand(::message::message * pmessage)
   {

      __pointer(::message::base) pbase(pmessage);

      //if (pbase->m_wparam == SC_SCREENSAVE)
      //{

      //   if (!_001CanEnterScreenSaver())
      //   {

      //      pbase->m_bRet = true;

      //      pbase->m_lresult = 0;

      //      return;

      //   }

      //}

      ////if (m_bWindowFrame)
      //{

      //   if (pbase->m_wparam == SC_MAXIMIZE)
      //   {

      //      INFO("SC_MAXIMIZE");

      //      display(e_display_zoomed);

      //      set_need_redraw();

      //      pbase->m_bRet = true;

      //      pbase->m_lresult = 0;

      //   }
         //else if (pbase->m_wparam == SC_RESTORE)
         //{

         //   INFO("SC_RESTORE");

         //   if (layout().sketch().display() == e_display_default)
         //   {

         //      display_previous_restore();

         //   }
         //   else
         //   {

         //      display(m_edisplayRestore);

         //   }

         //   set_need_redraw();

         //   pbase->m_bRet = true;

         //   pbase->m_lresult = 0;

         //}
         //else if (pbase->m_wparam == SC_MINIMIZE)
         //{

            //INFO("SC_MINIMIZE");

            //display_system_minimize();

            //set_need_redraw();

            //pbase->m_bRet = true;

           // pbase->m_lresult = 0;

         //}

      //}

   }


   bool frame::_001Restore()
   {

      if (layout().sketch().display() == e_display_default)
      {

         display_previous_restore();

      }
      else
      {

         display(m_edisplayRestore);

      }

      set_need_redraw();

      post_redraw();

      return true;

   }


} // namespace user



