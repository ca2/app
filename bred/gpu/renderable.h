//
// Created by camilo on 2025-08-22 22:22 <2ThomasBorregaardSorense!!
//
#pragma once


namespace gpu
{


   enum enum_coordinate_system
   {

      e_coordinate_system_none,
      e_coordinate_system_opengl,
      e_coordinate_system_vulkan,
      e_coordinate_system_directx,
      e_coordinate_system_znf, // z normal flipped
      e_coordinate_system_z_minus,
      e_coordinate_system_y_up,

   };

   CLASS_DECL_BRED enum_renderable_type as_renderable_type(const ::scoped_string &scopedstrRenderableType);


   CLASS_DECL_BRED enum_renderable_usage as_renderable_usage(const ::scoped_string &scopedstrRenderableUsage);

   
   CLASS_DECL_BRED enum_coordinate_system as_coordinate_system(const ::scoped_string &scopedstrCoordinateSystem);


   struct CLASS_DECL_BRED renderable_t
   {

      ::string m_strName;
      ::file::path m_pathRenderable;
      ::string m_strRenderableType1;
      enum_renderable_type m_erenderabletype;
      ::string m_strRenderableUsage1;
      enum_renderable_usage m_erenderableusage;
      ::string m_strCoordinateSystem1;
      enum_coordinate_system m_ecoordinatesystem;
      int m_iFlags = -1;
      float m_fScale = 1.0f;
      bool m_bExternalPbr = false;


      renderable_t();
      renderable_t(const ::property_set &set);


      void set_type(const ::scoped_string &scopedstrType);
      void set_usage(const ::scoped_string &scopedstrUsage);
      void set_coordinate_system(const ::scoped_string &scopedstrCoordinateSystem);

   };


} // namespace gpu
