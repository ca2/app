//
// Created by camilo on 30/12/2021. 14:56 BRT <ThomasBorregaardSorensen!!
//
#include "platform.h"
#include "meta.h"


namespace image
{


   image_meta::~image_meta()
   {

      //::release(m_pdraw2dbitmap);
      //::release(m_pgraphics);

   }


   void image_meta::set_exif_orientation(::i32 iExifOrientation)
   {

      m_iExifOrientation = iExifOrientation;


   }


   void image_meta::set_image_source_path(const ::file::path & path)
   {

      m_pathImageSource = path;
      m_sizeImageSource = {};
      m_eImageDerivation = e_image_derivation_none;

   }


   void image_meta::set_stretched_from(const image_meta & imagemetaSource)
   {

      m_pathImageSource = imagemetaSource.m_pathImageSource;
      m_sizeImageSource = imagemetaSource.size();
      m_eImageDerivation = e_image_derivation_stretched;

   }


   ::string image_meta::image_debug_provenance() const
   {

      ::string strProvenance;

      if (m_eImageDerivation == e_image_derivation_stretched)
      {

         strProvenance.formatf(" derived=stretch source_path=%s source_size=%dx%d",
            m_pathImageSource.has_character() ? m_pathImageSource.c_str() : "(unknown)",
            m_sizeImageSource.cx, m_sizeImageSource.cy);

      }
      else if (m_pathImageSource.has_character())
      {

         strProvenance.formatf(" source_path=%s", m_pathImageSource.c_str());

      }

      return strProvenance;

   }


} // namespace image



