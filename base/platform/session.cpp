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

      auto estatus = ::axis::session::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      m_ecursorDefault                 = cursor_arrow;

      m_ecursor                        = cursor_default;

      m_ecursorDefault                 = cursor_arrow;

      m_ecursor                        = cursor_default;

      m_bDrawCursor                    = false;

      m_puiLastLButtonDown             = nullptr;

      m_pmapKeyPressed                 = nullptr;

      m_puiMouseMoveCapture            = nullptr;

      m_bShowPlatform                  = false;

      m_pappCurrent                    = nullptr;

      m_puiCapture = nullptr;

      m_puiMouseMoveCapture = nullptr;

      m_ecursorDefault = cursor_arrow;

      m_ecursor = cursor_default;

      m_puiMouseMoveCapture = nullptr;

      return estatus;

   }



   __namespace_session_factory(session);


} // namespace base



