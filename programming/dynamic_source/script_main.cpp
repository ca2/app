#include "framework.h"
#include "_.h"


namespace dynamic_source
{


   script_main::script_main()
   {

      m_posdataNetnodeScriptMain = nullptr;

      __note_assign(m_pmain, this, "this is annotation");

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


   ::estatus script_main::initialize(::layered * pobjectContext)
   {

      auto estatus = ::html::file::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   void script_main::finalize()
   {
         
      script_interface::finalize();

      __named_release(m_pmain);

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



