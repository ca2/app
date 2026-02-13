// Created by camilo on 2025-10-16 19:05 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "_hlsl.h"

namespace hlsl
{

#include "hlsl/brdf_convolution_map.frag.h"
#include "hlsl/brdf_convolution_map.vert.h"

#include "hlsl/diffuse_irradiance_map.frag.h"
#include "hlsl/diffuse_irradiance_map.vert.h"

#include "hlsl/equirectangular_cubemap.frag.h"
#include "hlsl/equirectangular_cubemap.vert.h"


#include "hlsl/prefiltered_environment_map.frag.h"
#include "hlsl/prefiltered_environment_map.vert.h"


#include "hlsl/gltf.frag.h"
#include "hlsl/gltf.vert.h"


#include "hlsl/scene.frag.h"
#include "hlsl/scene.vert.h"


} // namespace hlsl namespace hlsl

CLASS_DECL_GPU::block hlsl_brdf_convolution_vert_memory()
{
   return  hlsl::g_psz_brdf_convolution_map_vert; 
}

   CLASS_DECL_GPU::block hlsl_brdf_convolution_frag_memory()
{
   return hlsl::g_psz_brdf_convolution_map_frag;
}


CLASS_DECL_GPU::block hlsl_embedded_diffuse_irradiance_vert()
{
   return hlsl::g_psz_diffuse_irradiance_map_vert;
}
   CLASS_DECL_GPU::block hlsl_embedded_diffuse_irradiance_frag() { return hlsl::g_psz_diffuse_irradiance_map_frag; }

   ::block hlsl_prefiltered_environment_map_vert_memory()
{

   return hlsl::g_psz_prefiltered_environment_map_vert;
}


::block hlsl_prefiltered_environment_map_frag_memory()
{

   return hlsl::g_psz_prefiltered_environment_map_frag;
}


::block hlsl_embedded_ibl_hdri_cube_vert() 
{ return hlsl::g_psz_equirectangular_cubemap_vert; 
}
      


::block hlsl_embedded_ibl_hdri_cube_frag()
{

   return hlsl::g_psz_equirectangular_cubemap_frag;
}



::block hlsl_embedded_gltf_vert()
{

   return hlsl::g_psz_gltf_vert;
}


::block hlsl_embedded_gltf_frag() {

   return hlsl::g_psz_gltf_frag;
}



::block hlsl_embedded_scene_vert() { return hlsl::g_psz_scene_vert; }


::block hlsl_embedded_scene_frag() { return hlsl::g_psz_scene_frag; }
