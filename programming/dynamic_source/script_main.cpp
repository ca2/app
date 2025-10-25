#include "framework.h"
#include "httpd_socket.h"
#include "script.h"
#include "script_main.h"
#include "script_manager.h"


namespace dynamic_source
{


   script_main::script_main()
   {

      //m_pmanager2 = nullptr;

      m_pnetnodescriptmain = nullptr;

   }


   script_main::~script_main()
   {


   }


#ifdef _DEBUG


   long long script_main::increment_reference_count()
   {

      return script_interface::increment_reference_count();

   }


   long long script_main::decrement_reference_count()
   {

      return script_interface::decrement_reference_count();

   }


#endif


   void script_main::initialize(::particle * pparticle)
   {

      ::dynamic_source::script_interface::initialize(pparticle);

   }


   void script_main::initialize_script_main(
      ::dynamic_source::script_manager* pscriptmanager1,
      ::dynamic_source::httpd_socket* phttpsocket1,
      ::dynamic_source::script* pscript1)
   {

      m_pscriptmanager1 = pscriptmanager1;

      auto phttpdsocket1Old = m_phttpdsocket1;

      m_phttpdsocket1 = phttpsocket1;

      if (!m_phttpdsocket1 && phttpdsocket1Old)
      {

         ::output_debug_string("!m_phttpdsocket1");

      }


      m_pscript1 = pscript1;

      m_pscriptmain1 = this;

   }


   void script_main::destroy()
   {

      //try
      //{

      //   for (auto& pinterface : m_interfacea)
      //   {

      //      try
      //      {

      //         if (pinterface)
      //         {

      //            pinterface->m_pmain.release();

      //         }

      //      }
      //      catch (...)
      //      {

      //      }

      //   }

      //}
      //catch (...)
      //{

      //}

      m_interfacea.clear();
         
      m_phttpdsocket1.release();

      //m_pmanager2.release();

      script_interface::destroy();

   }


   bool script_main::main_initialize()
   {

      return true;

   }


   bool script_main::main_finalize()
   {

      destroy();

      return true;

   }


} // namespace dynamic_source



