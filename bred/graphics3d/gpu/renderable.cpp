//
// Created by camilo on 2025-08-22 22:23 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "renderable.h"


namespace gpu
{



   CLASS_DECL_BRED enum_renderable_type as_renderable_type(const ::scoped_string & scopedstrRenderableType)
   {
      ::string str(scopedstrRenderableType);

      str.make_lower();

      if (str == "obj" || str=="wavefront")
      {
         return e_renderable_type_wavefront_obj;
      }
      else if (str == "gltf")
      {
         return e_renderable_type_gltf;
      }
      else
      {
         return e_renderable_type_none;
      }
   }


   CLASS_DECL_BRED enum_renderable_usage as_renderable_usage(const ::scoped_string & scopedstrRenderableUsage)
   {
      ::string str(scopedstrRenderableUsage);

      str.make_lower();

      if (str == "skybox" || str=="cube")
      {
         return e_renderable_usage_skybox;
      }
      else
      {
         return e_renderable_usage_default;
      }

   }


   renderable_t::renderable_t()
   {


   }


   renderable_t::renderable_t(const ::property_set & set)
   {

      auto &entry = set;

      m_strName = entry["name"];

      set_type(entry["type"].as_string("obj"));

      m_pathRenderable = "matter://models/" + entry["path"].as_file_path();

      set_usage(entry["usage"].as_string(""));

      if (m_erenderabletype == e_renderable_type_gltf)
      {

         m_iFlags = entry["flags"].as_unsigned_int();

         m_fScale = entry["scale"].as_float(1.0f);

      }

      m_bExternalPbr = entry["external_pbr"].is_true();

   }



   void renderable_t::set_type(const ::scoped_string & scopedstrRenderableType)
   {

      m_strRenderableType1 = scopedstrRenderableType;

      m_erenderabletype = as_renderable_type(m_strRenderableType1);


   }


   void renderable_t::set_usage(const ::scoped_string &scopedstrRenderableUsage)
   {

      m_strRenderableUsage1 = scopedstrRenderableUsage;

      m_erenderableusage = as_renderable_usage(m_strRenderableUsage1);

   }


} // namespace gpu



