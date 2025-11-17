#include "framework.h"
#include "script_composite.h"
#include "script_main.h"


namespace dynamic_source
{


   //script_composite::script_composite()
   //{

   //}


   script_composite::~script_composite()
   {

   }


   void script_composite::initialize(::particle * pparticle)
   {

      //auto estatus = 
      
      script_interface::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void script_composite::initialize_script_composite(script_interface* pscriptinterface)
   {

      m_pinterface = pscriptinterface;

      auto phttpdsocket1Old = m_phttpdsocket1;

      m_phttpdsocket1 = pscriptinterface->m_phttpdsocket1;

      if (!m_phttpdsocket1 && phttpdsocket1Old)
      {

         ::output_debug_string("!m_phttpdsocket1");

      }

      m_pscriptmain1 = pscriptinterface->m_pscriptmain1;

      m_pscriptmanager1 = pscriptinterface->m_pscriptmanager1;

   }


   void script_composite::initialize_with_socket_thread(::httpd::socket_thread* psocketthread)
   {

      ::dynamic_source::script_interface::initialize_with_socket_thread(psocketthread);

      m_pinterface = m_pscriptmain1;

   }


   void script_composite::destroy()
   {

      m_pinterface.release();

      script_interface::destroy();

   }


} // namespace dynamic_source



