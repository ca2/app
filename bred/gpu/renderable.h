//
// Created by camilo on 2025-08-22 22:22 <2ThomasBorregaardSorense!!
//
#pragma once


namespace gpu
{


   CLASS_DECL_BRED enum_renderable_type as_renderable_type(const ::scoped_string &scopedstrRenderableType);


   CLASS_DECL_BRED enum_renderable_usage as_renderable_usage(const ::scoped_string &scopedstrRenderableUsage);


   struct CLASS_DECL_BRED renderable_t
   {

      ::string m_strName;
      ::file::path m_pathRenderable;
      ::string m_strRenderableType1;
      enum_renderable_type m_erenderabletype;
      ::string m_strRenderableUsage1;
      enum_renderable_usage m_erenderableusage;
      int m_iFlags = -1;
      float m_fScale = 1.0f;
      bool m_bExternalPbr = false;


      renderable_t();
      renderable_t(const ::property_set &set);


      void set_type(const ::scoped_string &scopedstrType);
      void set_usage(const ::scoped_string &scopedstrUsage);

   };


} // namespace gpu
