// Created by camilo on 2025-05-19 21:58 <3ThomasBorregaardSorensen!!
#pragma once


namespace gpu
{


   class CLASS_DECL_BRED frame :
      virtual public ::particle
   {
   public:


      ::pointer < ::gpu::layer > m_pgpulayer;


      frame();
      ~frame();


      virtual void initialize_frame();




   };


}  // namespace gpu


