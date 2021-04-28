#include "framework.h"
#include "_.h"


namespace dynamic_source
{


   script_main::script_main()
   {

      m_posdataNetnodeScriptMain = nullptr;

      __note_assign(m_pmain, this, OBJ_REF_DBG_COMMA_THIS_NOTE("this is annotation"));

   }


   script_main::~script_main()
   {


   }


#ifdef DEBUG


   ::i64 script_main::add_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return script_interface::add_ref(OBJ_REF_DBG_ARGS);

   }


   ::i64 script_main::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return script_interface::dec_ref(OBJ_REF_DBG_ARGS);

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


   ::e_status script_main::finalize()
   {
         
      auto estatus = script_interface::finalize();

      __named_release(m_pmain);

      return estatus;

   }


   bool script_main::main_initialize()
   {

      return true;

   }


   bool script_main::main_finalize()
   {

      finalize();

      return true;

   }


} // namespace dynamic_source



