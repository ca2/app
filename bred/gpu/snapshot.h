// Created by camilo on 2025-06-12 20:58 <3ThomasBorregaardSørensen!!
#pragma once


namespace gpu
{

   class CLASS_DECL_BRED snapshot :
      virtual public ::particle {
   public:


      ::pointer < context > m_pgpucontext;
      ::int_rectangle m_rectangleTarget;
      ::pointer <texture > m_pgputexture;

      //::comptr < ID3D12Resource > m_presource;

      snapshot();
      ~snapshot() override;

      virtual void initialize_gpu_snapshot(context * pcontext, texture* ptexture, const ::int_rectangle& rectangleTarget);

   };

   

} // namespace gpu



