//
// Created by camilo on 2025-08-22 22:23 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "renderable.h"


namespace gpu
{



   CLASS_DECL_BRED enum_model as_gpu_model(const ::scoped_string & scopedstrRenderableType)
   {

      ::string str(scopedstrRenderableType);

      str.make_lower();

      if (str == "obj" || str=="wavefront")
      {
         return e_model_wavefront;
      }
      else if (str == "gltf")
      {
         return e_model_gltf;
      }
      else
      {
         return e_model_none;
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


   CLASS_DECL_BRED enum_coordinate_system as_coordinate_system(const ::scoped_string &scopedstrCoordinateSystem)
   {

      ::string str(scopedstrCoordinateSystem);

      str.make_lower();

      if (str == "opengl")
      {
         return e_coordinate_system_opengl;
      }
      else if (str == "vulkan")
      {
         return e_coordinate_system_vulkan;
      }
      else if (str == "directx")
      {
         return e_coordinate_system_directx;
      }
      else if (str == "z-")
      {
         return e_coordinate_system_z_minus;
      }
      else if (str == "yup")
      {
         return e_coordinate_system_y_up;
      }
      else
      {
         return e_coordinate_system_none;
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

      set_coordinate_system(entry["coordinate_system"].as_string(""));

      if (m_egpumodel == e_model_gltf)
      {

         m_iFlags = entry["flags"].as_unsigned_int();

         m_fScale = entry["scale"].as_float(1.0f);

      }

      m_bExternalPbr = entry["external_pbr"].is_true();

   }


   void renderable_t::set_type(const ::scoped_string & scopedstrRenderableType)
   {

      m_strRenderableType1 = scopedstrRenderableType;

      m_egpumodel = as_gpu_model(m_strRenderableType1);

   }


   void renderable_t::set_usage(const ::scoped_string &scopedstrRenderableUsage)
   {

      m_strRenderableUsage1 = scopedstrRenderableUsage;

      m_erenderableusage = as_renderable_usage(m_strRenderableUsage1);

   }


   void renderable_t::set_coordinate_system(const ::scoped_string &scopedstrCoordinateSystem)
   {

      m_strCoordinateSystem1 = scopedstrCoordinateSystem;

      m_ecoordinatesystem = as_coordinate_system(m_strCoordinateSystem1);

   }


} // namespace gpu



