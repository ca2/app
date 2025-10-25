#pragma once


#include "script_interface.h"


namespace dynamic_source
{


   class CLASS_DECL_APP_PROGRAMMING script_main :
      virtual public script_interface
   {
   public:


      ::netnode::script_main *                                 m_pnetnodescriptmain;

      //::pointer<httpd_socket>                                  m_phttpsocket1;
      //::pointer < script_manager >                             m_pscriptmanager2;
      ::pointer < script_instance >                            m_pscriptinstanceLastlyInstantiated;
      ::pointer_array < ::dynamic_source::script_interface >   m_interfacea;

      ::pointer<::dynamic_source::script_interface>            m_pscriptinterfaceTopic;

      //::url::url                                               m_url;


      script_main();
      ~script_main() override;


#ifdef _DEBUG

      virtual long long increment_reference_count() override;

      virtual long long decrement_reference_count() override;

#endif

      void initialize(::particle * pparticle) override;

      virtual void initialize_script_main(
         ::dynamic_source::script_manager* pscriptmanager1,
         ::dynamic_source::httpd_socket * phttpsocket1,
         ::dynamic_source::script * pscript1);

      //void finalize() override;

      void destroy() override;

      virtual bool main_initialize();
      virtual bool main_finalize();



   };


} // namespace dynamic_source



