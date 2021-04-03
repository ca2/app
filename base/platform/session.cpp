#include "framework.h"
#include "base/user/experience/_experience.h"
#include "acme/platform/static_setup.h"


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


   ::e_status session::initialize(::object * pobject)
   {

      auto estatus = ::axis::session::initialize(pobject);

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


   void session::on_instantiate_application(::apex::application* papp)
   {

      ::axis::session::on_instantiate_application(papp);

      papp->m_pbasesession = this;
      papp->m_pbasesystem = m_pbasesystem;

   }


   __namespace_session_factory(session);


} // namespace base



