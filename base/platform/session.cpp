#include "framework.h"
#include "base/user/experience/_experience.h"
#include "apex/platform/static_setup.h"


namespace base
{


   session::session()
   {

   }


   session::~session()
   {

      output_debug_string("aura::session::~session()");

   }


   ::e_status session::initialize(::context_object * pcontextobject)
   {

      auto estatus = ::axis::session::initialize(pcontextobject);

      if (!estatus)
      {

         return estatus;

      }

      m_puiLastLButtonDown             = nullptr;

      m_pmapKeyPressed                 = nullptr;

      m_puiMouseMoveCapture            = nullptr;

      m_bShowPlatform                  = false;

      m_papplicationCurrent                    = nullptr;

      m_puiMouseMoveCapture = nullptr;

      return estatus;

   }



   __namespace_session_factory(session);


} // namespace base



