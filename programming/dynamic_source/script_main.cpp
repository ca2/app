#include "framework.h"
#include "_.h"


namespace dynamic_source
{


   script_main::script_main()
   {

      m_pnetnodescriptmain = nullptr;

      __note_assign(m_pmain, this, OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS_NOTE("this is annotation"));

   }


   script_main::~script_main()
   {


   }


#ifdef DEBUG


   ::i64 script_main::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return script_interface::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   ::i64 script_main::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return script_interface::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


#endif


   ::e_status script_main::initialize(::object * pobject)
   {

      auto estatus = ::html::file::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status script_main::destroy()
   {
         
      auto estatus = script_interface::destroy();

      m_psocket2.release();
      m_pmanager2.release();

      return estatus;

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



