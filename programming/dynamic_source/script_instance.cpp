#include "framework.h"
#include "script.h"
#include "script_instance.h"
#include "script_main.h"
#include "script_manager.h"


namespace dynamic_source
{


   //script_instance::script_instance()
   //{

   //}


   script_instance::~script_instance()
   {

   }


   void script_instance::initialize_script_instance_script(
      ::dynamic_source::script* pscript1)
   {

      m_pscriptmanager1 = pscript1->m_pscriptmanager1;

      m_pscript1 = pscript1;

   }


   void script_instance::initialize_script_instance(
      ::dynamic_source::script_interface* pscriptinterfaceParent1)
   {

      m_pscriptmain1 = pscriptinterfaceParent1->m_pscriptmain1;

      m_pscriptmain1->m_pscriptinstanceLastlyInstantiated = this;

      m_pinstanceParent1 = pscriptinterfaceParent1;

      initialize_script_composite(m_pscriptmain1);

   }


   bool script_instance::ShouldBuild()
   {

      return false;

   }




} // namespace dynamic_source



