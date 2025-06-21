// Created by camilo on 2025-06-12 20:58 <3ThomasBorregaardSørensen!!
#pragma once


namespace gpu
{


   class CLASS_DECL_BRED layer :
      virtual public ::particle
   {
   public:


      ::pointer < renderer >        m_pgpurenderer;
      //::pointer < renderer >        m_pgpurendererTarget;
      //::int_rectangle m_rectangleTarget;
      ::pointer_array <texture >    m_gputexturea;
      //::pointer_array <texture >    m_gputextureaTarget;

      //::comptr < ID3D12Resource > m_presource;

      layer();
      ~layer() override;


      virtual void initialize_gpu_layer(renderer * pgpurenderer);


      //virtual void set_target_texture(texture* ptextureTarget);


      virtual void layer_end();


      ::pointer < texture > & texture();
      renderer * renderer();


   };
   

} // namespace gpu



