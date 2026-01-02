// Created by camilo on 2025-12-09 <3ThomasBorregaardSørensen!!
#pragma once


namespace gpu
{


   struct texture_data
   {
   protected:

      enum_texture_data m_etexturedata = e_texture_data_none;
      ::pointer_array<::image::image> m_imagea;
      ::file::path m_path;
      const void *m_p = nullptr;

   public:


      texture_data() : m_etexturedata(e_texture_data_none) {}

      texture_data(const ::pointer_array<::image::image> &imagea) : m_etexturedata(e_texture_data_image_array), m_imagea(imagea) {}

      texture_data(const ::file::path &path) : m_etexturedata(e_texture_data_file_path), m_path(path) {}
      texture_data(const void *p) : m_etexturedata(e_texture_data_raw_scoped_data), m_p(p) {}

      bool is_image_array() const { return m_etexturedata == e_texture_data_image_array && m_imagea.has_element(); }
      bool is_file_path() const { return m_etexturedata == e_texture_data_file_path && m_path.has_character(); }

      bool is_raw_scoped_data() const { return m_etexturedata == e_texture_data_raw_scoped_data && ::is_set(m_p); }
      const ::pointer_array<::image::image> &imagea() const
      {
         ASSERT(is_image_array());

         return m_imagea;
      }

      const ::file::path &file_path() const
      {
         ASSERT(is_file_path());

         return m_path;
      }

      const void *raw_scoped_data() const
      {

         ASSERT(is_raw_scoped_data());

         return m_p;
      }

      enum_texture_data type() const { return m_etexturedata; }

      bool is_set() const {return m_etexturedata != e_texture_data_none;}
      bool is_empty() const {return !this->is_set();}
   };


} // namespace gpu




