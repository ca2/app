// Created by camilo on 2025-06-18 19:51 <3ThomasBorregaardSørensen!!
#pragma once


namespace gpu
{



   class CLASS_DECL_BRED compositor :
      virtual public ::particle
   {
   public:

      ::pointer <::gpu::context> m_pgpucontext;


      compositor();
      ~compositor() override;


      virtual void start_gpu_layer();
      virtual void end_gpu_layer();


   };

}
