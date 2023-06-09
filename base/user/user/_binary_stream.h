// from user/picture.cpp by camilo on 2022-10-15 04:31 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/filesystem/file/binary_stream.h"


template < typename FILE >
binary_stream < FILE > & operator << (binary_stream < FILE > & stream, const ::user::picture & picture)
{

   if (stream.is_version(FIRST_VERSION))
   {

      bool bEnable = false;

      bEnable = m_ppictureimpl != nullptr;

      stream << bEnable;

      if (bEnable)
      {

         stream << *m_ppictureimpl;

      }

   }

}

template < typename FILE >
binary_stream < FILE > & operator << (binary_stream < FILE > & stream, const ::user::picture & picture)
{

   picture.write(stream);

   return stream;

}


template < typename FILE >
binary_stream < FILE > & operator >> (binary_stream < FILE > & stream, ::user::picture & picture)
{

   if (stream.is_version(FIRST_VERSION))
   {

      bool bEnable = false;

      stream >> bEnable;

      enable_picture(bEnable);

      if (bEnable)
      {

         stream >> *m_ppictureimpl;

      }

   }

}



template < typename FILE >
binary_stream < FILE > & operator << (binary_stream < FILE > & stream, const ::user::picture::picture_impl & t)
{

   stream << t.m_rectangle;
   stream << t.m_rectangleDrawing;
   stream << t.m_rectangleCursor;
   stream << t.m_bDrag;
   stream << t.m_dRotate;
   stream << t.m_rectangleBounding;
   stream << t.m_polygon;
   stream << t.m_polygonDrawing;
   stream << t.m_pointaCursor;
   stream << t.m_dZoom;
   stream << t.m_pointDrag2;
   stream << t.m_bOutline;
   stream << t.m_iOutlineWidth;
   stream << t.m_hlsOutline;
   stream << t.m_bGlowDropShadow;
   stream << t.m_iGlowDropShadowOffset;
   stream << t.m_iGlowDropShadowBlur;
   stream << t.m_hlsGlowDropShadow;
   stream << t.m_iBlur;
   stream << t.m_bGrayscale;
   stream << t.m_bInvert;
   stream << t.m_iOpacity;
   stream << t.m_iSaturation;

   return stream;


}



template < typename FILE >
binary_stream < FILE > & operator >> (binary_stream < FILE > & stream, ::user::picture::picture_impl & t)
{

   stream >> t.m_rectangle;
   stream >> t.m_rectangleDrawing;
   stream >> t.m_rectangleCursor;
   stream >> t.m_bDrag;
   stream >> t.m_dRotate;
   stream >> t.m_rectangleBounding;
   stream >> t.m_polygon;
   stream >> t.m_polygonDrawing;
   stream >> t.m_pointaCursor;
   stream >> t.m_dZoom;
   stream >> t.m_pointDrag2;
   stream >> t.m_bOutline;
   stream >> t.m_iOutlineWidth;
   stream >> t.m_hlsOutline;
   stream >> t.m_bGlowDropShadow;
   stream >> t.m_iGlowDropShadowOffset;
   stream >> t.m_iGlowDropShadowBlur;
   stream >> t.m_hlsGlowDropShadow;
   stream >> t.m_iBlur;
   stream >> t.m_bGrayscale;
   stream >> t.m_bInvert;
   stream >> t.m_iOpacity;
   stream >> t.m_iSaturation;

   return stream;

}




