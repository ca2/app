// Created by camilo on 2025-06-29 03:53 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "input_layout.h"

#include "context.h"


namespace gpu
{


   input_layout::input_layout()
   {


   }


   input_layout::~input_layout()
   {


   }


   void input_layout::initialize_input_layout(::gpu::context * pgpucontext, const properties& properties)
   {

      m_pgpucontext = pgpucontext;

      set(properties.m_pproperties);

      on_initialize_input_layout();

   }

   
   void input_layout::on_initialize_input_layout()
   {


   }


} // namespace gpu



