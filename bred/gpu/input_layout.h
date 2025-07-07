// Created by camilo on 2025-06-29 03:32 <3ThomasBorregaardSørensen!!
#pragma once


#include "bred/gpu/properties.h"


namespace gpu
{


   class CLASS_DECL_BRED input_layout :
      virtual public properties,
      virtual public ::particle
   {
   public:


      ::pointer < ::gpu::context >  m_pgpucontext;


      input_layout();
      ~input_layout() override;


      virtual void initialize_input_layout(::gpu::context * pgpucontext, const properties & properties);

      virtual void on_initialize_input_layout();


   };


} // namespace gpu



