#include "framework.h"
#include "dynamic_source.h"


namespace dynamic_source
{


   script_instance::script_instance(script * pscript) :
      ::object(pscript)
   {

      m_pscript = pscript;

      m_pscriptScriptInstance = pscript;

   }


   script_instance::~script_instance()
   {

   }

   bool script_instance::ShouldBuild()
   {

      return false;

   }

   
   bool script_interface::rerun()
   {

      return false;

   }


   var script_interface::call_run()
   {

      bool bRerun = rerun();

      bool bOk = false;

      try
      {

         bOk = run();

      }
      catch (const ::dynamic_source::exit_exception & e)
      {

         destroy();

         throw e;

      }
      catch (...)
      {

         // stop point
         bOk = false;

      }

      var var = m_varRet;

      try
      {

         destroy();

      }
      catch (...)
      {

      }

      if (bRerun)
      {

         run();

      }

      if (!bOk)
      {

         return type_empty;

      }

      return var;

   }


} // namespace dynamic_source



