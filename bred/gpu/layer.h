// Created by camilo on 2025-06-12 20:58 <3ThomasBorregaardSørensen!!
#pragma once


namespace gpu
{


   class CLASS_DECL_BRED layer :
      virtual public ::particle
   {
   public:


      ::pointer < renderer > m_pgpurenderer;
      ::int_rectangle m_rectangleTarget;
      ::pointer <texture > m_pgputextureSource;
      ::pointer <texture > m_pgputexture;

      //::comptr < ID3D12Resource > m_presource;

      layer();
      ~layer() override;


      virtual void initialize_gpu_layer(renderer * pgpurenderer, const ::int_rectangle& rectangleTarget);


      virtual void set_texture(texture* ptexture);


      virtual void take_snapshot();


   };
   

} // namespace gpu



