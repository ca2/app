// Created by camilo on 2025-06-18 19:51 <3ThomasBorregaardSørensen!!
#pragma once


namespace gpu
{



   class CLASS_DECL_BRED compositor :
      virtual public ::particle
   {
   public:
      bool m_bInLayer = false;

      ::pointer <::gpu::context> m_pgpucontext;


      compositor();
      ~compositor() override;


      virtual void start_gpu_layer();
      virtual void end_gpu_layer();


      virtual void gpu_layer_on_after_begin_render();
      virtual void gpu_layer_on_before_end_render();


      virtual void just_after_new_frame();

      virtual void on_start_layer();
      virtual void on_end_layer();

   };

}
