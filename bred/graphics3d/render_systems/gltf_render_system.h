// Changed by camilo on 2025-12-06 21:40 <3ThomasBorregaardSørensen!!
#pragma once


#include "bred/graphics3d/render_systems/pbr_with_ibl_render_system.h"



namespace graphics3d
{


	class CLASS_DECL_BRED gltf_render_system :
		virtual public ::graphics3d::pbr_with_ibl_render_system
	{
	public:

  //    ::graphics3d::scene_renderable *m_pscenerenderableCurrent;
  //    bool m_bDisableAlbedo = false;
  //    bool m_bDisableMetallicRoughness = false;
  //    bool m_bDisableNormal = false;
  //    bool m_bDisableAmbientOcclusion = false;
  //    bool m_bDisableEmissive = false;
  //    bool m_bForceDefaultMetallicFactor = false;
  //    bool m_bForceDefaultRoughnessFactor = false;
  //    bool m_bForceDefaultAmbientOcclusionFactor = false;
  //    bool m_bForceDefaultAlbedo = false;
  //    bool m_bForceDefaultEmission = false;
  //    float m_fDefaultMetallicFactor = 0.0f;
  //    float m_fDefaultRoughnessFactor = 0.0f;
  //    float m_fDefaultAmbientOcclusionFactor = 0.0f;
  //    floating_sequence3 m_seq3DefaultAlbedo={};
  //    floating_sequence3 m_seq3DefaultEmission = {};
  //    ::pointer<::gpu::shader> m_pshader;
		//::pointer < ::gpu::shader > m_pshaderOpaque;
		//::pointer < ::gpu::shader > m_pshaderMask;
		//::pointer < ::gpu::shader > m_pshaderBlend;

		//::pointer <::graphics3d::asset_manager > m_passetmanager;

		gltf_render_system();
		~gltf_render_system();

      void on_prepare(::gpu::context *pgpucontext) override;

		void on_render(::gpu::context* pgpucontext, ::graphics3d::scene_base* pscene) override;


	};


} // namespace graphics3d


