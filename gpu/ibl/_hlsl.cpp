// Created by camilo on 2025-10-16 19:05 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "_hlsl.h"

namespace hlsl
{

#include "hlsl/brdfconvolution.frag.h"
#include "hlsl/brdfconvolution.vert.h"

#include "hlsl/diffuseirradiance.frag.h"
#include "hlsl/diffuseirradiance.vert.h"

#include "hlsl/hdricube.frag.h"
#include "hlsl/hdricube.vert.h"

#include "hlsl/pbr.frag.h"
#include "hlsl/pbr.vert.h"

#include "hlsl/specularenv.frag.h"
#include "hlsl/specularenv.vert.h"


} // namespace hlsl namespace hlsl


CLASS_DECL_GPU::block hlsl_embedded_brdf_convolution_frag()
{
   return {hlsl::g_psz_brdfconvolution_frag, sizeof(hlsl::g_psz_brdfconvolution_frag) - 1};
}
CLASS_DECL_GPU::block hlsl_embedded_brdf_convolution_vert()
{
   return {hlsl::g_psz_brdfconvolution_vert, sizeof(hlsl::g_psz_brdfconvolution_vert) - 1};

}

CLASS_DECL_GPU::block hlsl_embedded_diffuse_irradiance_frag()
{
   return {hlsl::g_psz_diffuseirradiance_frag, sizeof(hlsl::g_psz_diffuseirradiance_frag) - 1};
}
CLASS_DECL_GPU::block hlsl_embedded_diffuse_irradiance_vert()
{
   return {hlsl::g_psz_diffuseirradiance_vert, sizeof(hlsl::g_psz_diffuseirradiance_vert) - 1};
}

::block hlsl_embedded_prefiltered_env_map_vert()
{

   return {hlsl::g_psz_specularenv_vert, sizeof(hlsl::g_psz_specularenv_vert) - 1};
}


::block hlsl_embedded_prefiltered_env_map_frag()
{

   return {hlsl::g_psz_specularenv_frag, sizeof(hlsl::g_psz_specularenv_frag) - 1};
}


::block hlsl_embedded_ibl_hdri_cube_vert()
{

   return {hlsl::g_psz_hdricube_vert, sizeof(hlsl::g_psz_hdricube_vert) - 1}; }


::block hlsl_embedded_ibl_hdri_cube_frag()
{

   return {hlsl::g_psz_hdricube_frag, sizeof(hlsl::g_psz_hdricube_frag) - 1}; }



::block hlsl_embedded_pbr_vert()
{

   return {hlsl::g_psz_pbr_vert, sizeof(hlsl::g_psz_pbr_vert) - 1};
}


::block hlsl_embedded_pbr_frag() {

   return {hlsl::g_psz_pbr_frag, sizeof(hlsl::g_psz_pbr_frag) - 1};
}
