// Created on 2021-03-29 at 13:00 BRT <3TBS_, Mummi and bilbo!!
#pragma once


#include "acme/graphics/image/_configuration.h"
//#include "acme/prototype/geometry2d/_geometry2d.h"
#include "apex/platform/context.h"


namespace aura
{


   class CLASS_DECL_AURA context :
      virtual public ::platform::context
   {
   public:


      context();
      ~context() override;


      void initialize_context() override;

      void initialize_context_1() override;

      virtual void defer_initialize_context_image() override;

      void destroy() override;



   };


} // namespace apex



