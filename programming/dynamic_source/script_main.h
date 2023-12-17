#pragma once


#include "script_interface.h"


namespace dynamic_source
{


   class CLASS_DECL_APP_PROGRAMMING script_main :
      virtual public script_interface
   {
   public:


      ::netnode::script_main *                                 m_pnetnodescriptmain;

      ::pointer<httpd_socket>                                  m_psocket2;
      ::pointer<script_manager>                                m_pmanager2;


      ::pointer_array < ::dynamic_source::script_interface >   m_interfacea;



      script_main();
      ~script_main() override;


#ifdef _DEBUG

      virtual ::i64 increment_reference_count() override;

      virtual ::i64 decrement_reference_count() override;

#endif

      void initialize(::particle * pparticle) override;

      void finalize() override;

      void destroy() override;

      virtual bool main_initialize();
      virtual bool main_finalize();



   };


} // namespace dynamic_source



