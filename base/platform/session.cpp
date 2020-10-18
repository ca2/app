#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/experience/_experience.h"
#endif
#include "apex/platform/static_setup.h"


namespace base
{


   session::session()
   {

      m_pbasesession = this;

   }


   session::~session()
   {

      output_debug_string("aura::session::~session()");

   }


   ::estatus session::initialize(::layered * pobjectContext)
   {

      auto estatus = ::thread::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      m_bIfs                           = true;

      m_bProgrammerMode                = false;

      m_bSystemSynchronizedCursor      = true;

      m_bSystemSynchronizedScreen      = true;

      m_pimplPendingFocus2             = nullptr;

      set_context_session(this);

      if (get_context_system() != nullptr)
      {

         m_bSystemSynchronizedCursor   = get_context_system()->m_bSystemSynchronizedCursor;

         m_bSystemSynchronizedScreen   = get_context_system()->m_bSystemSynchronizedScreen;

      }

      m_ecursorDefault                 = cursor_arrow;

      m_ecursor                        = cursor_default;

      m_ecursorDefault                 = cursor_arrow;

      m_ecursor                        = cursor_default;

      m_bDrawCursor                    = false;

      m_pappCurrent                    = nullptr;

      m_puiLastLButtonDown             = nullptr;

      m_pmapKeyPressed                 = nullptr;

      m_puiMouseMoveCapture            = nullptr;

      m_iMainMonitor                   = -1;

      m_bZipIsDir2                     = true;

      m_iEdge                          = 0;

      m_bShowPlatform                  = false;

      m_pappCurrent                    = nullptr;


      //m_strAppId = "base_session";
//m_strAppName = "base_session";
//m_strBaseSupportId = "base_session";
//m_strInstallToken = "base_session";

      m_iMainMonitor = -1;

      m_puiCapture = nullptr;

      m_puiMouseMoveCapture = nullptr;

      m_ecursorDefault = cursor_arrow;

      m_ecursor = cursor_default;

      m_puiMouseMoveCapture = nullptr;

      return estatus;

   }



   __namespace_session_factory(session);


} // namespace base



