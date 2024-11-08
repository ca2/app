#pragma once


#include "script_interface.h"


namespace dynamic_source
{


   class CLASS_DECL_APP_PROGRAMMING script_composite :
      virtual public script_interface
   {
   public:


      ::pointer<script_interface>      m_pinterface;


      script_composite();
      ~script_composite() override;


      void initialize(::particle * pparticle) override;

      //void finalize() override;

      void destroy() override;


   };


} // namespace dynamic_source



