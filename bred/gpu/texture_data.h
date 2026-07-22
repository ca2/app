// Created by camilo on 2025-12-09 <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/graphics/image/pixmap.h"


namespace gpu
{


   struct texture_data
   {
   protected:

      enum_texture_data m_etexturedata = e_texture_data_none;
      ::pointer_array<::pixmap> m_pixmapa;
      ::file::path m_path;
      pixmap_t m_pixmap;

   public:


      texture_data() : m_etexturedata(e_texture_data_none) {}

      texture_data(const ::pointer_array<::pixmap> &pixmapa) :
          m_etexturedata(e_texture_data_image_array), m_pixmapa(pixmapa)
      {
      }

      texture_data(const ::file::path &path) : m_etexturedata(e_texture_data_file_path), m_path(path) {}
      texture_data(const pixmap_t & pixmap) : m_etexturedata(e_texture_data_raw_scoped_pixmap), m_pixmap(pixmap) {}

      bool is_pixmap_array() const { return m_etexturedata == e_texture_data_image_array && m_pixmapa.has_element(); }
      bool is_file_path() const { return m_etexturedata == e_texture_data_file_path && m_path.has_character(); }

      bool is_raw_scoped_pixmap() const { return m_etexturedata == e_texture_data_raw_scoped_pixmap && m_pixmap.is_ok(); }
      const ::pointer_array<::pixmap> &pixmapa() const
      {
         if (!is_pixmap_array())
         {

            throw ::exception(error_wrong_state);

         }

         return m_pixmapa;
      }

      const ::file::path &file_path() const
      {
         if (!is_file_path())
         {

            throw ::exception(error_wrong_state);

         }

         return m_path;
      }

      const ::pixmap_t & raw_scoped_pixmap() const
      {

         if (!is_raw_scoped_pixmap())
         {

            throw ::exception(error_wrong_state);

         }

         return m_pixmap;
      }

      enum_texture_data type() const { return m_etexturedata; }

      bool is_set() const {return m_etexturedata != e_texture_data_none;}
      bool is_empty() const {return !this->is_set();}
   };


} // namespace gpu




