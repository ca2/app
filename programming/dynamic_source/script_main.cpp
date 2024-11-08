#include "framework.h"
#include "script_main.h"


namespace dynamic_source
{


   script_main::script_main()
   {

      m_pmanager2 = nullptr;

      m_pnetnodescriptmain = nullptr;

   }


   script_main::~script_main()
   {


   }


#ifdef _DEBUG


   huge_integer script_main::increment_reference_count()
   {

      return script_interface::increment_reference_count();

   }


   huge_integer script_main::decrement_reference_count()
   {

      return script_interface::decrement_reference_count();

   }


#endif


   void script_main::initialize(::particle * pparticle)
   {

      ::dynamic_source::script_interface::initialize(pparticle);

   }


   void script_main::destroy()
   {

      try
      {

         for (auto& pinterface : m_interfacea)
         {

            try
            {

               if (pinterface)
               {

                  pinterface->m_pmain.release();

               }

            }
            catch (...)
            {

            }

         }

      }
      catch (...)
      {

      }

      m_interfacea.clear();
         
      m_psocket2.release();

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



