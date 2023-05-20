#include "framework.h"
#include "session.h"
#include "apex/platform/application.h"
////#include "base/user/experience/_component.h"
#include "acme/platform/system_setup.h"
#include "aura/user/user/user.h"


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


   void session::initialize(::particle * pparticle)
   {

      //auto estatus = 
      
      ::axis::session::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //m_puiLastLButtonDown             = nullptr;

      m_pmapKeyPressed                 = nullptr;

      m_puiMouseMoveCapture            = nullptr;

      m_bShowPlatform                  = false;

      m_pappCurrent                    = nullptr;

      m_puiMouseMoveCapture = nullptr;

      //return estatus;

   }


   void session::on_instantiate_application(::acme::application* papp)
   {

      ::axis::session::on_instantiate_application(papp);

      //papp->m_pbasesession = this;
      //papp->m_pbasesystem = m_pbasesystem;

   }

   
   ::base::user* session::user()
   {
      
      return m_puser ? m_puser->m_pbaseuser : nullptr; 
   
   }

   
} // namespace base



