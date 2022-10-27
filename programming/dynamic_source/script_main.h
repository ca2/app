#pragma once


#include "script_interface.h"


namespace dynamic_source
{


   class CLASS_DECL_APP_PROGRAMMING script_main :
      virtual public script_interface
   {
   public:


      ::netnode::script_main *            m_pnetnodescriptmain;

      ::pointer<httpd_socket>            m_psocket2;
      ::pointer<script_manager>          m_pmanager2;


      script_main();
      ~script_main() override;


#ifdef _DEBUG

      virtual ::i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;

      virtual ::i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;

#endif

      void initialize(::particle * pparticle) override;


      void destroy() override;

      virtual bool main_initialize();
      virtual bool main_finalize();


   };


} // namespace dynamic_source



