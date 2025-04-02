// Created by camilo on 2025-03-09 01:24 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/platform/component.h"
#include "apex/database/client.h"


namespace apex
{


   class CLASS_DECL_APEX component :
      virtual public ::component,
      virtual public ::database::client
   {
   public:


      void _update_enabled_implementations() override;


      void handle(::topic * ptopic, ::handler_context * pcontext) override;


      void destroy() override;


   };


} // namespace apex






