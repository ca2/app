//
// Created by camilo on 2025-08-22 09:34 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace gpu
{

   class CLASS_DECL_BRED queue :
      virtual public ::particle
   {
   public:


      ::pointer < ::gpu::context >        m_pgpucontext;


      queue();
      ~queue() override;


      virtual void initialize_gpu_queue(::gpu::context * pgpucontext);


   };


} // namespace gpu



