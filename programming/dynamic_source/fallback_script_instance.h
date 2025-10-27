// Created by camilo on 2025-10-22 19:56 <3ThomasBorregaardSorensen!!
#pragma once


#include "programming/dynamic_source/script_instance.h"


namespace dynamic_source
{


   class fallback_script_instance :
      virtual public ::dynamic_source::script_instance
   {
   public:
      
      
      fallback_script_instance();
      ~fallback_script_instance() override;
      void run() override;
      virtual void script_run();

   };



} // namespace dynamic_source



